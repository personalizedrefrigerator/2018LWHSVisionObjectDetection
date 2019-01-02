#pragma once

// Include the configuration information header.
#include "CMakeConfigurationInformation.h"

// Include the string libarary.
#include <string>

// Standard library string building.
#include <sstream> // Contains std::stringstream

// Standard shared pointer library.
#include <memory>

// Other standard library headers.
#include <unordered_map>

// If using WPILib,
#ifdef USE_WPILIB

	// Include network tables libraries.
	#include "ntcore.h"
	#include "networktables/NetworkTable.h"

	// A class to communicate information from this vision program over the network.

	class NetworkCommunicator
	{
		public:
		static const int defaultValue=0;
		
		NetworkCommunicator(std::string serverIP, std::string tableName);
		
		template <typename T>
		void updateValue(const std::string& key, T value);
		
		template <typename T>
		T getValue(const std::string& key);

		std::string getStringValue(const std::string& key);
		
		private:
		// A variable to store the network table.
		std::shared_ptr<NetworkTable> mainTable;
	};




	// These functions are in the header due to linker properties.

	// Update a value in the network table.
	template <typename T>
	void NetworkCommunicator::updateValue(const std::string& key, T value)
	{
		mainTable->PutNumber(key, value);
	}

	// Get a value from the network table.
	template <typename T>
	T NetworkCommunicator::getValue(const std::string& key)
	{
		// TODO: Replace this c style cast with a static_cast<T>.
		return static_cast<T>(mainTable->GetNumber(key, defaultValue));
	}

	// Get a string value from the network table.
	template <typename T>
	T NetworkCommunicator::getStringValue(const std::string& key)
	{
		return mainTable->GetString(key, defaultValue);
	}
#else
	// Otherwise, use sockets!

	// Memory management
	#include <memory> // shared_ptr and unique_ptr

	#include <set> // Standard sets. Used for a list of modified keys.

	// Threading.
	#include <thread>
	#include <mutex> // Allows resource locking for thread saftey.
					 // Note that multiple reads at the same time are okay, but not writes.
	#include <condition_variable> 	// Event support for threading see 
									//"A Tour of C++" by Bjarne Stroustrup page 146.
	
	// Linux headers.
	#include <sys/types.h>
	#include <netinet/in.h> // Defines sockaddr_in.
	#include <netdb.h>	// Defines hostent. Hostent is a struct
						// that stores server info.
	#include <sys/socket.h> // Socket library.
	#include <errno.h>

	class NetworkCommunicator
	{
		private:
		// All data is internally stored as strings.
		std::mutex dataLock; // This lock is for data and modifiedList.
		std::unordered_map<std::string, std::string> data;
		std::set<std::string> modifiedList; // A list of keys that have been modified.
		std::condition_variable conditionVarSyncData; 	// Used to notify the socket thread
														//of a need to update data.

		// Socket data.
		int socketFileDescriptor; // Used to access the socket.
		sockaddr_in serverAddress; // Server information.
		hostent * serverHost; // More server information.
		std::string serverLocation; // Server location.
		std::string tableName;
		bool socketOpen = false;

		// Theading
		void startCommunicationThread();
		void communicationThreadFunction();
		std::unique_ptr<std::thread> communicationThread;

		bool sendData(const std::string& dataToSend); // Send data accross the network.

		std::string readData(); // Read data from the network. Reads chunkSize characters.

		// Danger! These network functions to be used only on the socket's thread.
		//These involve waiting for the server, which should not be done on the client thread.
		std::string getOrSetNetworkTableSegement(const std::string& keyName, bool accessing,	// Internal. To be used to facilitate implementation of
			const std::string& valueToSet);												//getTableSegement and setTableSegement.
																													
		std::string getNetworkTableSegement(const std::string& keyName); // Read data from the table using a given key.
		void setNetworkTableSegement(const std::string& keyName, const std::string& value); // Put string data into the table.

		bool openSocket(); 	// Attempt to open a Linux socket to be used for communication. Returns success/failure.
							// Status is saved in an instance of the NetworkCommunicator class.

		bool closeSocketIfOpen();

		bool getDataUpdateNeeded(); // Determines whether server data must be updated.

		// Main/not socket thread functions.
		std::string getTableSegement(const std::string& keyName);
		void setTableSegement(const std::string& keyName, const std::string& value);
		void noteDataUpdateNeeded(); // Set that a data update is needed.


		bool useNetwork = true; // Allows networking to be turned on and off. Should only be changed on construction and deconstruction.
		bool dataUpdateNeeded = false;

		// Constants.
		static const int defaultValue=0;
		static const unsigned int chunkSize = 1024;
		static const unsigned int port = 4342; 	// This port should not need to change --
												//but it should be tested to ensure that
												//a deploy and disable do not leave a
												//port unopenable as a socket server 
												//runing on linux in C++ can.
												//TODO: Put test results here.

		public:

		// For compatability with the WPILib version of this class,
		//this constructor does NOT take the port to connect to as
		//an argument.
		NetworkCommunicator(const std::string& serverIP, const std::string& tableName);
		~NetworkCommunicator();
		
		// TODO: To avoid waiting, start a separate thread to 
		//send results to the roboRIO.
		
		template <typename T>
		void updateValue(const std::string& key, T value)
		{
			if(useNetwork)
			{
				std::stringstream stringGenerator;
				stringGenerator << value;

				setTableSegement(key, stringGenerator.str());
			}
		};
		
		template <typename T>
		T getValue(const std::string& key)
		{
			if(useNetwork)
			{
				std::string value = getTableSegement(key);

				return T(std::stod(value));
			}
			else
			{
				return T (0.0);
			}
		};

		std::string getStringValue(const std::string& key)
		{
			if(useNetwork)
			{
				std::string value = getTableSegement(key);

				return value;
			}
			else
			{
				return "";
			}
		};
	};

#endif // End the using non-wpilib if.
