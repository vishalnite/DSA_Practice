#include<bits/stdc++.h>
using namespace std;

/* In selection sort, the array is divided into two parts: sorted and unsorted. 
The outer loop runs from 0 to n - 2
The inner loop runs from index of outer loop to n - 1 and finds the smallest element from the unsorted part of the aaray. 
After this the smallest element is swapped with the first element in the unsorted part and is made sorted.
*/

void selectionSort(vector<int> &arr, int n) {
    for(int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for(int j = i + 1; j < n; j++) {
            if(arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// int main() {
//     vector<int> arr {13, 46, 52, 9, 10, 21};

//     selectionSort(arr, 6);

//     for(int i = 0; i < 6; i++) {
//         cout << arr[i] << " ";
//     }
// }