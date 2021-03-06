#include "VisionApplication.h"

#include "PowerCube.h"

VisionApplication::VisionApplication()
{
	// Clear the detector's list of comparison shapes.
	detector.clearComparisonShapes();
	
	// Load all comparison shapes.
	loadDefaultShapes();
	
	// Set the detector's comparison shapes to those loaded.
	detector.setComparisonShapes(&shapesToCompare);
	tracker.setComparisonShapes(&foundShapes);
	
	// Tell the tracker's found shapes list that it isn't responsable for its memory.
	//detector.getFoundShapes().setHandlingMemoryManagment(false);
	tracker.getComparisonShapes().setHandlingMemoryManagment(false);
	
	// Add the tracking shape to the found shapes.
	//foundShapes.add(currentShape);
}

// Run opperations on a single frame.
void VisionApplication::runFrame(cv::Mat inputImage, VisionOutput & visionOutput, VisionInputParameters & options)
{
	// Give the detectors the image.
	tracker.setImage(inputImage);
	detector.setImage(inputImage);

	// Set surface detection options,
	tracker.setPlaneDetectorOptions(options.surfaceDetectionOptions);
	detector.setPlaneDetectorOptions(options.surfaceDetectionOptions);
	

	if(!trackingObjects)
	{
		tracker.setComparisonShapes(&shapesToCompare); // Set the tracker's list of comparison shapes to those  loaded.
		
		tracker.detectAllShapes(); // Detect all shapes.
	}
	else
	{
		tracker.setComparisonShapes(&foundShapes);
		tracker.clearComparisonShapes();
		
		
		Shape copyOf = *currentShape;
		tracker.addComparisonShape(copyOf);
		
		// Find probable shapes based on this.
		tracker.findProbableShapes();
	}
	
	// So long as now tracking objects, and there are objects to track,
	if(tracker.getFoundShapes().size() > 0)
	{
		
		bool success=tracker.findTargetAndUpdate(*currentShape, options.worstMatchRating);
		
		
		if(!trackingObjects)
		{
			trackingShape=tracker.getLastComparedComparisonShape();
		}
		
		
		
		if(currentShape->getContentSize() < 100)
		{
			success=false;
		}
		
		trackingObjects=success;
		
		// If a success,
		if(trackingObjects)
		{
			// Give the shape needed information. TODO: Make use of focalY.
			currentShape->setScreenZ(options.focalLengthX);
		
			// Calculate shape properties.
			currentShape->calculateCenterAndOkScreenSize();
			currentShape->calculateAngle(inputImage.cols, inputImage.rows);
			
			currentShape->calculateSignificantPoints(); // Tell the current shape to calculate its significant points.
			currentShape->trimCorners(4);
			
			std::vector<Point2D> previousCornersToUse=previousCorners;
			
			// Get the corners.
			definedPreviousCorners=true;
			previousCorners.clear();
			currentShape->getCorners(previousCorners); // Store the previous corners.
			
			if(definedPreviousCorners)
			{
				//currentShape->compareAndFilterCorners(previousCornersToUse, previousCenter); // Filter corners that changed distance.
				//currentShape->filterCornersToFurthest(4); // Get only the 4 corners furthest from the center.
				
			}
			previousCenter=currentShape->getCenter();
			
			Shape & currentShapeRefrence = *currentShape;
			
			// Create a box from the current shape.
			Box * boxShape = new Box();
			boxShape->fromOther(currentShapeRefrence);
			boxShape->setScreenSize(inputImage.cols, inputImage.rows);
			boxShape->findCameraPosition();
			
			// TODO Update these values.
			boxShape->setWorldHeight(5.0);
			boxShape->setCameraPitch(0.0);
			boxShape->convertUnits(20, 10, 350);
			
			// Give debugging output.
			if(showDebugOutput)
			{
				boxShape->drawDebugOutput(inputImage);
			}
			
			// Give other output.
			visionOutput.setXRotation(currentShape->getXAngle());
			visionOutput.setYRotation(currentShape->getYAngle());
			visionOutput.setPixelSize(currentShape->getContentSize());
			visionOutput.setAverageColor(currentShape->getAverageColor());
			visionOutput.setCenterLocation(currentShape->getCenter());
			
			// Output the screenZ to the visionOutput.
			visionOutput.setDistance(boxShape->getDistance());
			
			//Color averageColor=currentShape->getAverageColor();
			
			//unsigned int averageRedAndGreen=(averageColor.getR() + averageColor.getG())/2;
			
			// Set the tracking shape's color to that of the tracking shape.
			currentShape->setAverageColor(trackingShape.getAverageColor());
			
			// Free memory.
			delete boxShape;
		}
	}
	else
	{
		// Otherwise, 
		//we are not tracking an object.
		trackingObjects=false;
	}
}

// Find the shapes that might be tracked in an input image.
void VisionApplication::findShapes(cv::Mat image)
{
	// Set the image to be used by the detector.
	detector.setImage(image);
	
	// Tell the detector to find shapes.
	detector.detectAllShapes();
	
	// Set whether we are tracking shapes to whether the detector has found any.
	trackingObjects=detector.getFoundShapes().size() > 0;

}

// Set whether the debug output of the program should be drawn to the image, etc.
void VisionApplication::setShowDebugOutput(bool isDebugging)
{
	showDebugOutput=isDebugging;
}

// Load the comparison shapes to be used.
bool VisionApplication::loadDefaultShapes()
{
	shapesToCompare.clear();

	// Make a yellow, empty shape, that finds others completely based on color.
	Shape * cubeShape=new PowerCube();
	
	// Add the shape to the list of shapes to compare with.
	shapesToCompare.push_back(cubeShape);

	// Return true on success.
	return true;
}
