#pragma once
// Filter input from a camera.
//Henry Heino

// Include opencv libraries.
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>

// Include the camera normalizer (for correcting camera errors).
#include "CameraNormalizer.h"

// Include the plane detector.
#include "PlaneDetector.h"


class CameraFilter
{
	public:
	void normalize();
	void erodeAndDilate();
	void cornerHarris();
	void detectCorners();
	void detectLineSegments();
	void showPlane();
	
	void runAllFilters();

	void setPlaneDetectorOptions(PlaneDetectorOptions options);

	void setData(cv::Mat); // cv::Mat does not store the matrix data, but a pointer/refrence to it! This does not copy the entire image.
	cv::Mat getData();

	CameraFilter(unsigned int cameraNumber);

	private:
	cv::Mat data;

	bool normalized=false;
	CameraNormalizer normalizer=CameraNormalizer();
	PlaneDetector planeDetector=PlaneDetector();
};
