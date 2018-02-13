#include "CameraNormalizer.h"

// Include opencv libraries.
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>

// Include serialization libraries.
#include "Serialize.h"

// Include file access libraries.
#include<fstream>

// Include stringstream libraries.
#include<sstream>

// Set the camera numbe to be used.
void CameraNormalizer::setCameraNumber(unsigned int cameraNumber)
{
	this->cameraNumber=cameraNumber;
}

// Set the image size to expect.
void CameraNormalizer::setImageSize(cv::Size size)
{
	imageSize=size;
}

// Calibrate.
void CameraNormalizer::calibrate()
{
	calibrate(true);
}

// Calibrate the camera. This displays a user-interface.
void CameraNormalizer::calibrate(bool useUI)
{
	// If using a user-interface,
	if(useUI)
	{
		// Create a name to use for the calibration window.
		std::string calibrationWindowName="Calibration Window";
		
		std::cout << "Calibrating camera " << cameraNumber << '\n';
		
		// Open the camera.
		cv::VideoCapture video;
		video.open(cameraNumber);

		// Open a display window.
		cv::namedWindow(calibrationWindowName, cv::WINDOW_AUTOSIZE);

		// Create a variable to store the last key.
		char lastKey='\0';
		
		// Create a variable to store the current frame.
		cv::Mat currentFrame;
		
		// Create a variable to store the current image from the camera and a varible to store the image to be directly written to the camera.
		cv::Mat currentCaptureData, displayImage;

		// Create a variable to store the grayscale version of the current frame.
		cv::Mat grayscaleCurrentFrame;

		// Store the found corners.
		std::vector<cv::Point2f> cornersFound;

		std::vector<std::vector<cv::Point2f> > allCornersFound;
		
		// Create a variable to store whether the chess-board has been found.
		bool chessboardFound=false;

		// Take the next avaliable chessboard picture.
		bool takeFrame=false;

		// While the user hasn't pressed the 'q' key.
		while(lastKey != 'q')
		{
			// Pipe the video frame into the current frame.
			video >> currentCaptureData;
			
			// Resize the capture data and move it to the current frame.
			//cv::resize(currentCaptureData, currentFrame, imageSize);
			currentFrame=currentCaptureData;
			
			// Turn the current frame into a grayscale version of its-self.			
			cv::cvtColor(currentFrame, 
				grayscaleCurrentFrame, CV_RGB2GRAY);			
			
			// Check for the chessboard.
			chessboardFound=cv::findChessboardCorners(grayscaleCurrentFrame,
				cornerSize, cornersFound,
				cv::CALIB_CB_FAST_CHECK + cv::CALIB_CB_ADAPTIVE_THRESH + 
				cv::CALIB_CB_NORMALIZE_IMAGE);

			// If the chessboard was found,
			if(chessboardFound)
			{
				// Find the corners' location, to a more accurate degree.
				cv::cornerSubPix(grayscaleCurrentFrame, cornersFound, 
					cv::Size(10, 10), // Search in a 10 by 10 area.
					cv::Size(-1, -1), // Don't skip anywhere.
					cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1)); // Terminate conditions.
				
				// Draw the chessboard corners.
				cv::drawChessboardCorners(currentFrame, 
					cornerSize, cv::Mat(cornersFound), chessboardFound);
				
				

				// So long as we haven't found 20 sets of corners.
				if(allCornersFound.size() < 20 && takeFrame)
				{
					std::vector<cv::Point2f> oldCorners=cornersFound;
					allCornersFound.push_back(oldCorners);
					takeFrame=false;
				}
			}
			
			// Resize the current frame to the captured size, and store in the display image.
			cv::resize(currentFrame, displayImage, cv::Size(currentCaptureData.cols, currentCaptureData.rows));
			
			
			std::stringstream outputText;
			outputText << "Q to quit. A for next picture. ";
			outputText << allCornersFound.size() << " chessboards found and used.";
			putText(displayImage, outputText.str(), cv::Point(50, 50), 1, 1.0, cv::Scalar(255,0,0));
			
			// Display the image.
			cv::imshow(calibrationWindowName, displayImage);

			// Wait 10 ms for a key to be pressed.
			lastKey=cv::waitKey(10);

			switch(lastKey)
			{
				// If the 'a' key was pressed.
				case 'a':
					takeFrame=true;
				break;
				default: break;
			}
		}

		// Release the video.
		video.release();

		// Generate how the corners should be. TODO: Put this in a seperate function.
		std::vector<std::vector<cv::Point3f> > actualCornerLocations;
		
		actualCornerLocations.push_back(std::vector<cv::Point3f>());

		// The size of the squares. TODO: Change this.
		float squareLength=80.0f;

		// Add the corners to the array.
		for(int y=0; y<cornerSize.height; y++)
		{
			for(int x=0; x<cornerSize.width; x++)
			{
				actualCornerLocations.at(0).push_back(cv::Point3f((x)*squareLength, (y)*squareLength, 0)); // All have a z of 0.
			}
		}
		
		std::vector<cv::Point3f> firstRow=actualCornerLocations.at(0);
		// Resize the array.
		actualCornerLocations.resize(allCornersFound.size(), firstRow);

		// Initialize the camera matrix as a 3x3 identity matrix.
		cameraMatrix=cv::Mat::eye(3, 3, CV_64F);

		// Initialize a matrix to store coefficents such as focal length.
		distortionCoefficents=cv::Mat::zeros(8, 1, CV_64F);

		// Calibrate the camera.
		cv::calibrateCamera(actualCornerLocations, allCornersFound,
			currentFrame.size(), cameraMatrix, distortionCoefficents,
			rotationVectors, translationVectors, CV_CALIB_FIX_K2);
	}
	else
	{
		// TODO: Create a version that runs without UI.
	}
}

// Get the X component of the focal length. Assumes cameraMatrix has been initialized.
double CameraNormalizer::getFocalLengthX()
{
	// f_sub_x is at (0,0) in the camera matrix.
	double focalX=cameraMatrix.at<double>(0, 0);
	
	// Return the focal length.
	return focalX;
}

// Get the Y component of the focal length. Call calibrate first or load a camera matrix.
double CameraNormalizer::getFocalLengthY()
{
	// f_sub_y is at (1,1) in the camera matrix.
	double focalY=cameraMatrix.at<double>(1, 1);
	
	// Return the focal length.
	return focalY;
}


// Save the current calibration.
void CameraNormalizer::saveCalibration()
{
	// Create an output stream.
	std::ofstream fileOutput;
	
	// Open the set filename.
	fileOutput.open(filePath);
	
	// Write the data to the file.
	fileOutput << cameraNumber << '\n';
	fileOutput << serializeMatrix(cameraMatrix) << '\n';
	fileOutput << serializeMatrix(distortionCoefficents) << '\n';
	fileOutput << serializeSize(cornerSize) << '\n';
	
	// Close the file.
	fileOutput.close();
}

// Normalize the camera.
void CameraNormalizer::normalize(cv::Mat cameraData)
{
	cv::Mat copyOfData;
	cameraData.copyTo(copyOfData);
	// Undistort the camera.
	cv::undistort(copyOfData, cameraData, cameraMatrix, distortionCoefficents);
}

// Load the data.
bool CameraNormalizer::loadData()
{
	std::cout << "Starting to load data.\n";
	std::ifstream fileInput;
	std::cout << "Opened file input.\n";
	fileInput.open(filePath);
	
	// If the file can be read from,
	if(fileInput.good())
	{
		std::cout << "The file can be read from.\n";
		// Create variables to store different parts of the data.
		std::string cameraNumberData, cameraMatrixData, distortionCoefficentsData, cornerSizeData;

		// Load data into these.
		std::getline(fileInput, cameraNumberData);
		std::getline(fileInput, cameraMatrixData);
		std::getline(fileInput, distortionCoefficentsData);
		std::getline(fileInput, cornerSizeData);

		// Load these matricies.
		cameraMatrix = recallSerializedMatrix(cameraMatrixData);
		distortionCoefficents = recallSerializedMatrix(distortionCoefficentsData);
		cornerSize = recallSerializedSize(cornerSizeData);
		
		int newCamera=atoi(cameraNumberData.c_str());
		// If the new camera number != the old camera number.
		if(newCamera != cameraNumber)
		{
			// Try changing the file name.
			bool nameChanged=setConfigurationURLBasedOnCameraNumber();

			fileInput.close();

			bool result=false;

			// If the name changed.
			if(nameChanged)
			{
				// Try to re-load the data.
				result = loadData();
			}

			// Return the result.
			return result;
		}		

		fileInput.close();
		return true;
	}
	else
	{
		// Try changing the file name.
		bool nameChanged=setConfigurationURLBasedOnCameraNumber();

		bool result=false;
		// If the name changed.
		if(nameChanged)
		{
			// Try to re-load the data.
			result = loadData();
		}

		// Return the result.
		return result;
	}
}

// Set the file path based on the camera number. Return whether the name changed.
bool CameraNormalizer::setConfigurationURLBasedOnCameraNumber()
{
	std::string oldPath=filePath;

	// Try changing the file name.
	std::stringstream newFilePath;
	newFilePath << "cameraConfiguration" << cameraNumber << ".txt";
	filePath=newFilePath.str();

	return oldPath != filePath; // != is overloaded for std::string.
}

// Convert an OpenCV matrix to a readable format.
std::string CameraNormalizer::serializeMatrix(cv::Mat input)
{
	// Use the created function.
	return Serialize::serializeMatrix(input);
}

// Recall a serialized matrix.
cv::Mat CameraNormalizer::recallSerializedMatrix(std::string input)
{
	// Use the created function
	return Serialize::recallSerializedMatrix(input);
}

// Serialize a size.
std::string CameraNormalizer::serializeSize(cv::Size input)
{
	// Return a serialized size, from the given function.
	return Serialize::serializeSize(input);
}

// Recall a serialized size.
cv::Size CameraNormalizer::recallSerializedSize(std::string input)
{
	// Return the result of the provided implementation's serialization.
	return Serialize::recallSerializedSize(input);
}
