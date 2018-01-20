#include "CameraFilter.h"

#include "PlaneDetectorOptions.h"

// Construct a filtering object.
CameraFilter::CameraFilter(unsigned int cameraNumber)//cv::Mat startingData, unsigned int cameraNumber)
{
	//data=startingData;
	std::cout << "Loading camera filter...\n";
	normalizer.setCameraNumber(cameraNumber);
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

// Correct errors in the camera.
void CameraFilter::normalize()
{
	normalizer.normalize(data);
}

// Run cornerHarris to detect corners.
void CameraFilter::cornerHarris()
{
	// Learning to use cornerHarris, see
	// https://docs.opencv.org/master/d4/d7d/tutorial_harris_detector.html

	// Create matricies for output.
	cv::Mat grayscaleVersion, result, normalResult, scaled;

	// Convert camera data to grayscale.
	cvtColor(data, grayscaleVersion, cv::COLOR_BGR2GRAY);
	result=cv::Mat::zeros(grayscaleVersion.size(), CV_64F);

	// Run cornerHarris to detect corners, 8x8 search region per pixel.
	cv::cornerHarris(grayscaleVersion, result, 8, 5, 0.01, cv::BORDER_DEFAULT);

	// Normalize the result.
	cv::normalize(result, normalResult, 0, 255, cv::NORM_MINMAX, CV_64F, cv::Mat());
	//cv::convertScaleAbs(normalResult, scaled); // Make 8 bit unsigned ints.
	//normalResult=result;

	// Take the average.
	double avg=0.0;
	int count=0;
	for(int y=0; y<normalResult.rows; y++)
	{
		for(int x=0; x<normalResult.cols; x++)
		{
			avg+=normalResult.at<double>(y, x);
			count++;
		}
	}
	avg/=count;

	// For each potential corner,
	int x;
	for(int y=0; y<normalResult.rows; y++)
	{
		for(x=0; x<normalResult.cols; x++)
		{
			if((int)normalResult.at<double>(y, x) > avg*1.05)
			{
				// Draw a circle.
				cv::circle(data, cv::Point(x, y), 1, cv::Scalar(0, 200, 100, 200), 1, 8, 0); // 8 is line type.
			}
		}
	}
}

// Detect corners.
void CameraFilter::detectCorners()
{
	// Define matricies.
	cv::Mat grayscaleVersion;

	// Convert camera data to grayscale.
	cvtColor(data, grayscaleVersion, cv::COLOR_BGR2GRAY);

	// Normalize the brightness and change the contrast.
	cv::equalizeHist(grayscaleVersion, grayscaleVersion);

	// Detect edges.
	//cv::Canny(grayscaleVersion, grayscaleVersion, 80, 160);

	// Create an array to store the corners found.
	std::vector<cv::Point2f> cornersFound;
	
	// Find the first 1500 corners, in an 8x8 area.
	cv::goodFeaturesToTrack(grayscaleVersion, cornersFound, 1500, 0.01, 20, cv::Mat(), 10, false, 0.04);

	// For each corner,
	for(unsigned int i=0; i<cornersFound.size(); i++)
	{
		// Draw a circle.
		cv::circle(data, cornersFound.at(i), 4, cv::Scalar(0, 100, 200, 200), 2, 8, 0); // 8 is line type. 2 is line-width.
	}
}

void CameraFilter::detectLineSegments()
{
	cv::Mat edges;

	std::vector<cv::Vec4i> lines;

	// Define matricies.
	cv::Mat grayscaleVersion;

	// Convert camera data to grayscale.
	cvtColor(data, grayscaleVersion, cv::COLOR_BGR2GRAY);

	// Normalize the brightness and change the contrast.
	cv::equalizeHist(grayscaleVersion, grayscaleVersion);
	// Detect edges. Min Max size.
	cv::Canny(data, edges, 50, 140, 3);
	//edges.copyTo(data);
	// Run a Hough line transform. 1 location accuracy, angle accuracy, threshold, min line length,
	//min gap.
	cv::HoughLinesP(edges, lines, 2, 1, 10, 54, 1);

	// For each line,
	for(int i=0; i<lines.size(); i++)
	{
		cv::Vec4i currentLine=lines.at(i);
		cv::line(data, cv::Point(currentLine[0], currentLine[1]), cv::Point(currentLine[2],
			currentLine[3]), cv::Scalar(255, 255, 0), 4, 1);//cv::LINE_AA);
	}

	// For all edges,
	for(int y=0; y<data.rows; y++)
	{
		for(int x=0; x<data.cols; x++)
		{
			if(edges.at<unsigned char>(y, x) > 100)
			{
				data.at<unsigned char>(y, x*3)=0;
				data.at<unsigned char>(y, x*3+1)=0;
				data.at<unsigned char>(y, x*3+1)=255;
			}
		}
	}
}

// Erode and dilate the camera input.
void CameraFilter::erodeAndDilate()
{
	cv::Mat erodeDilateElement=cv::getStructuringElement(cv::MORPH_RECT, 
			cv::Size(3, 3)); // Change the size to emphasize different shapes.
	
	// Erode and dilate
	cv::erode(data, data, erodeDilateElement,
			cv::Point(-1, -1), 1); // An anchor of nowhere and 1 iteration.
		cv::dilate(data, data, erodeDilateElement,
			cv::Point(-1, -1),  1); // An anchor of nowhere and 1 iteration.
}

// Show a plane found by the plane detector.
void CameraFilter::showPlane()
{
	//std::cout << "Detecting 2D points.\n";
	planeDetector.detectPoints2D(); // Detect the points on the plane.
	//std::cout << "Detecting significant points.\n";
	planeDetector.detectSignificantPoints(); // Detect parts of the edge deemed "significant."
	planeDetector.showPlaneRegion(data);
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
	//detectCorners();
	//detectLineSegments();
	//detectCorners();
	//cornerHarris();
	showPlane();
}
