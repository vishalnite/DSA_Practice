#include<bits/stdc++.h>
using namespace std;

/* Merge sort uses divide and conquer technique.
We use a recursive function to divide the array hypothetically into two part. The division is done until a single element is left.
The base condition is if (low >= high) then return.
We use a function merge that merges the two sorted array. 
It stores the element into a temporary array and after merging puts the sorted elemen into the original array.
[NOTE: The recursive call first divides the left of the array and then moves to the right.]
T.C - O(NlogN) - in all the cases
S.C - O(N)
*/

void merge(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp;
    int left = low, right = mid + 1;

    while(left <= mid && right <= high) {
        if(arr[left] < arr[right]) {
            temp.push_back(arr[left]);
            left++;
        }
        else {
            temp.push_back(arr[right]);
            right++;
        }
    }

    while(left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }

    while(right <= high) {
        temp.push_back(arr[right]);
        right++;
    }

    for(int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }
}

void mergeSort(vector<int> &arr, int low, int high) {
    if(low >= high)
        return;

    int mid = (low + high) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

// int main() {
//     vector<int> arr {13, 46, 52, 9, 10, 21};

//     mergeSort(arr, 0, 5);

//     for(int i = 0; i < 6; i++) {
//         cout << arr[i] << " ";
//     }
// }