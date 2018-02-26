#include "ListHelper.h"

// Include standard input/output.
#include <iostream>

#include <math.h>

#include <cstdlib>

#include <vector>

// Test the sorting function.
void ListHelper::testSort()
{
	std::cout << "\nStarting merge sort test.";
	
	std::vector< ObjectSortingContainer<double> > list;
	
	for(double i = 0; i < 5; i++)
	{
		list.push_back(ObjectSortingContainer<double>((rand() % 10000)));
	}
	
	
	
	std::cout << "\nList: ";
	for(unsigned int index = 0; index < list.size(); index++)
	{
		std::cout << list.at(index).getValue() << ", ";
	}
	
	mergeSort(list, true);
	
	std::cout << "\nList: ";
	for(unsigned int index = 0; index < list.size(); index++)
	{
		std::cout << list.at(index).getValue() << ", ";
	}
	
	std::cout << "\n======\nMerge two.";
	
	list.clear();
	
	std::vector< ObjectSortingContainer<double> > list2;
	
	for(double i = 0; i < 5; i++)
	{
		list.push_back(ObjectSortingContainer<double>((rand() % 10000)));
		list2.push_back(ObjectSortingContainer<double>((rand() % 10000)));
	}
	
	list = mergeTwoSorted(list, list2, true);
	
	std::cout << "\nList: ";
	for(unsigned int index = 0; index < list.size(); index++)
	{
		std::cout << list.at(index).getValue() << ", ";
	}
}
