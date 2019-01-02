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
	
	private VisionOutput visionInformation = new VisionOutput();
	
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
		
		// Log an error to the console.
		public void logError(Exception error)
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
		
		public void run()
		{
			while(SOCKETS)
			{
				System.out.println("Waiting for connections...");
				boolean hasClient=connectToClient();
				System.out.println("Connected or error.");
				
				if(hasClient)
				{
					System.out.printf("Connected to client on %d.%n", client.getPort());
					
					boolean communicating=true;
					
					String currentInputLine;
					
					try
					{
						int lineNumber = 0;
						
						//char inputBuffer[] = new char[999];
						
						while(communicating && lineNumber < 1)
						{
							lineNumber++;
							
							// Get a line of input.
							currentInputLine = input.readLine();
							//input.read(inputBuffer, 0, inputBuffer.length);
							
							//currentInputLine = charArrayToString(inputBuffer);
							
							System.out.println(currentInputLine);
							
							// If null, stop.
							if(currentInputLine != null)
							{
								// Find the property or command portion.
								String[] commandParts = currentInputLine.split(" ");
								
								// Find the command portion of the command parts.
								String command = commandParts[0];
								
								// Process the command (JDK7 Strings work in switch statements).
								switch(command)
								{
								case "quit":
									communicating = false;
									break;
								case "setObjectRotation":
									
									double angle=0.0;
									if(commandParts.length >= 2)
									{
										try
										{
											angle = Double.parseDouble(commandParts[1]);
											
											synchronized(visionInformation)
											{
												visionInformation.setAngleToObject(angle);
											}
										}
										catch(Exception e)
										{
											logError(e);
										}
									}
									break;
								default:
									System.out.println("Server command: " + command + ", currentInputLine: " + currentInputLine + ".");
									//Logging.consoleLog("Unknown server command.");	
									break;
								}
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
					
					output.println("OK");
					
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
	
	public double getAngleToObject()
	{
		double result = 0.0;
		
		if(SOCKETS)
		{
			synchronized(visionInformation)
			{
				result = visionInformation.getAngleToObject();
			}
		}
		else
		{
			result = table.getNumber("xRotation", 0.0);
		}
		
		return result;
	}
}
