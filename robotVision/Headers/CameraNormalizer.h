#pragma once

// Normalize a camera -- use OpenCV to
//normalize a camera.

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

	bool loadData();
	bool loadData(std::string filePathToLoad) {}; // TODO: Implement.
	
	double getFocalLengthX(); // Get the X portion of the focal length stored in the camera matrix.
	double getFocalLengthY(); // Get the Y component of the focal length stored in the camera matrix.
	void setImageSize(cv::Size newSize); // Set the image size to expect. This is used in calibration.

	bool setConfigurationURLBasedOnCameraNumber(); // Returns whether the name changed.
	
	private:
	std::string filePath="cameraConfiguration.txt";
	cv::Mat cameraMatrix;
	cv::Mat distortionCoefficents; // Coeffiecents for calibration (radial and tangental).
					// Used for cv::undistort.
	unsigned int cameraNumber=0; // If not specified, assume the 0th camera (/dev/video0).
	cv::Size imageSize=cv::Size(300, 300); // The image size to expect for calibration.

	// Serialize a matrix.
	std::string serializeMatrix(cv::Mat input); // TODO: Move this to a different class.

	// Recall a serialized matrix.
	cv::Mat recallSerializedMatrix(std::string input); // TODO: Move this to a different class.

	// Store and recall serialized sizes.
	std::string serializeSize(cv::Size input);
	cv::Size recallSerializedSize(std::string size);

	// The number of inner corners of the chessboard. By default, a 9 by 6. This does not count the edges.
	cv::Size cornerSize=cv::Size(9, 6);

	// The rotation vectors.
	std::vector<cv::Mat> rotationVectors;

	// The translation vectors.
	std::vector<cv::Mat> translationVectors;
};
