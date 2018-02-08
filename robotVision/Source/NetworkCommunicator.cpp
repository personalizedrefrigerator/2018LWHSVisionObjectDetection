#include "NetworkCommunicator.h"


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
