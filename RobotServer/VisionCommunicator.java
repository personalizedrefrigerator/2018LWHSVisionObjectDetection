package org.usfirst.frc.team5827.robot;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

import edu.wpi.first.wpilibj.networktables.NetworkTable;

/**
 *  A class handling all communication with the vision system.
 *  Sockets are used in place of network tables (for now).
 *  DO NOT use WPILib code in this class.
 * @author Henry Heino
 */

public class VisionCommunicator
{
	public static int PORT_NUMBER=4342;
	private ServerSocket server;
	private NetworkTable table;
	private static final boolean SOCKETS = true;
	private boolean stopServer = false;
	
	private VisionOutput visionInformation = new VisionOutput();
	
	// Log an error to the console.
	private void logError(Exception error)
	{
		StackTraceElement[] stackTraceList = error.getStackTrace();
		
		String stackTrace="";
		
		for(StackTraceElement currentTrace : stackTraceList)
		{
			stackTrace += "\nIn " + currentTrace.getFileName() + ", " + currentTrace.getMethodName() + ", line " + currentTrace.getLineNumber() + ".";
		}
		
		// Log the error.
		System.err.printf("Error: %s, %s%n", error.getMessage(), stackTrace);
		//Logging.consoleLog("Error: %s, %s", error.getMessage(), stackTrace);
	}
	
	class Server implements Runnable
	{
		private ServerSocket server;
		private Socket client;
		private PrintWriter output;
		private BufferedReader input;
		
		public Server(ServerSocket serverToUse)
		{
			server=serverToUse;
		}
		
		public String charArrayToString(char[] input)
		{
			StringBuilder resultBuilder = new StringBuilder();
			
			for(char c : input)
			{
				resultBuilder.append(c);
			}
			
			return resultBuilder.toString();
		}
		
		public boolean connectToClient()
		{
			try
			{
				// Accept a connection to a client.
				client = server.accept();
				
				// Create the input and output streams.
				input = new BufferedReader(new InputStreamReader(client.getInputStream()));
				output = new PrintWriter(client.getOutputStream());
				
				// Return true, the connection was a success.
				return true;
			}
			catch(IOException e)
			{
				//Logging.consoleLog("Error connecting to client: %s, trace: %s.", e.getMessage(), e.getStackTrace());
				
				// If not, wait 500 ms.
				try
				{
					Thread.sleep(500);
				}
				catch (InterruptedException e1)
				{
					logError(e1);
				}
				
				logError(e);
				
				// Note that an error occurred.
				return false;
			}
		}
		
		/**
		 *  Handle an HTTP web-browser request.
		 *  @param requestType This should be either GET or POST, the type of request given to the server.
		 *  @param filePath This should be the name of the file requested.
		 *  @return The server's response.
		 */
		private String handleWebBrowserRequest(String requestType, String filePath)
		{
			String response = "HTTP/1.1 200 OK\r\nServer: WebServer\r\nContent-type: text/html\r\n\r\n"; // HTTP 1.1 response header.
			
			// JDK7 Strings work in switch statements.
			switch(requestType)
			{
			case "GET":
				response += "<!DOCTYPE html>"
							+ "<html>"
							+ "<head>"
							+ WebHelper.getDefaultMetas()
							+ "<title>Debug Page</title>"
							+ WebHelper.getDefaultStyleSheet()
							+ "</head>"
							+ "<body>"
							+ "<div id = 'contentDiv'>"
							+ "<h1>A Debug Page</h1>"
							+ "<p>This port is to be used for communication between the Jetson TX1 and the roboRIO.</p>"
							+ "<ul>"
							+ "<li>The server is running and accepting connections.</li>"
							+ "<li><b>TODO</b> Display other useful information here.</li>"
							+ visionInformation.getAsHTMLString() // Reading from visionInformation should be fine without locking data.
							+ "</ul>"
							+ "</div>"
							+ "</body>"
							+ "</html>";
				break;
			case "POST":
				response += "Not implemented.";
				break;
			default:
				response += "Not a valid request type.";
				break;
			}
			
			return response;
		}
		
		
		/**
		 *  Handle a command given to the server.
		 * @param command The first element of args or the command to be run.
		 * @param args All arguments to the command.
		 * @return The command's response to input.
		 */
		public String handleServerCommand(String command)
		{
			// Create a variable to store the server's response.
			String response = "";
			
			// Find the property or command portion.
			String[] commandParts = command.split(" ");
			
			if(command.indexOf("HTTP") > 0 && command.indexOf("HTTP") < "GET / HTTP/1.1".length())
			{
				response = handleWebBrowserRequest(commandParts[0], commandParts[1]);
			}
			else
			{
				// JDK7 Strings work in switch statements.
				switch(commandParts[0])
				{
				case "SET":
					// Format: SET <table name> <variable>=<value>;
					if(commandParts.length < 3)
					{
						response = "FORMAT ERROR";
						break; // This section must have at least 3 inputs.
					}
					
					int secondSpaceLocation = commandParts[0].length() + 1 + commandParts[1].length() + 1;
					
					String setSegement = command.substring(secondSpaceLocation); // <variable>=<value>, without spaces.
					
					int equalsLocation = setSegement.indexOf('=');
					int semicolonLocation = setSegement.indexOf(';');
					
					// If either of the two was not found,
					if(equalsLocation < 0 || semicolonLocation < 0)
					{
						response = "FORMAT ERROR"; // Note the error.
						
						break; // Exit.
					}
					
					// Find the key, remove excess spaces.
					String keyName = setSegement.substring(0, equalsLocation);
					keyName.trim();
					
					// Find the value and trim excess spacing. Use equalsLocation + 1 to ignore the equals-sign.
					String value = setSegement.substring(equalsLocation + 1, semicolonLocation);
					value.trim();
					
					// Prevent data racing (multiple writes at the same time).
					synchronized(visionInformation)
					{
						visionInformation.putKey(keyName, value);
					}
					
					response = String.format("Put key %s as %s.", keyName, value);
					break;
				default:
					response = "Not implemented";
					break;
				}
			}
			
			return response;
		}
		
		public void run()
		{
			System.out.println("Waiting for connections...");
			while(SOCKETS && !stopServer)
			{
				boolean hasClient=connectToClient();
				
				if(hasClient)
				{
					//System.out.printf("Connected to client on %d.%n", client.getPort());
					
					boolean communicating=true;
					
					String currentInputLine;

					String response = "OK"; // The default response is "OK".
					
					try
					{
						int lineNumber = 0;
						
						//char inputBuffer[] = new char[999];
						
						while(communicating && lineNumber < 1)
						{
							lineNumber++;
							
							// Get a line of input.
							currentInputLine = input.readLine();
							
							// If null, stop.
							if(currentInputLine != null)
							{
								// Find the property or command portion.
								String[] commandParts = currentInputLine.split(" ");
								
								// Find the command portion of the command parts.
								String command = commandParts[0];
								
								// Process the command (JDK7 Strings work in switch statements).
								response = handleServerCommand(currentInputLine);
							}
							else
							{
								communicating = false;
								break;
							}
						}
					}
					catch(Exception e)
					{
						logError(e);
					}
					
					output.println(response);
					
					try
					{
						output.close();
						input.close();
						client.close();
					}
					catch(Exception e)
					{
						logError(e);
					}
				} // End if(hasClient)
			} // End while(SOCKETS).
			System.out.println("Quit server.");
		}
	}
	
	/**
	 *  Start and open the socket server.
	 */
	private void openServer()
	{
		try
		{
			server = new ServerSocket(PORT_NUMBER);
		}
		catch(IOException e)
		{
			PORT_NUMBER++;
			
			System.out.printf("Port changed to %d", PORT_NUMBER);
			
			openServer();
		}
	}
	
	
	// Construct.
	public VisionCommunicator()
	{
		// If using sockets,
		if(SOCKETS)
		{
			System.out.println("Starting server...");
			
			// Open the server.
			openServer();
			
			// Start the thread.
			Thread serverThread = new Thread(new Server(server));
			
			serverThread.setDaemon(true); // The thread will exit when user threads do.
			
			serverThread.run(); // Run the thread.
			
			System.out.println("The server is running...");
		}
		else
		{
			System.out.println("Using network tables.");
			table=NetworkTable.getTable("visionTable");
		}
		
	}
	
	public void stop()
	{
		stopServer = true;
		
		System.out.println("Stopping server...");
		
		if(SOCKETS)
		{
			try 
			{
				Socket connection = new Socket(server.getInetAddress().getHostAddress(), PORT_NUMBER);
				
				PrintWriter output = new PrintWriter(connection.getOutputStream(), true); // True is for autoflush.
				output.println("quit");
				output.close();
				
				connection.close();
				server.close();
			} 
			catch (IOException e)
			{
				logError(e);
			}
		}
	}
	
	public double getAngleToObject()
	{
		double result = 0.0;
		
		if(SOCKETS)
		{
			synchronized(visionInformation)
			{
				result = visionInformation.getDouble("xRotation");
			}
		}
		else
		{
			result = table.getNumber("xRotation", 0.0);
		}
		
		return result;
	}
	
	public String getStringFromJetson(String key)
	{
		String result;
		
		if(SOCKETS)
		{
			synchronized(visionInformation)
			{
				result = visionInformation.getString(key);
			}
		}
		else
		{
			result = table.getString(key, "");
		}
		
		return result;
	}
}
