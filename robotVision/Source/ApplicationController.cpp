#include "ApplicationController.h"

// Other headers.
#include<iostream>
#include<sstream>

// String to int, etc.
#include<cstdlib>

// OpenCV headers.
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>

// Headers from this program.
#include "CameraFilter.h"
#include "ShapeDetector.h"
#include "CameraOptionsTrackbarManager.h"

// Construct.
ApplicationController::ApplicationController()
{
	
}

// Set whether the UI should be shown.
void ApplicationController::setShowUserInterface(bool shouldShowUI)
{
	showUI=shouldShowUI;
}

// Set the camera number.
void ApplicationController::setCameraNumber(unsigned int newCameraNumber)
{
	cameraNumber=newCameraNumber;
	cameraNumberSet=true;
}

// Set whether this application should log information to the console.
void ApplicationController::setLogInformation(bool shouldLogInfo)
{
	logInfo=shouldLogInfo;
}

// Set the stream to log output to.
void ApplicationController::setOutputStream(std::ostream * newOutput)
{
	outputStream=newOutput;
}

// Log output, if specified.
void ApplicationController::logOutput(std::string output)
{
	if(logInfo)
	{
		(*outputStream) << output;
	}
}

// Run the main application loop. TODO: Allow this to be better changed from outside the class.
void ApplicationController::mainLoop()
{
	// If the camera number has not been explicitly set,
	if(!cameraNumberSet)
	{
		// Request the camera number.
		std::cout << "Camera number: ";

		// Create a variable to store the string version of the camera number.
		std::string cameraNumberResponse;
		std::cin >> cameraNumberResponse;

		cameraNumber=atoi(cameraNumberResponse.c_str());
	}

	// Create a filter.
	CameraFilter filter=CameraFilter(cameraNumber);
	
	logOutput("Attempting to access camera ");

	std::stringstream cameraNumberString;
	cameraNumberString << cameraNumber;

	logOutput(cameraNumberString.str());
	logOutput("\n");

	// Open a camera.
	cv::VideoCapture video;
	video.open(cameraNumber);

	// Create a variable to store the current frame.
	cv::Mat currentFrame;

	// Write to the current frame.
	video >> currentFrame;
	
	// If showing UI,
	if(showUI)
	{
		// Open a window.
		cv::namedWindow("Camera View", cv::WINDOW_AUTOSIZE);
	}

	// Create a trackbar manager.
	CameraOptionsTrackbarManager trackbarManager=CameraOptionsTrackbarManager();

	// Create a variable to store information from the trackbars.
	PlaneDetectorOptions options=PlaneDetectorOptions();
	

	int colorChangeThreshold=(int)options.colorChangeThreshold; 
	int averageChangeThreshold=(int)options.averageChangeThreshold;
	int cornerK=4000,
		cornersToFind=4,
		minCornerDistance=4,
		cornerBlockSize=10,
		cornerHarris=0;
	
	// If a UI should be shown,
	if(showUI)
	{
		trackbarManager.setWindowName("Camera View");

		// Add trackbars.
		trackbarManager.addTrackbar(std::string("Color Change Threshold"), 256, &colorChangeThreshold);
		trackbarManager.addTrackbar(std::string("Average Value Change Threshold"), 256, &averageChangeThreshold);
		trackbarManager.addTrackbar(std::string("Corner K."), 16000, &cornerK);
		trackbarManager.addTrackbar(std::string("Corners to find."), 20, &cornersToFind);
		trackbarManager.addTrackbar(std::string("Minimum corner distance."), 160, &minCornerDistance);
		trackbarManager.addTrackbar(std::string("Corner block size."), 20, &cornerBlockSize);
		trackbarManager.addTrackbar(std::string("Corner harris?"), 1, &cornerHarris);
	}


	// Create a variable to store the last key.
	char lastKey='\0';

	ShapeDetector detector=ShapeDetector();

	Shape mainShape;

	mainShape.setCenterLocation(Point2D(100, 100));

	double rating=-1.0;

	bool foundShape=false;

	// Enter the main loop.
	do
	{
		//logOutput("Starting loop.\n");

		// Load the current image seen by the camera into the current frame.
		video >> currentFrame;
		filter.setData(currentFrame);


		detector.setImage(currentFrame);


		//logOutput("Image set.\n");

		// If showing UI,
		if(showUI)
		{
			options.colorChangeThreshold=(double)colorChangeThreshold;
			options.averageChangeThreshold=(double)averageChangeThreshold;

			
			filter.configureCornerDetection((double)(cornerK/100000.0), cornersToFind+1, minCornerDistance+1, cornerBlockSize+1, (bool)cornerHarris);

			filter.setPlaneDetectorOptions(options);
			detector.setPlaneDetectorOptions(options);
		}
		filter.runAllFilters();		

	
		
		//logOutput("Clearing found...\n");
		detector.clearFoundShapes();
		//logOutput("Done!\n");

		foundShape=true;

		//logOutput("Finding shapes.\n");

		//detector.detectShapes();
		if(!detector.findTargetAndUpdate(mainShape, rating))
		{
			//logOutput("Was false.\n");
			detector.detectShapes();

			//logOutput("Done detecting shapes.\n");

			foundShape=detector.findTargetAndUpdate(mainShape, rating);
			//logOutput("Updated!\n");
		}

		if(foundShape)
		{
			//std::cout << "Starting...\n";
			mainShape.calculateCenterAndOkScreenSize();
			//std::cout << "Ending...\n";



			mainShape.calculateCornersCV();

			//std::cout << "Done calculating corners.\n";

			mainShape.drawDebugOutput(currentFrame);

			//std::cout << "Done drwawing debug output.\n";

		}
		rating=0.21;

		//std::cout << "Imshow.\n";
		
		// If showing UI,
		if(showUI)
		{
			cv::imshow("Camera View", currentFrame);
		}


		//std::cout << "Done.\n";
		
		// Wait at least 1 ms for a key.
		lastKey = cv::waitKey(1);
	} // Stop when 'q' is pressed.
	while(lastKey != 'q');
}
