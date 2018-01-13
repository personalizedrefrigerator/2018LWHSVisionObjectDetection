#pragma once
// Put opperations relating to filtering the camera.
//Henry Heino
#include "


class CameraFilter
{
	public:
	void normalize();
	void setData();
	cv::Mat getData();

	private:
	cv::Mat data;
};
