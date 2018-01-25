#ifndef UTILITY_FUNCTIONS
#define UTILITY_FUNCTIONS

#include <iostream>
#include <list>
#include <string>


template <typename T>
void writeList(const std::list<T>& aList, const std::string& sep = " ");


template <typename T>
void writeList(const std::list<T>& aList, const std::string& sep)
{
	typename std::list<T>::const_iterator iter;

	for (iter = aList.begin(); iter != aList.end(); iter++)
		std::cout << *iter << sep;
	std::cout << '\n';
}


#endif // UTILITY_FUNCTIONS
