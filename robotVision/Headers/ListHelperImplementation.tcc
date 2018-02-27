#pragma once

#include <iostream>
#include <sstream>

namespace ListHelper
{
	// Merge-sort a list.
	template <typename templateType>
	void mergeSort(std::vector< ObjectSortingContainer<templateType> >& input, bool leastToGreatest)
	{
		
		unsigned int subListSize=2;
		std::vector< std::vector< ObjectSortingContainer<templateType> > > subVectors;
		subVectors.reserve(input.size()/2);
		
		unsigned int index, inputSize = input.size();
		
		for(unsigned int index = 0; index < inputSize; index+=2)
		{
			
			std::vector< ObjectSortingContainer<templateType> > current;
			current.reserve(2);
			
			current.push_back(input.at(index));
			
			if(index+1 < inputSize)
			{
				current.push_back(input.at(index+1));
				
				// Swap the two if necessary.
				if(current.at(0) > current.at(1) && leastToGreatest || current.at(0) < current.at(1) && !leastToGreatest)
				{
					 ObjectSortingContainer<templateType> cachedValue=current.at(0);
					
					current.at(0)=current.at(1);
					
					current.at(1)=cachedValue;
				}
			}
			
			subVectors.push_back(current);
		}
		
		
		while(subVectors.size() > 1)
		{
			std::vector< std::vector< ObjectSortingContainer<templateType> > > newSubVectors;
			
			// For every two sub-lists,
			for(index = 0; index < subVectors.size(); index+=2)
			{
				std::vector< ObjectSortingContainer<templateType> >& current = subVectors.at(index);
				
				// If there is a next,
				if(index+1 < subVectors.size())
				{
					std::vector< ObjectSortingContainer<templateType> >& next=subVectors.at(index + 1);
					
					std::vector< ObjectSortingContainer<templateType> > newVector = mergeTwoSorted< templateType >(current, next, leastToGreatest);
					
					
					// Merge the current and the next.
					newSubVectors.push_back(newVector);
				}
				else
				{
					newSubVectors.push_back(current);
				}
			}
			
			subVectors=newSubVectors;
		}
		
		if(subVectors.size() > 0)
		{
			// Re-assign the input to the only remaining subvector (this works in c++).
			input=subVectors.at(0);
		}
	}

	// Merge two already sorted lists.
	template <typename templateType>
	std::vector< ObjectSortingContainer<templateType> > mergeTwoSorted(const std::vector< ObjectSortingContainer<templateType> >& first, const std::vector< ObjectSortingContainer<templateType> >& second, bool leastToGreatest)
	{
		std::vector< ObjectSortingContainer<templateType> > result;

		ObjectSortingContainer<templateType>  leftElement, rightElement;
	
		
		unsigned int leftListSize=first.size(), rightListSize=second.size();
		
		unsigned int leftIndex=0, rightIndex=0;
		
		
		while(leftIndex < leftListSize || rightIndex < rightListSize)
		{
			if(leftIndex < leftListSize)
			{
				leftElement=first.at(leftIndex);
			}
			
			if(rightIndex < rightListSize)
			{
				rightElement=second.at(rightIndex);
			}
			
			if(((leftElement < rightElement && leastToGreatest) || (leftElement > rightElement && !leastToGreatest) || rightIndex >= rightListSize) && leftIndex < leftListSize)
			{
				result.push_back(leftElement);
				leftIndex++;
			}
			else
			{
				result.push_back(rightElement);
				rightIndex++;
			}
		}
		
		return result;
	}
}
