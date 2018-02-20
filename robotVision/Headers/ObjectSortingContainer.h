#pragma once

// A conainer for sorting objects.
template <typename T>
class ObjectSortingContainer
{
	public:
	ObjectSortingContainer<T>(double startingValue, T* startingObject) { value=startingValue; baseObject=startingObject; };
	T * baseObject; // The object the container starts with.
	
	// Operators relating to sorting.
	bool operator<(ObjectSortingContainer& other) { return other.getValue() < value; };
	bool operator>(ObjectSortingContainer& other) { return other.getValue() > value; };
	bool operator==(ObjectSortingContainer& other) { return other.getValue() == value; };
	
	double getValue();
	
	private:
	double value=0.0;
	
};

// Get the stored value.
template <typename T>
double ObjectSortingContainer<T>::getValue()
{
	return value;
}
