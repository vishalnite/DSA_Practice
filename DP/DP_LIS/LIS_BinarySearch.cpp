/*
Find the length of the LIS using Binary Search. We have already done it using DP which took a time complexity of O(N^2) but we can solve it in 
O(NlogN).

We make use of a temporary array to store subsequences and its length give us the length of LIS at the end.
If the element is greater than the last element in the array then insert it
Else replace it in the position just greater than or equal to the element [lowebound() function or create your own]
*/

#include<vector>

int longestIncreasingSubsequence(int arr[], int n)
{
    vector<int> temp;
    int len = 1;
    temp.push_back(arr[0]);

    for(int i = 1; i < n; i++) {
        if(arr[i] > temp.back()) {
            temp.push_back(arr[i]);
            len++;
        }
        else {
            int pos = lower_bound(temp.begin(), temp.end(), arr[i]) - temp.begin();
            temp[pos] = arr[i];
        }
    }

    return len;
}
