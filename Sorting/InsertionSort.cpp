#include<bits/stdc++.h>
using namespace std;

/* In insertion sort, we shift elements and put the element in their correct positions instead of swapping the smallest one.
We run two loops.
The outer loop runs from 0 to n - 1.
The inner loop runs from i to 1. If the current element is less than the previous element then we shift it to its right position. 
T.C - O(N^2)
S.C - O(1)
*/

void insertionSort(vector<int> &arr, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = i; j > 0; j--) {
            if(arr[j] < arr[j - 1]) {
                swap(arr[j], arr[j - 1]);
            }
        }
    }
}

int main() {
    vector<int> arr {13, 46, 52, 9, 10, 21};

    insertionSort(arr, 6);

    for(int i = 0; i < 6; i++) {
        cout << arr[i] << " ";
    }
}