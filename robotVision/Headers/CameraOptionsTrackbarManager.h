#pragma once

// Include standard libraries.
#include<string>

// Import OpenCV librarues.
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>

// Define the class.
class CameraOptionsTrackbarManager
{
	public:
	void addTrackbar(std::string label, int maximum, int * modify); // Add a new trackbar to the window.
	void setWindowName(std::string windowName);

	private:
	std::string windowName; // The name of the window to display the trackbar on.
	static void onTrackbarChange(int, void*) {}; // A function to be called on trackbar change.

};
