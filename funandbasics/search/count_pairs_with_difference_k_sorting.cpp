#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>


int binarySearch(std::vector<int> &arr, int low, int high, int x) {
	if (high >= low) {
		int mid = low + (high - low)/2;
		if (x == arr[mid]) {
			return mid;
		} else if (x > arr[mid]) {
			return binarySearch(arr, mid+1, high, x);
		} else {
			return binarySearch(arr, low, mid-1, x);
		}
	}
	return -1;
}


int countPairsWithDiffK(std::vector<int> &arr, int k) {
	int count = 0;

	// Sort array
	std::sort(arr.begin(), arr.end());

	// Search for val+k in array
	for (int i=0; i<arr.size(); i++){
		if (binarySearch(arr, i+1, arr.size()-1, arr[i]+k) != -1) {
			count++;
		}
	}
	return count;
}


int runTest(int testSize, int k) {
	std::vector<int> arr;
	for (int i=0; i<testSize; i++) {
		arr.push_back(i);
	}
	
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	std::cout << "Count of pairs with diff k = "<< k << " is "<< countPairsWithDiffK(arr, k) << '\n';
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
			                                                                                
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
				                                                                                
	std::cout<< "Array size: "<< testSize << ", Duration: "<<duration <<" microseconds.\n\n";

	return int(duration);
}

int main() {

	std::vector<int> durations;

	durations.push_back( runTest(10, 3) );
	durations.push_back( runTest(100, 3) );
	durations.push_back( runTest(1000, 3) );
	durations.push_back( runTest(10000, 3) );
	durations.push_back( runTest(100000, 3) );

	for (int i=durations.size()-1; i>0; i--) {
		std::cout<< durations[i]/durations[i-1] <<'\n';
	}

	return 0;
}
