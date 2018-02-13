#include "CornerDetector.h"




// Detect the corners of a shape given in an image, using OpenCV.
std::vector<Point2D> CornerDetector::detectCorners(cv::Mat inputImage)
{
	// Create an array to store the corners found.
	std::vector<cv::Point2f> cornersFound;

	cv::Mat inputImage2;

	// Convert the input to grayscale.
	cvtColor(inputImage, inputImage2, cv::COLOR_BGR2GRAY);

	// Find the corners.
	cv::goodFeaturesToTrack(inputImage2, cornersFound, cornersToFind, quality, minCornerDistance, cv::Mat(), cornerBlockSize, useCornerHarris, cornerK);
	
	// Convert the array of found corners into an array of Point2Ds.
	std::vector<Point2D> result;
	
	cv::Point2f currentPoint;
	
	
	unsigned int cornersIndex;
	for(cornersIndex=0; cornersIndex<cornersFound.size(); cornersIndex++)
	{
		currentPoint=cornersFound.at(cornersIndex);
		result.push_back(Point2D(currentPoint.x, currentPoint.y));
	}
	
	return result;
}

// Set options relating to corner detection.
void CornerDetector::setOptions(double k, int cornersToFind, int minCornerDistance, int cornerBlockSize, bool useCornerHarris, double quality)
{
	this->cornerK=k;
	this->cornersToFind=cornersToFind;
	this->minCornerDistance=minCornerDistance;
	this->cornerBlockSize=cornerBlockSize;
	this->useCornerHarris=useCornerHarris;
	this->quality=quality;
}
