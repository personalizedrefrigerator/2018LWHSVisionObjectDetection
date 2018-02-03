#pragma once
// Filter input from a camera.
//Henry Heino

// Include opencv libraries.
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/stitching.hpp>

// Include the camera normalizer (for correcting camera errors).
#include "CameraNormalizer.h"

// Include the plane detector.
#include "PlaneDetector.h"

#include<vector>


class CameraFilter
{
	public:
	~CameraFilter();
	
	void normalize();
	void erodeAndDilate();
	void erodeAndDilate(cv::Mat image, unsigned int recursions);
	void cornerHarris();
	void detectCorners();
	void detectLineSegments();
	void showPlane();
	void tier(int multiplier);
	
	void runAllFilters();
	
	CameraNormalizer & getNormalizer();
	
	cv::Mat stitch(std::vector<cv::Mat> inputs);
	cv::Mat stitchTwo(cv::Mat input1, cv::Mat input2); // Stitch just two images together.

	void setPlaneDetectorOptions(PlaneDetectorOptions options);

	void setData(cv::Mat); // cv::Mat does not store the matrix data, but a pointer/refrence to it! This does not copy the entire image.
	cv::Mat getData();

	CameraFilter(unsigned int cameraNumber);

	void configureCornerDetection(double k, int cornersToFind, int minCornerDistance, int cornerBlockSize, bool useCornerHarris); 

	private:
	cv::Mat data;
	
	bool stitcherMade=true;
	cv::Stitcher stitcher=cv::Stitcher::createDefault();

	bool normalized=false;
	CameraNormalizer normalizer=CameraNormalizer();
	PlaneDetector planeDetector=PlaneDetector();


	double cornerK=0.04;
	int cornersToFind=4, minCornerDistance=4, cornerBlockSize=9;
	bool useCornerHarris=false;
};
