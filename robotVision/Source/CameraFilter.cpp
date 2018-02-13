#include "CameraFilter.h"

#include "PlaneDetectorOptions.h"

#include <vector>
#include <opencv2/stitching.hpp>

// Construct a filtering object.
CameraFilter::CameraFilter(unsigned int cameraNumber)//cv::Mat startingData, unsigned int cameraNumber)
{
	//data=startingData;
	std::cout << "Loading camera filter...\n";
	normalizer.setCameraNumber(cameraNumber);
	normalizer.setImageSize(imageSize);
	std::cout << "Attemptint to load data...\n";
	bool couldLoadData=normalizer.loadData();
	
	std::cout << "Data loaded!" << couldLoadData << "\n";

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
	planeDetector.setImage(data);
}

// Set the size of the image to expect.
void CameraFilter::setImageSize(cv::Size size)
{
	imageSize=size;
}

// Correct errors in the camera.
void CameraFilter::normalize()
{
	normalizer.normalize(data);
}

// Erode and dilate the camera input.
void CameraFilter::erodeAndDilate(cv::Mat dataToUse, unsigned int recursions)
{
	cv::Mat erodeDilateElement=cv::getStructuringElement(cv::MORPH_RECT, 
			cv::Size(5, 5)); // Change the size to emphasize different shapes.
	
	// Erode and dilate
	cv::dilate(dataToUse, dataToUse, erodeDilateElement,
			cv::Point(-1, -1),  recursions); // An anchor of nowhere and 1 iteration.
	cv::erode(dataToUse, dataToUse, erodeDilateElement,
			cv::Point(-1, -1), recursions); // An anchor of nowhere and 1 iteration.
}

void CameraFilter::erodeAndDilate()
{
	erodeAndDilate(data, 1);
}

// Divide an image's colors into tiers.
void CameraFilter::tier(int multiplier)
{
	int x, y, c;
	unsigned char * ptr;
	for(y=0; y<data.rows;y++)
	{
		ptr=data.ptr<unsigned char>(y);
		for(x=0; x<data.cols; x++)
		{
			for(c=0; c<3; c++)
			{
				ptr[x*3+c]=((unsigned char)(ptr[x*3+c]/multiplier))*multiplier;
			}
		}
	}
}

// Show a plane found by the plane detector.
void CameraFilter::showPlane()
{
	planeDetector.detectPoints2D(); // Detect the points on the plane.

	cv::Mat planeOutput=cv::Mat::zeros(data.rows, data.cols, CV_8UC3);
	planeDetector.showPlaneRegion(planeOutput);
	erodeAndDilate(planeOutput, 5);
	
	cv::Mat grayscaleVersion;
	// Convert camera data to grayscale.
	cvtColor(planeOutput, grayscaleVersion, cv::COLOR_BGR2GRAY);

	// Create an array to store the corners found.
	std::vector<cv::Point2f> cornersFound;
	
	// Find the first 4 corners, 0.1 quality, 7 min distance, empty mask, block size of 15, using
	//a harris detector.
	cv::goodFeaturesToTrack(grayscaleVersion, cornersFound, cornersToFind, 0.001, minCornerDistance, cv::Mat(), cornerBlockSize, useCornerHarris, cornerK);


	//planeDetector.detectSignificantPoints(); // Detect parts of the edge deemed "significant."
	planeDetector.showPlaneRegion(data);

	// For each corner,
	for(unsigned int i=0; i<cornersFound.size(); i++)
	{
		// Draw a circle.
		cv::circle(data, cornersFound.at(i), 4, cv::Scalar(0, 100, 200, 200), 2, 8, 0); // 8 is line type. 2 is line-width.
	}
}

// Get the camera's normalizer.
CameraNormalizer & CameraFilter::getNormalizer()
{
	return normalizer;
}

// Stitch images together.
cv::Mat CameraFilter::stitch(std::vector<cv::Mat> inputs)
{
	cv::Mat output;

	// If the stitcher hasn't been made,
	if(!stitcherMade)
	{
		// Make an image stitcher. cv::Stitcher::Mode::PANORAMA is 0.
		//cv::Stitcher::Mode mode=cv::Stitcher::PANORAMA;
		stitcher=cv::Stitcher::createDefault(true);
		
		// Note that one was made.
		stitcherMade=true;
	}
	stitcher.stitch(inputs, output);
	
	return output;
}

// Stitch just two images together.
cv::Mat CameraFilter::stitchTwo(cv::Mat image1, cv::Mat image2)
{
	std::vector<cv::Mat> inputs;
	inputs.push_back(image1);
	inputs.push_back(image2);
	
	return stitch(inputs);
}

// Configure corner detection options.
void CameraFilter::configureCornerDetection(double k, int cornersToFind, int minCornerDistance, int cornerBlockSize, bool useCornerHarris)
{
	this->cornerK=k;
	this->cornersToFind=cornersToFind;
	this->minCornerDistance=minCornerDistance;
	this->cornerBlockSize=cornerBlockSize;
	this->useCornerHarris=useCornerHarris;
}

// Set the plane detector options.
void CameraFilter::setPlaneDetectorOptions(PlaneDetectorOptions options)
{
	planeDetector.setOptions(options);
}

// Run all camera filters.
void CameraFilter::runAllFilters()
{
	normalize();
	erodeAndDilate();
}

// Deconstruct.
CameraFilter::~CameraFilter()
{
	// Unrefrence pointers here.
}
