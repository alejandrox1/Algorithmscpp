#include <iostream>
#include <cstdlib>
#include <ctime>


template <typename T>
void selectionSort(T arr[], int n);
template <typename T>
int binSearch(const T arr[], int first, int last, const T& target);



int main(int argc, char **argv){
    
    int arr[5];
    int idx = -1; 
    std::srand(std::time(NULL));

    // Initialize array values
    for (int i=0; i<5; i++)
        arr[i] = std::rand() % 10 + 1;

    // Print original values to stdout
    for (int i=0; i<5; i++)
        std::cout<< arr[i] << ", ";
    std::cout<< '\n';

    // Sort array
    selectionSort(arr, 5);
    idx = binSearch(arr, 0, 5, 3);

    // Print sorted array
    std::cout<< "Array: ";
    for (int i=0; i<5; i++)
        std::cout<< arr[i] << ", ";
    std::cout<< '\n';

    std::cout<< "Index of 3: "<< idx << '\n';

    return 0;
}



template <typename T>
void selectionSort(T arr[], int n){
    int smallIndex;
    T temp;

    for (int i=0; i<n-1; i++)
    {
        smallIndex = i;
        for (int j=i+1; j<n; j++)
        {
            if (arr[smallIndex] > arr[j])
                smallIndex = j;
        }

        // If smallest is not at our current position then exchange them
        if (smallIndex != i)
        {
            temp = arr[i];
            arr[i] = arr[smallIndex];
            arr[smallIndex] = temp;
        }
    }
}


template <typename T>
int binSearch(const T arr[], int first, int last, const T& target){
    int mid;
    T midValue;

    while (first < last){
        mid = (first + last)/2;
        midValue = arr[mid];

        if (midValue==target)
            return mid;
        else if (target < midValue)
            last = mid;
        else
            first = mid + 1;
    }
    return -1;
}
