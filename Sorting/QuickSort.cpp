#include<bits/stdc++.h>
using namespace std;

/* Quick sort uses divide and conquer technique.
We use recursion just like merge sort. So the recursive call is similar to it.
First we find a pivot element. The pivot element can be anything in the array.
We need to put the pivot in its correct position in the array.
That position can be considered as the partition index and then the array is divided into two parts.

TO find the partition index-
we put two pointers i at the low and j at the hign.
Increment i until we find element greater than pivot element and decrement j until we find element smaller then pivot.
If i < j, we swap the elements
else we come out of loop and swap jth element with the pivot. 
jth index is the partition index.

T.C - O(NlogN)  worst case - O(N^2)
S.C - O(1) - Better than Merge Sort for some cases
*/

int partitionArray(vector<int> &arr, int low, int high) {
    int pivot = low;
    int i = low, j = high;

    while(i < j) {
        while(arr[i] <= arr[pivot] && i < high) {
            i++;
        }
        while(arr[j] > arr[pivot] && j > low) {
            j--;
        }

        if(i < j) {
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[j], arr[pivot]);

    return j;
}

void quickSort(vector<int> &arr, int low, int high) {
    if(low < high) {
        int partitionIndex = partitionArray(arr, low, high);
        quickSort(arr, low, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, high);
    }
}

// int main() {
//     vector<int> arr {13, 46, 52, 9, 10, 21};

//     quickSort(arr, 0, 5);

//     for(int i = 0; i < 6; i++) {
//         cout << arr[i] << " ";
//     }
// }