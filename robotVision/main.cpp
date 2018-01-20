#include<iostream>

#include<cstdlib>

// OpenCV headers.
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>

// Headers from this program.
#include "CameraFilter.h"
#include "CameraOptionsTrackbarManager.h"

// Run cmake to compile this for release, as
//cmake ../robotVision -DCMAKE_BUILD_TYPE=Release


// The main method.
int main()
{
	Line testLine=Line(new Point2D(0,0), new Point2D(1, 1));
	std::cout << testLine.getAngle2D();

	// Allocate memory to store the camera number.
 	int cameraNumber=0;


	// Request the camera number.
	std::cout << "Camera number: ";

	// Create a variable to store the string version of the camera number.
	std::string cameraNumberResponse;
	std::cin >> cameraNumberResponse;

	cameraNumber=atoi(cameraNumberResponse.c_str());

	// Create a filter.
	CameraFilter filter=CameraFilter(cameraNumber);
	
	std::cout << "Attempting to access camera " << cameraNumber << '\n';

	// Open a camera.
	cv::VideoCapture video;
	video.open(cameraNumber);

	// Create a variable to store the current frame.
	cv::Mat currentFrame;

	// Write to the current frame.
	video >> currentFrame;
	
	// Open a window.
	cv::namedWindow("Camera View", cv::WINDOW_AUTOSIZE);

	// Create a trackbar manager.
	CameraOptionsTrackbarManager trackbarManager=CameraOptionsTrackbarManager();

	// Create a variable to store information from the trackbars.
	PlaneDetectorOptions options=PlaneDetectorOptions();
	
	trackbarManager.setWindowName("Camera View");

	int colorChangeThreshold=(int)options.colorChangeThreshold; 
	int averageChangeThreshold=(int)options.averageChangeThreshold;
	int significantPointAccuracy=(int)(options.significantPointAccuracy*10);

	// Add trackbars.
	trackbarManager.addTrackbar(std::string("Color Change Threshold"), 256, &colorChangeThreshold);
	trackbarManager.addTrackbar(std::string("Average Value Change Threshold"), 256, &averageChangeThreshold);
	trackbarManager.addTrackbar(std::string("Significant point accuracy."), 100, &significantPointAccuracy);


	// Create a variable to store the last key.
	char lastKey='\0';

	// Enter the main loop.
	do
	{
		video >> currentFrame;
		filter.setData(currentFrame);

		options.colorChangeThreshold=(double)colorChangeThreshold;
		options.averageChangeThreshold=(double)averageChangeThreshold;
		options.significantPointAccuracy=significantPointAccuracy/10.0;

		filter.setPlaneDetectorOptions(options);
		filter.runAllFilters();		

		cv::imshow("Camera View", currentFrame);
		
		// Wait at least 1 ms for a key.
		lastKey = cv::waitKey(1);
	} // Stop when 'q' is pressed.
	while(lastKey != 'q');

	return 0;
}


// The result of learning OpenCV. Change things in this function to quickly test them.
int testCode()
{
	cv::Mat image=cv::Mat::zeros(4, 4, CV_8UC1);
	// Open a window.
	cv::namedWindow("Camera View", cv::WINDOW_AUTOSIZE);

	std::cout << image << "\n";

	// Open a camera.
	cv::VideoCapture video;
	video.open(0);

	// Open a window.
	cv::namedWindow("Camera View", cv::WINDOW_AUTOSIZE);

	// Create a variable to store the current frame.
	cv::Mat currentFrame, lastFrame;

	// Create a variable to store the last key.
	char lastKey='\0';

	video >> lastFrame;
	//currentFrame.copyTo(lastFrame);

	std::vector<cv::Point2f> corners;

	// Calibrate the camera.

	do
	{
		video >> currentFrame;
		//currentFrame=currentFrame.colRange(0,
		//	currentFrame.size().height);
		/*cv::Mat erodeDilateElement=cv::getStructuringElement(cv::MORPH_RECT, 
			cv::Size(20, 1));
		cv::erode(currentFrame, currentFrame, erodeDilateElement,
			cv::Point(-1, -1), 3);
		cv::dilate(currentFrame, currentFrame, erodeDilateElement,
			cv::Point(-1, -1),  3);*/

		int x, y;
		unsigned char * ptr;
		for(y=0; y<currentFrame.rows;y++)
		{
			ptr=currentFrame.ptr<unsigned char>(y);
			for(x=0; x<currentFrame.size().width; x++)
			{
				ptr[x*3]*=y;
			}
		}
		cv::Size cornerSize=cv::Size(9, 6);
		cv::cvtColor(currentFrame, lastFrame, CV_RGB2GRAY);
		bool success=cv::findChessboardCorners(lastFrame, cornerSize, corners, cv::CALIB_CB_FAST_CHECK + cv::CALIB_CB_ADAPTIVE_THRESH + cv::CALIB_CB_NORMALIZE_IMAGE);

		if(success)
		{
			//std::cout << "Found!";
			cv::cornerSubPix(lastFrame, corners, cv::Size(10, 10), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
			cv::drawChessboardCorners(currentFrame, cornerSize, cv::Mat(corners), success);
		}
		cv::imshow("Camera View", currentFrame);

		lastKey = cv::waitKey(1);
		currentFrame.copyTo(lastFrame);
	}
	while(lastKey != 'q');

	return 0;
}
