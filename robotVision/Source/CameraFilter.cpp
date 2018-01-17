#include "CameraFilter.h"

// Construct a filtering object.
CameraFilter::CameraFilter(unsigned int cameraNumber)//cv::Mat startingData, unsigned int cameraNumber)
{
	//data=startingData;

	normalizer.setCameraNumber(cameraNumber);
	bool couldLoadData=normalizer.loadData();
	
	// If a file containing the calibration data couldn't be found,
	if(!couldLoadData)
	{
		// Calibrate and save.
		normalizer.calibrate();
		normalizer.saveCalibration();
	}
}

// Set the camera's data.
void CameraFilter::setData(cv::Mat data)
{
	this->data=data;
}

// Correct errors in the camera.
void CameraFilter::normalize()
{
	normalizer.normalize(data);
}

// Run cornerHarris to detect corners.
void CameraFilter::cornerHarris()
{
	// Learning to use cornerHarris, see
	// https://docs.opencv.org/master/d4/d7d/tutorial_harris_detector.html

	// Create matricies for output.
	cv::Mat grayscaleVersion, result, normalResult, scaled;

	// Convert camera data to grayscale.
	cvtColor(data, grayscaleVersion, cv::COLOR_BGR2GRAY);
	result=cv::Mat::zeros(grayscaleVersion.size(), CV_64F);

	// Run cornerHarris to detect corners, 8x8 search region per pixel.
	cv::cornerHarris(grayscaleVersion, result, 8, 5, 0.01, cv::BORDER_DEFAULT);

	// Normalize the result.
	cv::normalize(result, normalResult, 0, 255, cv::NORM_MINMAX, CV_64F, cv::Mat());
	//cv::convertScaleAbs(normalResult, scaled); // Make 8 bit unsigned ints.
	//normalResult=result;

	// Take the average.
	double avg=0.0;
	int count=0;
	for(int y=0; y<normalResult.rows; y++)
	{
		for(int x=0; x<normalResult.cols; x++)
		{
			avg+=normalResult.at<double>(y, x);
			count++;
		}
	}
	avg/=count;

	// For each potential corner,
	int x;
	for(int y=0; y<normalResult.rows; y++)
	{
		for(x=0; x<normalResult.cols; x++)
		{
			if((int)normalResult.at<double>(y, x) > avg*1.05)
			{
				// Draw a circle.
				cv::circle(data, cv::Point(x, y), 1, cv::Scalar(0, 200, 100, 200), 1, 8, 0); // 8 is line type.
			}
		}
	}
}

// Detect corners.
void CameraFilter::detectCorners()
{
	// Define matricies.
	cv::Mat grayscaleVersion;

	// Convert camera data to grayscale.
	cvtColor(data, grayscaleVersion, cv::COLOR_BGR2GRAY);

	// Create an array to store the corners found.
	std::vector<cv::Point2f> cornersFound;
	
	// Find the first 40 corners.
	cv::goodFeaturesToTrack(grayscaleVersion, cornersFound, 100, 0.01, 1, cv::Mat(), 8, 5, false, 0.03);

	// For each corner,
	for(unsigned int i=0; i<cornersFound.size(); i++)
	{
		// Draw a circle.
		cv::circle(data, cornersFound.at(i), 4, cv::Scalar(0, 100, 200, 200), 1, 8, 0); // 8 is line type.
	}
}

// Erode and dilate the camera input.
void CameraFilter::erodeAndDilate()
{
	cv::Mat erodeDilateElement=cv::getStructuringElement(cv::MORPH_RECT, 
			cv::Size(5, 5)); // Change the size to emphasize different shapes.
	
	// Erode and dilate
	cv::erode(data, data, erodeDilateElement,
			cv::Point(-1, -1), 1); // An anchor of nowhere and 1 iteration.
		cv::dilate(data, data, erodeDilateElement,
			cv::Point(-1, -1),  1); // An anchor of nowhere and 1 iteration.
}

// Run all camera filters.
void CameraFilter::runAllFilters()
{
	normalize();
	erodeAndDilate();
	//detectCorners();
	cornerHarris();
}
