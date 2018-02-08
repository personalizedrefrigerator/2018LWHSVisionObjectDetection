#pragma once

// Include network tables libraries.
#include "ntcore.h"
#include "networktables/NetworkTable.h"

// Include the string libarary.
#include <string>

// Standard shared pointer library.
#include <memory>

// A class to communicate information from this vision program over the network.
//Henry Heino

class NetworkCommunicator
{
	public:
	static const int defaultValue=0;
	
	NetworkCommunicator(std::string serverIP, std::string tableName);
	
	template <typename T>
	void updateValue(std::string key, T value);
	
	template <typename T>
	T getValue(std::string key);
	
	private:
	// A variable to store the network table.
	std::shared_ptr<NetworkTable> mainTable;
};




// These functions are in the header due to linker properties.

// Update a value in the network table.
template <typename T>
void NetworkCommunicator::updateValue(std::string key, T value)
{
	mainTable->PutNumber(key, value);
}

// Get a value from the network table.
template <typename T>
T NetworkCommunicator::getValue(std::string key)
{
	// TODO: Replace this c style cast with a static_cast<T>.
	return (T)(mainTable->GetNumber(key, defaultValue));
}
