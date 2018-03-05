#pragma once

// Streams.
#include <iostream>

// Include opencv libraries.
#include<opencv2/opencv.hpp>

// A clas to run and control the application.
//Henry Heino

class ApplicationController
{
	public:
	ApplicationController(); // Make a new ApplicationController.
	void setShowUserInterface(bool); // Set whether the user interface should be shown while running the program.
	void setCameraNumber(unsigned int cameraNumber); // Set the camera to use for the program.
	void setLogInformation(bool logInfo); // Set whether to log information to the console.
	void setOutputStream(std::ostream * newOutput); // Set the output stream.
	void logOutput(std::string output); // Log text to the output stream.
	void setImageSize(cv::Size newSize);

	void mainLoop(); // The main program loop.
	void demoStitcher(); // Demo the image stitcher.
	void demoNetworkTables(); // Demo network tables.
	
	unsigned int promptForCamera(); // Ask the user to select a camera.


	private:
	bool showUI=true; // Whether to show UI.
	unsigned int cameraNumber=1; // The camera number to use.
	bool cameraNumberSet=false; // Whether the client has set the camera number.
	bool logInfo=false; // Whether output should be logged.
	
	cv::Size imageSize=cv::Size(600,600);

	// The stream to log output to.
	std::ostream * outputStream=&(std::cout);
};
