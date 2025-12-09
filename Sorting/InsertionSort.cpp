#include<bits/stdc++.h>
using namespace std;

/* In insertion sort, we shift elements and put the element in their correct positions instead of swapping the smallest one.
We run two loops.
The outer loop runs from 1 to n - 1.
We run an inner loop until we find the correct position for the current element. If moving in the left part we shift the element unless we find an element
less than or equal to the current element.
T.C - O(N^2)
S.C - O(1)
*/

void insertionSort(vector<int> &arr, int n) {
    for(int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// int main() {
//     vector<int> arr {13, 46, 52, 9, 10, 21};

//     insertionSort(arr, 6);

//     for(int i = 0; i < 6; i++) {
//         cout << arr[i] << " ";
//     }
// }
