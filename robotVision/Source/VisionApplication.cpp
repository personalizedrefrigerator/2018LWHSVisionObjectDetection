#include "VisionApplication.h"

VisionApplication::VisionApplication()
{
	// Clear the detector's list of comparison shapes.
	detector.clearComparisonShapes();
	
	// Load all comparison shapes.
	loadDefaultShapes();
	
	// Set the detector's comparison shapes to those loaded.
	detector.setComparisonShapes(&shapesToCompare);
	
	// Tell the tracker's found shapes list that it isn't responsable for its memory.
	detector.getFoundShapes().setHandlingMemoryManagment(false);
	
	// Add a shape for tracking purposes to the found shapes.
	foundShapes.add(new Shape());
}

// Run opperations on a single frame.
void VisionApplication::runFrame(cv::Mat inputImage, VisionOutput & visionOutput, VisionInputParameters & options)
{
	// Set surface detection options,
	tracker.setPlaneDetectorOptions(options.surfaceDetectionOptions);
	detector.setPlaneDetectorOptions(options.surfaceDetectionOptions);

	tracker.clearComparisonShapes();

	if(!trackingObjects)
	{
		findShapes(inputImage);
		
		// If there are shapes to track,
		if(detector.getFoundShapes().size() > 0)
		{
			Shape copyOf=*detector.getFoundShapes().at(0);
			tracker.addComparisonShape(copyOf);
			trackingObjects=true;
		}
	}
	else
	{
		Shape copyOf=*tracker.getFoundShapes().at(0);
		tracker.addComparisonShape(copyOf);
	}
	
	// So long as now tracking objects, and there are objects to track,
	if(trackingObjects && tracker.getComparisonShapes().size() > 0)
	{
		Shape * currentShape=new Shape();
		
		bool success=tracker.findTargetAndUpdate(*currentShape, options.worstMatchRating);
		
		trackingObjects=success;
		// If a success,
		if(success)
		{
			
			// Give the shape needed information. TODO: Make use of focalY.
			currentShape->setScreenZ(options.focalLengthX);
		
			// Calculate shape properties.
			currentShape->calculateCenterAndOkScreenSize();
			currentShape->calculateAngle(inputImage.cols, inputImage.rows);
			currentShape->calculateCornersCV();
			
			
			// Give debugging output.
			if(showDebugOutput)
			{
				currentShape->drawDebugOutput(inputImage);
			}
			
			// Give other output.
			visionOutput.setXRotation(currentShape->getXAngle());
			visionOutput.setYRotation(currentShape->getYAngle());
			visionOutput.setPixelSize(currentShape->getContentSize());
			visionOutput.setAverageColor(currentShape->getAverageColor());
			visionOutput.setCenterLocation(currentShape->getCenter());
		}
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
	// Make a yellow, empty shape, that finds others completely based on color.
	Shape * cubeShape=new Shape();
	cubeShape->setAverageColor(Color(255, 255, 0));
	
	// Set its comparison options.
	ShapeComparisonOptions& options=cubeShape->getShapeComparisonOptions();
	options.sizePortion=0;
	options.colorPortion=1.0;
	options.centerDeltaPortion=0.0;

	// Add the shape to the list of shapes to compare with.
	shapesToCompare.push_back(cubeShape);

	// Return true on success.
	return true;
}
