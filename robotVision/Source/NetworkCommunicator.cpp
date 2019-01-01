#include "NetworkCommunicator.h"

// Include the configuration information header.
#include "CMakeConfigurationInformation.h"

// Error management & logging
#include <Logging.h>

#ifdef USE_WPILIB

#include "ntcore.h"
#include "networktables/NetworkTable.h"

// Construct a new network communicator.
NetworkCommunicator::NetworkCommunicator(std::string serverIP, std::string tableName)
{
	// Create a network table.
	// Put it into client mode.
	NetworkTable::SetClientMode();
	
	// Give it the server IP.
	NetworkTable::SetIPAddress(serverIP.c_str());
	
	// Create the network table
	mainTable=NetworkTable::GetTable(tableName);
}

// See NetworkCommunicator.h for templated functions.

// If not using wpilib...
// Use sockets!
#else

// File controls (Linux).
#include <unistd.h> // Gives close, write, read, etc.

// Construct the network communicator.
//The socket should be created here. If unable to connect to the roboRIO,
//this should be noted and a connection should be later attempted.
NetworkCommunicator::NetworkCommunicator(const std::string& serverIp, const std::string& initialTableName)
{
	serverLocation = serverIp;
	tableName = initialTableName;
}

NetworkCommunicator::~NetworkCommunicator()
{
	if(socketOpen)
	{
		close(socketFileDescriptor);
		socketOpen = false;
	}
}

// Create a socket client to handle network communication with the 
//server (running on the RoboRIO).
// Socket refrences:
// * http://www.linuxhowtos.org/C_C++/socket.htm.
// * The Linux Programmer's Manual entry for bind: man bind
// * The Linux Programmer's Manual entry for connect: man connect
// The Linux Programmer's Manual can be found at
//  https://www.kernel.org/doc/man-pages/
bool NetworkCommunicator::openSocket()
{
	// The location of this code is stored in a local string variable, to be
	//given to Logging::error for debugging purposes when an error occurs.
	//Please change this location if this section of the program is moved.
	std::string debugLocation = "NetworkCommunicator.cpp (NetworkCommunicator::NetworkCommunicator)";

	// Clean up if the socket was previously opened.
	if(socketOpen)
	{
		close(socketFileDescriptor);
		socketOpen = false;
	}

	// Danger! This assumes compilation and execution on Linux!
	// A protocol of zero means to auto-infer the protocol.
	// Domain: AF_INET.
	// Type: SOCK_STREAM.
	// Protocol: 0
	socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);

	// Check for errors. If the socket file descriptor is
	//negative, an error has occured (stored in errno).
	//Here, we note an error, using the elsewhere-defined
	//error logging method.
	if(socketFileDescriptor < 0)
	{
		// Note: Logging::error is designed to give errno information
		// (In C, socket(...) stores potential errors in the global errno
		// variable).
		Logging::error("This error occured inside " + debugLocation + ".", 
			std::string {"socket(...) returned a negative integer. Error opening the client socket inside the non-wpilib portion of "} + 
			std::string {"NetworkCommunicator."}, "Another program is blocking socket connections, invalid socket inputs.");

		// Returning false means failure.
		return false;
	}

	// The socket is now open. Allow it to be cleaned up.
	socketOpen = true;

	// The function, gethostbyname, is from C, so serverIp
	//needs to be converted into a "const char *" to be 
	//used. Variable serverHost is a member-variable of
	//a NetworkCommunicator instance.
	serverHost = gethostbyname(serverLocation.c_str());

	// BAD C-style memory clear. TODO Change this c-style clear.
	//Research whether a "serverAddress = 0" will work for this.
	memset(&serverAddress, 0, sizeof(serverAddress));

	// Put information about the server's address in a structure to
	//be used by connect(int, sockaddr*, some_length_type).
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port); // htons converts the port 
										// to big-endian byte order:
										// the highest order bit is
										// stored at the memory
										// location -- it converts the
										// port to network byte order.
										//Ref: www.linuxhowtos.org/
										//data/6/byteorder.html
	
	serverAddress.sin_addr = *((struct in_addr *) serverHost->h_addr);
	
	Logging::log("Waiting to connect to server...");

	// Connect returns -1 on failure and zero on success.
	int connectResult = connect(socketFileDescriptor, 
		(sockaddr *) &serverAddress, sizeof(serverAddress));

	Logging::log("Connected.");

	// On failure, log debug information.
	//This might break during competition, so the debug
	//message should contain detailed information,
	//including related variable states.
	if(connectResult < 0)
	{
		std::stringstream errorDescription;
		errorDescription << "Port: " << port << ". Host: " << serverHost->h_addr;

		// A location, description, and possible causes are given to Logging::error to aid the user in debugging.
		Logging::error("From the check ensuring connectResult >= 0, attempting to connect to a socket in " + debugLocation + ".",
		 errorDescription.str(), std::string {"The RoboRIO may not be turned on, the router may not be connected to this device or the RoboRIO, or the RoboRIO's"} +
		 std::string { " server has not started (this program started before the RoboRIO's)." });

		// Note failure.
		return false;
	}

	// Note success.
	return true;
}

// Send raw data accross the network. This function is private
//as it will not be defined for the WPILib implementation.
bool NetworkCommunicator::sendData(const std::string& dataToSend)
{
	// If a socket isn't already open, open one.
	if(!socketOpen)
	{
		bool success = openSocket(); // Open socket will note that a socket opens should it succeed.

		// Explain the error if the socket was not opened. The function, openSocket,
		//should explain the error, but this output can be used to determine which method calls
		//caused the error (if any), or when in the program's execution the error occured.
		if(!success)
		{
			Logging::error("From NetworkCommunicator::sendData.",
				"Error opening socket, attempting to send " + dataToSend
				 + ". This will be a secondary error message. The socket failed to open or connect.", 
				"This may have been caused by server inavailability or an incorrect hostname/port. Hostname: "
				 + serverLocation + ". Table location: " + tableName + ".");

			return false; // Note this method's failure.
		}
	}

	int writeResult = write(socketFileDescriptor, dataToSend.c_str(), 
			dataToSend.length() * sizeof(dataToSend.at(0))); // std::string is by default a std::basic_string<char>.
															// .at(0) is used to ensure the size of the data to send
															// matches the type of character to be used.
	// If writeResult is -1: The write failed. Log this.
	if(writeResult < 0)
	{
		Logging::error("From NetworkCommunicator::sendData, error writing data.", 
			"Attempted to send: " + dataToSend + " to " + serverLocation + " on table "
			 + tableName + ". Write failed.", 
		 	"The provided length may not match the length of the data to send or the socket may not have been opened properly.");
		
		return false;
	}

	return true;
}

// Reads chunkSize characters
//from the network.
std::string NetworkCommunicator::readData()
{
	// Open a socket if not already open.
	if(!socketOpen)
	{
		bool opened = openSocket();

		if(!opened)
		{
			Logging::error("From NetworkCommunicator::readData().", 
				"Call to openSocket() failed. Attempting to contact " + serverLocation + " at table " + tableName + ".",
				"The server may have been unreachable.");
			return "\0";
		}
	}

	char buffer[chunkSize];

	int readResult = read(socketFileDescriptor, buffer, chunkSize);

	if(readResult < 0)
	{
		Logging::error("From NetworkCommunicator::readData().",
			"Unable to read data. Attempting to contact " + serverLocation + " at table " + tableName + ".",
			"The socket may not have connected to the server.");
	}

	return std::string {buffer};
}

// Get or set a segement of the table. Variable valueToSet is only used if accessing is true.
std::string NetworkCommunicator::getOrSetTableSegement(const std::string& keyName, bool accessing, const std::string& valueToSet)
{
	// Open a socket if not already open.
	if(!socketOpen)
	{
		bool opened = openSocket();

		if(!opened)
		{
			Logging::error("From NetworkCommunicator::getOrSetTableSegement(" + keyName + ").", 
				"Call to openSocket() failed. Attempting to contact " + serverLocation + " at table " + tableName + ".",
				"The server may be unreachable or the socket failed to open. Check network communications.");
			return "\0";
		}
	}

	bool success;

	// Send data to get or set a variable.
	if(!accessing)
	{
		success = sendData("SET " + tableName + " " + keyName + "=" + valueToSet + ";");
	}
	else
	{
		success = sendData("GET " + tableName + " " + keyName + ";");
	}

	// If sending the request failed,
	if(!success)
	{
		std::stringstream informationStream;
		informationStream << keyName << ", " << accessing << ", " << valueToSet;

		Logging::error("From NetworkCommunicator::getOrSetTableSegement(" + informationStream.str() + ").",
			"Error sending data.", "Write error / connection error.");

		if(!accessing)
		{
			return "Failure";
		}
	}

	// Get and return the server response.
	std::string response = readData();
	return response;
}

// Using NetworkCommunicator::getOrSetTableSegement, find the contents of a section of the table.
std::string NetworkCommunicator::getTableSegement(const std::string& keyName)
{
	std::string result = getOrSetTableSegement(keyName, true, ""); // Access at keyName.
}

// Using NetworkCommunicator::getOrSetTableSegement, set a section of a table.
void NetworkCommunicator::setTableSegement(const std::string& key, const std::string& value)
{
	getOrSetTableSegement(key, false, value);
}

// Look in NetworkCommunicator.h for the definitions of templated functions.
#endif