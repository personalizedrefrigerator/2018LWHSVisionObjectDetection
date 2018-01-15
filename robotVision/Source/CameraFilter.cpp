#include "CameraFilter.h"

// Construct a filtering object.
CameraFilter::CameraFilter(unsigned int cameraNumber)//cv::Mat startingData, unsigned int cameraNumber)
{
	//data=startingData;

	//normalizer.setCameraNumber(cameraNumber);
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

// Run other functions.
void CameraFilter::otherFilters()
{
	// Learning to use cornerHarris, see
	// https://docs.opencv.org/master/d4/d7d/tutorial_harris_detector.html
	cv::Mat grayscaleVersion, result, normalResult, scaled;
	cvtColor(data, grayscaleVersion, cv::COLOR_BGR2GRAY);
	result=cv::Mat::zeros(grayscaleVersion.size(), CV_64F);
	cv::cornerHarris(grayscaleVersion, result, 8, 5, 0.01, cv::BORDER_DEFAULT);

	cv::normalize(result, normalResult, 0, 255, cv::NORM_MINMAX, CV_64F, cv::Mat());
	//cv::convertScaleAbs(normalResult, scaled); // Make 8 bit unsigned ints.
	//normalResult=result;
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

	for(int y=0; y<normalResult.rows; y++)
	{
		for(int x=0; x<normalResult.cols; x++)
		{
			if((int)normalResult.at<double>(y, x) > avg*1.1)
			{
				cv::circle(data, cv::Point(x, y), 1, cv::Scalar(0, 100, 100, 200), 1, 8, 0); // 8 is line type.
			}
		}
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
	otherFilters();
}
