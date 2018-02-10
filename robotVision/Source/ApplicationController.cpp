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
	std::cout << "Camera number: ";

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
		(*outputStream) << output;
	}
}

// Demo the network tables.
void ApplicationController::demoNetworkTables()
{
	// Create the network table.
	NetworkCommunicator mainCommunicator=NetworkCommunicator("10.58.27.2", "testTable");
	
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
	cv::Mat image1, image2;
	
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
		
		currentFrame=filter1.stitchTwo(image1, image2);
		
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
	// If the camera number has not been explicitly set,
	if(!cameraNumberSet)
	{
		cameraNumber=promptForCamera();
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
	
	video.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	video.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

	// Create a variable to store the current frame.
	cv::Mat currentFrame;

	// Write to the current frame.
	//video >> currentFrame;
	
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
	int minRating=21;
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
		trackbarManager.addTrackbar(std::string("Minimum rating."), 100, &minRating);
		trackbarManager.addTrackbar(std::string("Corner K."), 16000, &cornerK);
		trackbarManager.addTrackbar(std::string("Corners to find."), 20, &cornersToFind);
		trackbarManager.addTrackbar(std::string("Minimum corner distance."), 160, &minCornerDistance);
		trackbarManager.addTrackbar(std::string("Corner block size."), 20, &cornerBlockSize);
		trackbarManager.addTrackbar(std::string("Corner harris?"), 1, &cornerHarris);
	}


	NetworkCommunicator * networkCommunicator; // Create a variable to store the network communicator to be used to communicate with the other parts of the robot.
	
	if(!showUI)
	{
		networkCommunicator=new NetworkCommunicator("10.58.27.2", "Team5827VisionTable");
	}

	// Create a variable to store the last key.
	char lastKey='\0';

	ShapeDetector detector=ShapeDetector();

	Shape mainShape;

	mainShape.setCenterLocation(Point2D(50, 50));

	mainShape.setScreenZ(filter.getNormalizer().getFocalLengthX()); // Set an estimate for the Z position of the screen from the camera.

	double rating=-1.0;

	bool foundShape=false;

	cv::Mat captureData, displayData;

	// Enter the main loop.
	do
	{
		//logOutput("Starting loop.\n");

		// Load the current image seen by the camera into the current frame.
		video >> captureData;
		
		
		
		filter.setData(captureData);
		filter.runAllFilters();	
		
		
		// Resize the input.
		cv::resize(captureData, currentFrame, cv::Size(300, 400));


		detector.setImage(currentFrame);


		//logOutput("Image set.\n");

		// If showing UI,
		if(showUI)
		{
			options.colorChangeThreshold=(double)colorChangeThreshold;
			options.averageChangeThreshold=(double)averageChangeThreshold;

			detector.setPlaneDetectorOptions(options);

			// Configure the corner detection for the main shape's corner detector. A 0.1 quality.
			mainShape.getCornerDetector().setOptions((double)(cornerK/100000.0), cornersToFind+1, minCornerDistance+1, cornerBlockSize+1, (bool)cornerHarris, 0.01);
		}	

	
		
		//logOutput("Clearing found...\n");
		detector.clearFoundShapes();
		//logOutput("Done!\n");

		foundShape=true;

		//logOutput("Finding shapes.\n");

		detector.clearComparisonShapes();
		detector.addComparisonShape(mainShape);

		//detector.detectShapes();
		if(!detector.findTargetAndUpdate(mainShape, rating))
		{
			std::cout << "Rechecking...\n";
			//logOutput("Was false.\n");
			detector.detectAllShapes();

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
			
			// If no UI,
			if(!showUI)
			{
				networkCommunicator->updateValue<double>("RotationDelta", mainShape.getXAngle());
				networkCommunicator->updateValue<double>("Size", mainShape.getContentSize());
			}

			//std::cout << "Done drwawing debug output.\n";

		}
		
		// If looking for rotation, give the rotation.
		

		// Set the rating to the minimum.
		rating=minRating/100.0;

		//std::cout << "Imshow.\n";
		
		// If showing UI,
		if(showUI)
		{
			cv::resize(currentFrame, displayData, cv::Size(400, 400));
			
			cv::imshow("Camera View", displayData);
		}


		//std::cout << "Done.\n";
		
		// Wait at least 1 ms for a key.
		if(showUI)
		{
			lastKey = cv::waitKey(1);
		}
	} // Stop when 'q' is pressed.
	while(lastKey != 'q');
}
