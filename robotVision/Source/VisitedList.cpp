#include "VisitedList.h"

// Construct the list.
VisitedList::VisitedList()
{
	// Clear the list of visited locations.
	visited.clear();
	
	// Set the width, height, and list length.
	width=0;
	height=0;
	listLength=0;
}

// Set the 2D size.
void VisitedList::setSize(unsigned int length)
{
	if(length != listLength)
	{
		// Set the new list length.
		listLength=length;
		
		// Resize the visited.
		visited.resize(listLength, false);
	}
}

// Set the list's size.
void VisitedList::setSize(unsigned int newWidth, unsigned int newHeight)
{
	// If the list needs to be modified...
	if(newWidth != width || newHeight != height)
	{
		// Update the dimensions and calculate the length.
		width=newWidth;
		height=newHeight;

		listLength=width*height;
		// Resize the list, new spaces containing false.
		visited.resize(listLength, false);
	}
}

// Note that a point was visited. Moved from PlaneDetector.cpp.
void VisitedList::setVisited(Point2D point, bool visited)
{
	unsigned int index=point.x+point.y*width;

	if(index >= 0 && index<listLength)
	{
		this->visited.at(index)=visited;
	}
}

// Set whether a point at a given index mwas bvisited.
void VisitedList::setVisited(unsigned int index, bool setTo)
{
	// So long as in the list,
	if(index >= 0 && index < listLength)
	{
		this->visited.at(index)=setTo;
	}
}

// Get whether a point was visited. Moved from PlaneDetector.cpp.
bool VisitedList::getVisited(Point2D point)
{
	unsigned int index=point.x+point.y*width;

	if(index >= 0 && index<listLength)
	{
		return visited.at(index);
	}

	return true;
}

// Get whether an index was visited.
bool VisitedList::getVisited(unsigned int at)
{
	if(at >= 0 && at < listLength)
	{
		return visited.at(at);
	}
	
	return true;
}

// Clear the list.
void VisitedList::clear()
{
	visited.clear();
	listLength=0;
	width=0;
	height=0;
}

// Get the vector of visited locations.
std::vector<bool>& VisitedList::getVisited()
{
	return visited;
}

// Add all trues from another visited list not recorded here.
void VisitedList::addVisitedItemsFromOther(VisitedList & otherVisitedList)
{
	std::vector<bool> otherList=otherVisitedList.getVisited();

	// Create room for variables to be used in traversing the other list.
	unsigned int currentIndex=0,
		otherLength=otherList.size();

	bool otherValue;

	// For every element in the other list.
	for(currentIndex=0; currentIndex<otherLength && currentIndex < listLength; currentIndex++)
	{
		otherValue=otherList.at(currentIndex);
		
		if(otherValue == true && visited.at(currentIndex) == false)
		{
			visited.at(currentIndex) = otherValue;
		}
	}
}
