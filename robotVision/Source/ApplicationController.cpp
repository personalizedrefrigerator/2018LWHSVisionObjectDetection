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
#include "VisionApplication.h"
#include "CameraOptionsTrackbarManager.h"
#include "NetworkVisionOutput.h"
#include "Vector3D.h"

#include "Logging.h"

// Include the network communication class.
#include "NetworkCommunicator.h"

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

// Prompt the user for a camera.
unsigned int ApplicationController::promptForCamera()
{
	// Request the camera number.
	Logging::log << "Camera number: ";

	// Create a variable to store the string version of the camera number.
	std::string cameraNumberResponse;
	std::cin >> cameraNumberResponse;
	
	// Return the integer version.
	return atoi(cameraNumberResponse.c_str());
}

// Log output to the output stream.
void ApplicationController::logOutput(std::string output)
{
	if(logInfo)
	{
		(*outputStream) << output << "\n";
	}
}

// Set the window size to use.
void ApplicationController::setImageSize(cv::Size newSize)
{
	imageSize=newSize;
}

// Demo the network tables.
void ApplicationController::demoNetworkTables()
{
	// Create the network table.
	NetworkCommunicator mainCommunicator { "10.58.27.2", "testTable" };
	
	// Update a value.
	mainCommunicator.updateValue("testValue", 123);
}

// Demo the image stitcher.
void ApplicationController::demoStitcher()
{
	// Request two cameras.
	unsigned int camera1=promptForCamera(),
		camera2=promptForCamera();
		
	// Create filters.
	CameraFilter filter1=CameraFilter(camera1);
	CameraFilter filter2=CameraFilter(camera2);
	
	// Open cameras.
	cv::VideoCapture video1, video2;
	video1.open(camera1);
	video2.open(camera2);

	// Create a variable to store the current frame.
	cv::Mat currentFrame;
	
	// Create variables to store the results from the individual cameras.
	cv::Mat image1, image2, image3, image4;
	
	// If showing UI,
	if(showUI)
	{
		// Open a window.
		cv::namedWindow("Camera View", cv::WINDOW_NORMAL);
	}
	
	// Create a variable to store the last key.
	char lastKey='\0';
	
	// Enter the main loop.
	do
	{
		//logOutput("Starting loop.\n");

		// Load the current image seen by the camera into the current frame.
		video1 >> image1;
		video2 >> image2;
		
		cv::resize(image1, image3, cv::Size(300,300));
		cv::resize(image2, image4, cv::Size(300,300));
		
		currentFrame=filter1.stitchTwo(image3, image4);
		
		// If showing UI,
		if(showUI && currentFrame.rows > 0 && currentFrame.cols > 0)
		{
			cv::imshow("Camera View", currentFrame);
		}
		
		// Wait at least 1 ms for a key.
		lastKey = cv::waitKey(1);
	} // Stop when 'q' is pressed.
	while(lastKey != 'q');
}

// Run the main application loop. TODO: Allow this to be better changed from outside the class.
void ApplicationController::mainLoop()
{
	Vector3D a=(Color(255,100,1)).getVector();
	Logging::log << a.getShadowAngle() << "\n";

	// If the camera number has not been explicitly set,
	if(!cameraNumberSet)
	{
		cameraNumber=promptForCamera();
	}

	// Create a filter.
	CameraFilter filter=CameraFilter(cameraNumber);
	filter.setImageSize(imageSize);
	
	logOutput("Attempting to access camera...");

	// Open the camera.
	cv::VideoCapture video;
	video.open(cameraNumber);

	// Create a variable to store the current frame.
	cv::Mat currentFrame;
	
	// If showing UI,
	if(showUI)
	{
		// Open a window.
		cv::namedWindow("Camera View", cv::WINDOW_AUTOSIZE);
	}

	// Create a trackbar manager.
	CameraOptionsTrackbarManager trackbarManager=CameraOptionsTrackbarManager();

	logOutput("Done! Creating plane detector options.");

	// Create a variable to store information from the trackbars.
	PlaneDetectorOptions options=PlaneDetectorOptions();
	logOutput("Done!");

	int colorChangeThreshold=(int)options.colorChangeThreshold; 
	int averageChangeThreshold=(int)options.averageChangeThreshold;
	int minRating=21, minH=20, maxH=35, minS=93, maxS=256, minV=0, maxV=256;
	/*int cornerK=4000,
		cornersToFind=4,
		minCornerDistance=4,
		cornerBlockSize=10,
		cornerHarris=0;*/
	
	// If a UI should be shown,
	if(showUI)
	{
		trackbarManager.setWindowName("Camera View");

		// Add trackbars.
		trackbarManager.addTrackbar(std::string("Color Change Threshold"), 256, &colorChangeThreshold);
		trackbarManager.addTrackbar(std::string("Average Value Change Threshold"), 256, &averageChangeThreshold);
		trackbarManager.addTrackbar(std::string("Minimum rating."), 100, &minRating);
		trackbarManager.addTrackbar(std::string("minH"), 256, &minH);
		trackbarManager.addTrackbar(std::string("maxH"), 256, &maxH);
		trackbarManager.addTrackbar(std::string("minS"), 256, &minS);
		trackbarManager.addTrackbar(std::string("maxS"), 256, &maxS);
		trackbarManager.addTrackbar(std::string("minV"), 256, &minV);
		trackbarManager.addTrackbar(std::string("maxV"), 256, &maxV);
		/*trackbarManager.addTrackbar(std::string("Corner K."), 16000, &cornerK);
		trackbarManager.addTrackbar(std::string("Corners to find."), 20, &cornersToFind);
		trackbarManager.addTrackbar(std::string("Minimum corner distance."), 160, &minCornerDistance);
		trackbarManager.addTrackbar(std::string("Corner block size."), 20, &cornerBlockSize);
		trackbarManager.addTrackbar(std::string("Corner harris?"), 1, &cornerHarris);*/
	}

	logOutput("Creating network output.");

	NetworkVisionOutput visionAppOutput("10.58.27.2", "visionTable"); // Create a variable to store the output of the vision application. TODO: GET RID OF STATIC IPs.

	logOutput("Done! Creating app parameters.");

	VisionInputParameters visionAppParameters; // Create a variable to store parameters for the vision app.
	
	logOutput("Done! Creating the app.");
	
	// Create the vision application.
	VisionApplication mainApp;
	
	logOutput("Done! Telling information.");
	
	// If showing UI, put the app into debug mode.
	if(showUI)
	{
		mainApp.setShowDebugOutput(true);
	}
	
	logOutput("1");

	// Create a variable to store the last key.
	char lastKey='\0';


	// Set the z distances to the screen accross the x and y axes.
	visionAppParameters.focalLengthX=filter.getNormalizer().getFocalLengthX();
	visionAppParameters.focalLengthY=filter.getNormalizer().getFocalLengthY();

	logOutput("2");

	// Images directly captured, and the image to directly write to the display.
	cv::Mat captureData, displayData;

	logOutput("Done! Entering mainloop.");

	// Enter the main loop.
	do
	{
		// Load the current image seen by the camera into the current frame.
		video >> captureData;
		
		// Resize the input to a reasonable size.
		//cv::resize(captureData, currentFrame, cv::Size(200,200));
		currentFrame=captureData;
	
	
		// Give the image filter the data.
		filter.setData(currentFrame);
		
		filter.hslFilter(minH, maxH, true, minS, maxS, true, minV, maxV, true);
		
		filter.runAllFilters();	// Run its filters, including an image correction, an erosion, and a dilation.


		// If showing UI,
		if(showUI)
		{
			options.colorChangeThreshold=(double)colorChangeThreshold;
			options.averageChangeThreshold=(double)averageChangeThreshold;

			visionAppParameters.surfaceDetectionOptions=options;
			
			visionAppParameters.worstMatchRating=minRating/100.0;

			//mainShape.getCornerDetector().setOptions((double)(cornerK/100000.0), cornersToFind+1, minCornerDistance+1, cornerBlockSize+1, (bool)cornerHarris, 0.01);
		}

		// Run the vision application.
		mainApp.runFrame(currentFrame, visionAppOutput, visionAppParameters);

		// If showing UI,
		if(showUI)
		{
			// Resize the image output to fit on the screen.
			cv::resize(currentFrame, displayData, imageSize);
			
			// Show this image.
			cv::imshow("Camera View", displayData);
		
			// Wait at least 1 ms for a key.
		
			lastKey = cv::waitKey(1);
		}
	} // Stop when 'q' is pressed.
	while(lastKey != 'q');
}
