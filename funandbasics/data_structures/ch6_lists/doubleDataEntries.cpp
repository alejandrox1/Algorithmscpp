#include <list>
#include "util.h"


template <typename T>
void doubleData(std::list<T>& aList); 


int main()
{
	int arr[] = {2, 3, 5};
	int arrSize = sizeof(arr)/sizeof(int);
	std::list<int> intList(arr, arr+arrSize);

	writeList(intList);
	doubleData(intList);
	writeList(intList);

	return 0;
}

template <typename T>
void doubleData(std::list<T>& aList)
{
	typename std::list<T>::iterator iter = aList.begin();

	while (iter != aList.end())
	{
		aList.insert(iter, *iter);
		iter++;
	}
}
