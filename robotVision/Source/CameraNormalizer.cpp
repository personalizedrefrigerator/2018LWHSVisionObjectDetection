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

		// Release the video.
		video.release();

		// Generate how the corners should be. TODO: Put this in a seperate function.
		std::vector<std::vector<cv::Point3f> > actualCornerLocations;
		
		actualCornerLocations.push_back(std::vector<cv::Point3f>());

		// The size of the squares. TODO: Change this.
		float squareLength=20.0f;

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
	std::ifstream fileInput;
	fileInput.open(filePath);
	
	// If the file can be read from,
	if(fileInput.good())
	{
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
			setConfigurationURLBasedOnCameraNumber();

			fileInput.close();

			// Try to re-load the data.
			bool result = loadData();


			return result;
		}		

		fileInput.close();
		return true;
	}
	else
	{
		// Try changing the file name.
		setConfigurationURLBasedOnCameraNumber();

		// Try to re-load the data.
		bool result = loadData();

		return result;
	}
}

// Set the file path based on the camera number.
void CameraNormalizer::setConfigurationURLBasedOnCameraNumber()
{
	// Try changing the file name.
	std::stringstream newFilePath;
	newFilePath << "cameraConfiguration" << cameraNumber << ".txt";
	filePath=newFilePath.str();
}

// Convert an OpenCV matrix to a readable format.
std::string CameraNormalizer::serializeMatrix(cv::Mat input)
{
	// Create variables to be used while traversing the input.
	int x, y;
	double* rowPointer;

	// Create a variable to accumulate the result.
	std::stringstream resultStream;

	// Store the width of the current frame.
	int width=input.size().width;
	
	// Add the matrix's dimensions to the output.
	resultStream << '[' << input.rows << 'x' << width << ']';

	for(y=0; y<input.rows; y++)
	{
		rowPointer=input.ptr<double>(y); // TODO: Change this from CV_64F to a template argument.
		for(x=0; x<width; x++)
		{
			resultStream << rowPointer[x] << "C";
		}
		resultStream << "R";
	}

	// Return the string version of the matrix.
	return resultStream.str();
}

// Recall a serialized matrix.
cv::Mat CameraNormalizer::recallSerializedMatrix(std::string input)
{
	// Make a variable to store the current character.
	char currentCharacter;
	
	// Create a variable to store the current part.
	std::stringstream currentPart;

	// Create variables to store the width and height.
	int width=0, height=0;

	// Create variables to store the current position.
	int currentX=0, currentY=0;

	// Create a matrix to store the output.
	cv::Mat output;

	// The current double value.
	double currentValue;

	// Extract the dimensions of the matrix.
	for(int i=1; i<input.length(); i++)
	{
		// Update the current character.
		currentCharacter=input.at(i);
		
		switch(currentCharacter)
		{
			case ']': // Matricies are heightxwidth.
				// Convert the current part to an integer.
				width=atoi(currentPart.str().c_str());
				
				// The width and height are probably both found. Create the matrix.
				output=cv::Mat::zeros(height, width, CV_64F);
				
				// Clear the current part.
				currentPart.str("");
			break;
			case 'x':
				// Convert the current part to an integer.
				height=atoi(currentPart.str().c_str());

				// Clear the current part.
				currentPart.str("");
			break;
			case 'C':
				// Store the current value.
				currentValue=atof(currentPart.str().c_str());
				
				// Place the current value into the matrix. This may fail (though works with std::vector).
				output.at<double>(currentY, currentX) = currentValue;				
				
				// Increase the x-position.
				currentX++;

				// If the current x position is larger than or equal to the matrix's length,
				if(currentX >= width)
				{
					// Go to the next row.
					currentX=0;
					currentY++;

					// If no more rows,
					if(currentY >= height)
					{
						// Stop.
						return output;
					}
				}

				// Clear the current part.
				currentPart.str("");
			break;
			case 'R':
				// Do nothing. 'R' is handled by the last 'C'.
			break;
			default:
				currentPart << currentCharacter;
			break;
		}
	}

	// Return the output.
	return output;	
}

// Serialize a size.
std::string CameraNormalizer::serializeSize(cv::Size input)
{
	std::stringstream output;
	
	output << input.width << 'x' << input.height;

	// Return the output.
	return output.str();
}

// Recall a serialized size.
cv::Size CameraNormalizer::recallSerializedSize(std::string input)
{
	// Create a variable to store the current character.
	char currentCharacter;
	
	// Store the current part, width of the size, and height of the size.
	std::stringstream currentPart;
	int width=0, height;

	for(int i=0; i<input.length(); i++)
	{
		// Update the current character.
		currentCharacter=input.at(i);

		// If an x, move to accumulating the height.
		if(currentCharacter == 'x')
		{
			width=atoi(currentPart.str().c_str());

			// Clear the current part.
			currentPart.str("");
		}
		else
		{
			// Add the current character to the current part.
			currentPart << currentCharacter;
		}
	}

	height=atoi(currentPart.str().c_str());
	return cv::Size(width, height);
}
