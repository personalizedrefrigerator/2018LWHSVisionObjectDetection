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
		return static_cast<T>(mainTable->GetNumber(key, defaultValue));
	}
#else
	// Otherwise, use sockets!

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
		std::unordered_map<std::string, std::string> data;

		// Socket data.
		int socketFileDescriptor; // Used to access the socket.
		sockaddr_in serverAddress; // Server information.
		hostent * serverHost; // More server information.
		std::string serverLocation; // Server location.
		std::string tableName;
		bool socketOpen = false;

		bool sendData(const std::string& dataToSend); // Send data accross the network.

		std::string readData(); // Read data from the network. Reads chunkSize characters.

		std::string getOrSetTableSegement(const std::string& keyName, bool accessing,	// Internal. To be used to facilitate implementation of
			const std::string& valueToSet);												//getTableSegement and setTableSegement.
																													
		std::string getTableSegement(const std::string& keyName); // Read data from the table using a given key.
		void setTableSegement(const std::string& keyName, const std::string& value); // Put string data into the table.

		bool openSocket(); 	// Attempt to open a Linux socket to be used for communication. Returns success/failure.
							// Status is saved in an instance of the NetworkCommunicator class.

		public:
		static const int defaultValue=0;
		static const unsigned int chunkSize = 1024;
		static const bool useNetwork = false;
		static const unsigned int port = 4342; 	// This port should not need to change --
												//but it should be tested to ensure that
												//a deploy and disable do not leave a
												//port unopenable as a socket server 
												//runing on linux in C++ can.
												//TODO: Put test results here.

		// For compatability with the WPILib version of this class,
		//this constructor does NOT take the port to connect to as
		//an argument.
		NetworkCommunicator(const std::string& serverIP, const std::string& tableName);
		~NetworkCommunicator();
		
		// TODO: To avoid waiting, start a separate thread to 
		//send results to the roboRIO.
		
		template <typename T>
		void updateValue(std::string key, T value)
		{
			if(useNetwork)
			{
				std::stringstream stringGenerator;
				stringGenerator << value;

				setTableSegement(key, stringGenerator.str());
			}
		};
		
		template <typename T>
		T getValue(std::string key)
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
	};

#endif // End the using non-wpilib if.
