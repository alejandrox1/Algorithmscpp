#include <iostream>
#include <chrono>
#include <vector>


int countPairsWithDiffK(std::vector<int> &arr, int n, int k) {
	int count = 0;

	for (int i=0; i<n; i++) {
		for (int j=i+1; j<n;j++) {
			if (arr[i] - arr[j] == k || arr[j] - arr[i] == k) {
				count++;
				//std::cout << arr[i] <<", "<< arr[j] << '\n';
			}
		}
	}
}


int runTest(int testSize, int k) {
	std::vector<int> arr;
	for (int i=0; i<testSize; i++) {
		arr.push_back(i);
	}
	
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	std::cout << "Count of pairs with diff k = "<< k << " is "<< countPairsWithDiffK(arr, testSize, k) << '\n';
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
