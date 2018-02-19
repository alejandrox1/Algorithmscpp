#include <iostream>


template <typename T>
int seqSearch(const T arr[], int first, int last, const T& target);


int main(int argc, char **argv)
{
    int arr[6] = {0, 1, 2, 3, 4, 5};
    int idx=-1;

    idx = seqSearch(arr, 0, 6, 3);

    std::cout << idx << '\n';
    
    return 0;
}


template <typename T>
int seqSearch(const T arr[], int first, int last, const T& target){
    int i = first;
    while(i != last && arr[i] != target){
        i++;
    }

    if (arr[i]!=target)
        return -1;
    else
        return i;
}
