#include "ListHelper.h"

// Merge-sort a list.
template <typename templateType>
void ListHelper::mergeSort(std::vector< ObjectSortingContainer<templateType> >& input, bool leastToGreatest)
{
	unsigned int subListSize=2;
	std::vector< std::vector< ObjectSortingContainer<templateType> > > subVectors;
	subVectors.resize(input.size()/2);
	
	unsigned int index;
	
	for(unsigned int index = 0; index < input.size(); index+=2)
	{
		std::vector< ObjectSortingContainer<templateType> > current;
		current.resize(2);
		
		current.at(0) = input.at(index);
		
		if(index+1 < input.size())
		{
			current.at(1) = input.at(index+1);
			
			// Swap the two if necessary.
			if(current.at(0) > current.at(1) && leastToGreatest || current.at(0) < current.at(1) && !leastToGreatest)
			{
				 ObjectSortingContainer<templateType>  cachedValue=current.at(0);
				
				current.at(0)=current.at(1);
				
				current.at(1)=cachedValue;
			}
		}
	}
	
	while(subVectors.size() > 1)
	{
	
		std::vector< std::vector< ObjectSortingContainer<templateType> > > newSubVectors;
		
		// For every two sub-lists,
		for(index = 0; index < subVectors.size(); index+=2)
		{
			std::vector< ObjectSortingContainer<templateType> >& current=subVectors.at(index);
			
			// If there is a next,
			if(index+1 < subVectors.size())
			{
				std::vector< ObjectSortingContainer<templateType> >& next=subVectors.at(index+1);
				
				// Merge the current and the next.
				newSubVectors.push_back(mergeTwoSorted< ObjectSortingContainer<templateType> >(current, next, leastToGreatest));
			}
			else
			{
				newSubVectors.push_back(current);
			}
		}
		
		subVectors=newSubVectors;
	}
	
	// Re-assign the input to the only remaining subvector.
	input=subVectors.at(0);
}

// Merge two already sorted lists.
template <typename templateType>
std::vector< ObjectSortingContainer<templateType> > ListHelper::mergeTwoSorted(std::vector< ObjectSortingContainer<templateType> >& first, std::vector< ObjectSortingContainer<templateType> >& second, bool leastToGreatest)
{
	std::vector< ObjectSortingContainer<templateType> > result;

	 ObjectSortingContainer<templateType>  leftElement, rightElement;
	
	unsigned int leftListSize=first.size(), rightListSize=second.size();
	
	unsigned int leftIndex=0, rightIndex=0;
	
	while(leftIndex < leftListSize || rightIndex < rightListSize)
	{
		if(leftIndex < leftListSize)
		{
			leftElement=first[leftIndex];
		}
		
		if(rightIndex < rightListSize)
		{
			rightElement=second[rightIndex];
		}
		
		if((leftElement < rightElement && leastToGreatest) || (leftElement > rightElement && !leastToGreatest) || rightIndex >= rightListSize)
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
