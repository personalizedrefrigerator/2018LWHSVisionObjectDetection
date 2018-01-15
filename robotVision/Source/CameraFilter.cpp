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

// Run all camera filters.
void CameraFilter::runAllFilters()
{
	normalize();
}
