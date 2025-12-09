#include<bits/stdc++.h>
using namespace std;

/* In bubble sort, we try to put the largest element to the end of the array.
We run two loops.
The outer loop runs from 0 to n - 2.
The inner loop runs from 0 to n - i - 1. The elements are swapped if arr[index] > arr[index + 1]
In every pass we reduce the number of iterations because the last element in that range is the largest element.
T.C - O(N^2)
S.C - O(1)
*/

void bubbleSort(vector<int> &arr, int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// int main() {
//     vector<int> arr {13, 46, 52, 9, 10, 21};

//     bubbleSort(arr, 6);

//     for(int i = 0; i < 6; i++) {
//         cout << arr[i] << " ";
//     }
// }
