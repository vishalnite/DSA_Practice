/*
We need to print all the possible subsequences of an array. A subsequence is a contiguous/ non-contiguous sequence in order.

The pattern to solve this problem is (Take / Not-take). At a particular index you either decide to pick an element or not pick it.
This way when all the recursive calls are over, you have all the possible subsequences.

T.C - O(2^N) -- Two function calls for all N
S.C - O(N) -- At max there won't be more than N function calls awaiting in the stack space.
*/

#include<bits/stdc++.h>
using namespace std;

void printSubsequences(int i, vector<int> &sub, vector<int> &arr, int n) {
    if(i == n) {
        // Printing the current subsequence
        cout << "[ ";
        for(int x: sub) {
            cout << x << " ";
        }
        cout << "]" << endl;
        return;
    }

    // Take the current element in the subsequence
    sub.push_back(arr[i]);
    printSubsequences(i + 1, sub, arr, n);
    // Do not take the current element in the subsequence
    sub.pop_back();
    printSubsequences(i + 1, sub, arr, n);
}

int main() {
    vector<int> arr = {3, 1, 2};
    vector<int> sub;
    printSubsequences(0, sub, arr, arr.size());

    return 0;
}