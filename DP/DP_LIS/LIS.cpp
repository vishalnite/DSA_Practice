/*
Longest Increasing Subsequence -- Subsequence where elements are in strictly increasing order.

- Function having cur_ind and prev_ind
- We either take the element or we do not take it
- We take it only if prev = -1 or the cur_elem is greater than prev_elem

The best complexity solution for this problem is O(NlogN) which uses binary search.
So the memoization solution gives runtime error due to the constraints.
Tabulation code will also give runtime error but tabulation code can be written in a space complexity of O(N) and thus, it will not
give runtime error.

Tabulation -- O(N) space complexity
- Initially we store 1 for every element of the array
- We run a loop from 0 to ind - 1 and see if the current element is greater than the previous one
- If it is, then put the max of the cur value and 1 + prev_value
- We also store the longest increasing subsequence upto the given element in a hash array
- We need this array to trace back in the array to print LIS
*/

/*********************** Recursion ************************/
int f(int ind, int prev_ind, int arr[], int n) {
    if(ind == n)
        return 0;

    int len = f(ind + 1, prev_ind, arr, n);

    if(prev_ind == -1 || arr[ind] > arr[prev_ind]) {
        len = max(len, 1 + f(ind + 1, ind, arr, n));
    }

    return len;
}

int longestIncreasingSubsequence(int arr[], int n)
{
    return f(0, -1, arr, n);
}





/*********************** Memoization ************************/
#include<vector>

int f(int ind, int prev_ind, int arr[], int n, vector<vector<int>> &dp) {
    if(ind == n)
        return 0;

    if(dp[ind][prev_ind + 1] != -1)
        return dp[ind][prev_ind + 1];

    int len = f(ind + 1, prev_ind, arr, n, dp);

    if(prev_ind == -1 || arr[ind] > arr[prev_ind]) {
        len = max(len, 1 + f(ind + 1, ind, arr, n, dp));
    }

    return dp[ind][prev_ind + 1] = len;
}

int longestIncreasingSubsequence(int arr[], int n)
{
    vector<vector<int>> dp(n, vector<int>(n + 1, -1));
    return f(0, -1, arr, n, dp);
}




/*********************** Tabulation ************************/
#include<vector>

int longestIncreasingSubsequence(int arr[], int n)
{
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for(int ind = n - 1; ind >= 0; ind--) {
        for(int prev_ind = ind - 1; prev_ind >= -1; prev_ind--) {
            int len = dp[ind + 1][prev_ind + 1];

            if(prev_ind == -1 || arr[ind] > arr[prev_ind]) {
                len = max(len, 1 + dp[ind + 1][ind + 1]);
            }

            dp[ind][prev_ind + 1] = len;
        }
    }

    return dp[0][0];
}





/*********************** Space Optimization ************************/
#include<vector>

int longestIncreasingSubsequence(int arr[], int n)
{
    vector<int> next(n + 1, 0), cur(n + 1, 0);

    for(int ind = n - 1; ind >= 0; ind--) {
        for(int prev_ind = ind - 1; prev_ind >= -1; prev_ind--) {
            int len = next[prev_ind + 1];

            if(prev_ind == -1 || arr[ind] > arr[prev_ind]) {
                len = max(len, 1 + next[ind + 1]);
            }

            cur[prev_ind + 1] = len;
        }
        next = cur;
    }

    return next[0];
}



/*********************** Tabulation with O(N) space ************************/
#include<vector>

int longestIncreasingSubsequence(int arr[], int n)
{
    vector<int> dp(n, 1);
    int maxi = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++) {
            if(arr[j] < arr[i]) {
                dp[i] = max(dp[i], 1 + dp[j]);
            } 
        }
        maxi = max(maxi, dp[i]);
    }

    return maxi;
}
