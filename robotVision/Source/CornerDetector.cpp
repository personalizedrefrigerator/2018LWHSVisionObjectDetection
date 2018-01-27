#include "CornerDetector.h"


// Detect the corners of a shape given in an image, using OpenCV.
void CornerDetector::detectCorners(cv::Mat inputImage)
{
	// Create an array to store the corners found.
	std::vector<cv::Point2f> cornersFound;
	
	// Find the corners.
	cv::goodFeaturesToTrack(grayscaleVersion, cornersFound, cornersToFind, quality, minCornerDistance, cv::Mat(), cornerBlockSize, useCornerHarris, cornerK);
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
