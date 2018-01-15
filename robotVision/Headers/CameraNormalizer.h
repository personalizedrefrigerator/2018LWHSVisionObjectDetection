#pragma once

// Normalize a camera.
// Henry Heino.

// Include opencv libraries.
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>

// Include standard libraries.
#include<string>

// Define the class.
class CameraNormalizer
{
	public:
	void calibrate(bool useUI);
	void calibrate(); // Calibrate, with UI.
	void saveCalibration();
	void normalize(cv::Mat cameraData);
	void setCameraNumber(unsigned int cameraNumber); 
	void setCornerSize(cv::Size cornerSize); // TODO: Implement.

	bool loadData() {}; // TODO: Implement.
	bool loadData(std::string filePathToLoad) {}; // TODO: Implement.
	
	private:
	std::string filePath="cameraConfigurations.txt";
	cv::Mat cameraMatrix;
	cv::Mat distortionCoefficents; // Coeffiecents for calibration (radial and tangental).
					// Used for cv::undistort.
	unsigned int cameraNumber=0; // If not specified, assume the 0th camera (/dev/video0).

	// The number of inner corners of the chessboard. By default, a 9 by 6. This does not count the edges.
	cv::Size cornerSize=cv::Size(9, 6);

	// The rotation vectors.
	std::vector<cv::Mat> rotationVectors;

	// The translation vectors.
	std::vector<cv::Mat> translationVectors;
};
