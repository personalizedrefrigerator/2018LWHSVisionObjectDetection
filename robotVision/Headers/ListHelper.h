#pragma once

// Include needed standard libraries.
#include<vector>

// Include files from this project.
#include "ObjectSortingContainer.h"

// Functions to help manage lists.

namespace ListHelper
{
	
	template <typename templateType>
	void mergeSort(std::vector< ObjectSortingContainer<templateType> >& input, bool leastToGreatest); // Merge-sort the input.
	
	template <typename templateType>
	void mergeTwoSorted(std::vector< ObjectSortingContainer<templateType> >& first, std::vector< ObjectSortingContainer<templateType> >& second, bool leastToGreatest); // Merge two sorted lists.
};


