#include "CameraNormalizer.h"

// Include opencv libraries.
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc.hpp>

// Include file access libraries.
#include<fstream>

// Include stringstream libraries.
#include<sstream>

// Set the camera numbe to be used.
void CameraNormalizer::setCameraNumber(unsigned int cameraNumber)
{
	this->cameraNumber=cameraNumber;
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

		// Open the camera.
		cv::VideoCapture video;
		video.open(cameraNumber);

		// Open a display window.
		cv::namedWindow(calibrationWindowName, cv::WINDOW_AUTOSIZE);

		// Create a variable to store the last key.
		char lastKey='\0';
		
		// Create a variable to store the current frame.
		cv::Mat currentFrame;

		// Create a variable to store the grayscale version of the current frame.
		cv::Mat grayscaleCurrentFrame;

		// Store the found corners.
		std::vector<cv::Point2f> cornersFound;

		std::vector<std::vector<cv::Point2f>> allCornersFound;
		
		// Create a variable to store whether the chess-board has been found.
		bool chessboardFound=false;

		// Take the next avaliable chessboard picture.
		bool takeFrame=false;

		// While the user hasn't pressed the 'q' key.
		while(lastKey != 'q')
		{
			// Pipe the video frame into the current frame.
			video >> currentFrame;
			
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
			
			std::stringstream outputText;
			outputText << "Q to quit. A for next picture. ";
			outputText << allCornersFound.size() << " chessboards found and used.";
			putText(currentFrame, outputText.str(), cv::Point(50, 50), 1, 1.0, cv::Scalar(255,0,0));
			
			// Display the image.
			cv::imshow(calibrationWindowName, currentFrame);

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

		// Generate how the corners should be. TODO: Put this in a seperate function.
		std::vector<std::vector<cv::Point3f>> actualCornerLocations;
		
		actualCornerLocations.push_back(std::vector<cv::Point3f>());

		// The size of the squares. TODO: Change this.
		float squareLength=20.0f;

		// Add the corners to the array.
		for(int x=0; x<cornerSize.width; x++)
		{
			for(int y=0; y<cornerSize.height; y++)
			{
				actualCornerLocations.at(0).push_back(cv::Point3f(x*squareLength, y*squareLength, 0)); // All have a z of 0.
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

// Save the current calibration.
void CameraNormalizer::saveCalibration()
{
	// Create an output stream.
	std::ofstream fileOutput;
	
	// Open the set filename.
	fileOutput.open(filePath);
	
	// Write the data to the file.
	fileOutput << cameraNumber << '\n';
	fileOutput << cameraMatrix << '\n';
	fileOutput << distortionCoefficents << '\n';
	fileOutput << cornerSize << '\n';
	
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
