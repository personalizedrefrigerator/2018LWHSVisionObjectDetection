// Include the header file for the trackbar manager.
#include "CameraOptionsTrackbarManager.h"

// Crete a trackbar in the set window.
void CameraOptionsTrackbarManager::addTrackbar(std::string label, int maximum, int * valueToModify)
{
	cv::createTrackbar(label, windowName, valueToModify, maximum, onTrackbarChange);
}

// Change the name of the window to add trackbars to.
void CameraOptionsTrackbarManager::setWindowName(std::string name)
{
	this->windowName=name;
}
