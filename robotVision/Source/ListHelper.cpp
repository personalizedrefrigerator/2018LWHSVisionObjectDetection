#include "ListHelper.h"

#include "Logging.h"

// Standard libraries.
#include <math.h>
#include <cstdlib>
#include <vector>

// Test the sorting function.
void ListHelper::testSort()
{
	Logging::log("Starting merge sort test.");
	
	std::vector< ObjectSortingContainer<double> > list;
	
	for(double i = 0; i < 5; i++)
	{
		list.push_back(ObjectSortingContainer<double>((rand() % 10000)));
	}
	
	
	
	Logging::log("List");
	for(unsigned int index = 0; index < list.size(); index++)
	{
		Logging::log << list.at(index).getValue() << ", ";
	}
	
	mergeSort(list, true);
	
	Logging::log("List: ");
	for(unsigned int index = 0; index < list.size(); index++)
	{
		Logging::log << list.at(index).getValue() << ", ";
	}
	
	Logging::log("======\nMerge two.");
	
	list.clear();
	
	std::vector< ObjectSortingContainer<double> > list2;
	
	for(double i = 0; i < 5; i++)
	{
		list.push_back(ObjectSortingContainer<double>((rand() % 10000)));
		list2.push_back(ObjectSortingContainer<double>((rand() % 10000)));
	}
	
	list = mergeTwoSorted(list, list2, true);
	
	Logging::log("List: ");

	for(unsigned int index = 0; index < list.size(); index++)
	{
		Logging::log << list.at(index).getValue() << ", ";
	}
}
