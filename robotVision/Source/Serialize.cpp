#include "Serialize.h"

// Include standard libraries.
#include <sstream>
#include <unistd> // atoi, etc.

using namespace Serialize;

// Serialize a pair of doubles.
std::string serializeRealPair(double x, double y)
{
	// Create a stream to store the output.
	std::stringstream output;
	
	output << x << 'x' << y;

	// Return the output.
	return output.str();
}

// Convert a string to a pair (a point 2D, with x and y parts).
Point2D recallSerializedRealPair(std::string input)
{
	// Create a variable to store the current character.
	char currentCharacter;
	
	// Store the current part, width of the size, and height of the size.
	std::stringstream currentPart;
	double x=0, y;

	for(int i=0; i<input.length(); i++)
	{
		// Update the current character.
		currentCharacter=input.at(i);

		// If an x, move to accumulating the height.
		if(currentCharacter == 'x')
		{
			x=atoi(currentPart.str().c_str());

			// Clear the current part.
			currentPart.str("");
		}
		else
		{
			// Add the current character to the current part.
			currentPart << currentCharacter;
		}
	}

	y=atoi(currentPart.str().c_str());
	return Point2D(x, y);
}

// Serialize a size, converting it to a string.
std::string serializeSize(cv::Size input)
{
	// Serialize the size as a pair.
	return serializeRealPair(input.x, input.y);
}

// Convert a string to a size.
cv::Size recallSerializedSize(std::string input)
{
	Point2D size=recallSerializedRealPair(input);
	
	return cv::Size((unsigned int)size.x, (unsigned int)size.y);
}

// Convert a matrix of doubles to a string.
std::string serializeMatrix(cv::Mat input)
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

// Read a matrix of doubles from a string.
cv::Mat recallSerializedMatrix(std::string input)
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

// Convert a provided color to a string.
std::string serializeColor(Color input)
{
	// Create a stringstream to accumulate the result.
	std::stringstream result;
	
	// Add the parts of the result.
	result << input.getR() << "c" << input.getG() << "c" << input.getB();
	
	// Return its string version.
	return result.str();
}

// Recall a color from a string.
Color recallSerializedColor(std::string input)
{
	// Create a variable to store the current part.
	std::string currentPart="";
	
	// Create a variable to store the current character.
	char currentCharacter;
	
	// Create variables to store the red, green, and blue parts.
	unsigned int red, green, blue;
	
	// Create a variable to store the resultant color parts.
	int[3] result=new int[3];
	
	// Create variables to store indices.
	unsigned int resultIndex=0;
	
	unsigned int characterIndex=0;
	
	// For every character.
	for(characterIndex=0; characterIndex<input.size(); characterIndex++)
	{
		// Store the current.
		currentCharacter=input.at(characterIndex);
		
		if(currentCharacter == 'c')
		{
			// Convert the current part to an integer, add put it in the result.
			result[resultIndex]=atoi(currentPart.c_str());
			
			// Increment the result index.
			resultIndex++;
			
			// Clear the current part.
			currentPart="";
		}
		else
		{
			// Otherwise, add the current character to the current part.
			currentPart+=currentCharacter;
		}
	}
	
	// Move values from the result.
	red=static_cast<unsigned char>(result[0]);
	green=static_cast<unsigned char>(result[1]);
	blue=static_cast<unsigned char>(result[2]);
	
	// Create the resultant color.
	Color resultantColor=Color(red, green, blue);
	
	// Return the result.
	return resultantColor;
}

// Convert a Point2D to a string.
std::string serializePoint2D(Point2D point)
{
	// Return the point, serialized as a real pair.
	return serializeRealPair(point.x, point.y);
}

// Convert a string (containing a serialized Point2D) to a Point2D.
Point2D recallSerializedPoint2D(std::string input)
{
	// Unserialize as a pair of doubles.
	return recallSerializedRealPair(input);
}

// Serialize a vector of Point2Ds.
std::string serializePoint2DVector(std::vector<Point2D> input)
{
	// Create a variable to store the index in the vector.
	unsigned int index = 0;
	
	// Create a variable to accumulate the result.
	std::stringstream result;
	
	// Create a variable to store the length of the given vector.
	unsigned int inputSize=input.size();
	
	// For every value in the given vector.
	for(index = 0; index < inputSize; index++)
	{
		// Store the current point.
		Point2D & currentValue=input.at(index);
		
		// Add the serialized version of the point.
		result << serializePoint2D(currentValue);
		
		// Add a comma to separate the elements, so long as not the last time.
		if(index < inputSize - 1)
		{
			result << ',';
		}
	}
	
	// Return the string version of the result.
	return result.str();
}

// Serialize shape comparison options, converting it to a machine-readable string.
std::string serializeShapeComparisonOptions(ShapeComparisonOptions options)
{
	// Create a stringstream to accumulate output.
	std::stringstream result;
	
	// Add the parts of the comparison options to the result.
	result << options.colorDeltaMultiplier << 'n';
	result << options.sizeDeltaMultiplier << 'n';
	result << options.centerPointDeltaMultiplier << 'n';
	result << options.sizePortion << 'n';
	result << options.colorPortion << 'n';
	result << options.centerDeltaPortion;
	
	// Return the string version of the result.
	return result.str();
}

// Recall a serialized version of the comparison options.
ShapeComparisonOptions recallSerializedShapeComparisonOptions(std::string input)
{
	// Split the input based on the letter 'n.'
	std::vector<string> partsOfInput = split(input, 'n');
	
	// Create a variable to store the result.
	ShapeComparisonOptions result;
	
	// So long as the split vector is at least the correct length.
	if(partsOfInput.size() >= 6)
	{
		// Convert all values to doubles.
		std::vector<double> doubleParts;
		
		// Create a variable to store the current index in the array of parts of the input, traverse it.
		unsigned int currentIndex=0;
		for(currentIndex=0; currentIndex < partsOfInput.size(); currentIndex++)
		{
			doubleParts.at(currentIndex) = atof(partsOfInput.at(currentIndex).c_str());
		}
		
		// Move the double and integer versions of the values to the result.
		result.colorDeltaMultiplier = doubleParts.at(0);
		result.sizeDeltaMultiplier = doubleParts.at(1);
		result.centerPointDeltaMultiplier = doubleParts.at(2);
		result.sizePortion = doubleParts.at(3);
		result.colorPortion = doubleParts.at(4);
		result.centerDeltaPortion = doubleParts.at(5);
	}
	
	// Return the result.
	return result;
}

// Get the number of occurences of a character in a string.
unsigned int getOccurencesOfCharacter(std::string input, char characterToFind)
{
	// Create a variable to store the current index in the input.
	unsigned int indexInInput=0;
	
	// Create a variable to store the length of the input.
	unsigned int inputLength=input.size();
	
	// Create a variable to store the current character.
	char currentCharacter;
	
	// Create a variable to store the number of that character found.
	unsigned int numberFound=0;
	
	// Count the number of commas, to find a reasonable vector size.
	for(indexInInput=0; indexInInput<inputLength; indexInInput++)
	{
		currentCharacter=input.at(indexInInput);
		
		// If a comma, note this.
		if(currentCharacter == characterToFind)
		{
			numberFound++;
		}
	}
	
	return numberFound;
}

// Recall a serialized vector of Point2Ds.
std::vector<Point2D> recallSerializedVectorOfPoint2Ds(std::string input)
{
	// Create a variable to store the current index in the input.
	unsigned int indexInInput=0;
	
	// Create a variable to store the length of the input.
	unsigned int inputLength=input.size();
	
	// Create a variable to store the current character.
	char currentCharacter;
	
	// Create a variable to store the number of commas found.
	unsigned int resultantLength = getOccurencesOfCharacter(input, ',');
	
	// The resultant length is 1 greater than the number of commas found.
	resultantLength++;
	
	// Create a vector to store the result.
	std::vector<Point2D> result(resultantLength);
	
	// Create a variable to store the current part of the string.
	std::string currentPartOfInput="";
	
	// For every character in the input.
	for(indexInInput=0; indexInInput < inputLength; indexInInput++)
	{
		currentCharacter=input.at(indexInInput);
		
		// If the current character is a comma,
		if(currentCharacter == ',')
		{
			// Unserialize the Point2D.
			Point2D currentPoint=recallSerializedPoint2D(currentPartOfInput);
			
			// Add it to the result.
			result.push_back(currentPoint);
			
			// Clear the current part buffer.
			currentPartOfInput="";
		}
		else
		{
			currentPartOfInput+=currentCharacter;
		}
	}
	
	// Return the result.
	return result;
}

// Split a string.
std::vector<std::string> split(std::string input, char splitCharacter)
{
	// Find the number of the split character in the result.
	unsigned int countOfSplitCharacter = getOccurencesOfCharacter(input, splitCharacter);

	// Create a variable to store the result.
	std::vector<std::string> result(countOfSplitCharacter+1);

	// Create a variable to store the current part of the string.
	std::string currentPart="";
	
	// Create a variable to store the string's length.
	unsigned int stringLength=input.size();
	
	// Create a variable to store the current character.
	char currentCharacter;
	
	// Creaet a varible to store the current index in the string.
	unsigned int index=0;
	
	for(index=0; index < stringLength; index++)
	{
		// Change the current character.
		currentCharacter=input.at(index);
		
		// If the splitCharacter, add it as a new element, to the result.
		if(currentCharacter == splitCharacter)
		{
			result.push_back(currentPart);
			
			// Clear the current part.
			currentPart="";
		}
		else
		{
			// Otherwise, add the current character to the current part.
			currentPart+=currentCharacter;
		}
	}
	
	// Add the current part to the result.
	result.push_back(currentPart);
	
	// Return the result.
	return result;
}
