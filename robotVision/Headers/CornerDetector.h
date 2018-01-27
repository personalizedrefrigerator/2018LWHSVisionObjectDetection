#pragma once

// Include opencv libraries.
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>

#include "Point2D.h"
#include <vector>

class CornerDetector
{
	public:
	std::vector<Point2D> detectCorners(cv::Mat grayscaleInputImage);
	
	void setOptions(double k, int cornersToFind, int minCornerDistance, int cornerBlockSize, bool useCornerHarris, double quality);
	
	private:
	double cornerK=0.04, quality=0.01;
	int cornersToFind=4, minCornerDistance=4, cornerBlockSize=9;
	bool useCornerHarris=false;
};
