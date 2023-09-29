/*
How to approach partition DP problems:
1. Start with the entire block or array.
2. Try all partitions [Run a loop to try all partitions -- this is the most crucial stage to figure out]
3. Return the best 2 partitions 

Here we are given an array of size N which denotes N - 1 matrices. The matrix size is given by A[i - 1] * A[i].
We need to find the minimum number of operations that can be performed by partitioning the array.
The array can be partitioned in many ways so, we will explore all ways.

Eg - Two array -- A[10x20] & B[20x30]
    Operations = 10x20x30 = 6000

We will start with the entire block i.e, 1 to N - 1 and the base case will be if (i == j) then the number of operations will be 0.
The most crucial stage -- Figure out partitions
    We will run a loop from k = i to j - 1 [j - 1 because we want all possible partitions]
    Then steps would be A[i - 1] x A[k] x A[j] + f(i, k) + f(k + 1, j)
    Find the minimum at each partition. 
*/


/************************ Recursion ***********************/
int f(int i, int j, int *arr) {
    if(i == j)
        return 0;

    int mini = 1e9;
    for(int k = i; k < j; k++) {
        int steps = arr[i - 1] * arr[k] * arr[j]
                + f(i, k, arr) 
                + f(k + 1, j, arr);
        if(steps < mini)
            mini = steps;
    }

    return mini;
}

int matrixChainMultiplication(int* arr, int n) {
    return f(1, n, arr);
}




/************************ Memoization ***********************/
#include<vector>

int f(int i, int j, int *arr, vector<vector<int>> &dp) {
    if(i == j)
        return dp[i][j] = 0;

    if(dp[i][j] != -1)
        return dp[i][j];

    int mini = 1e9;
    for(int k = i; k < j; k++) {
        int steps = arr[i - 1] * arr[k] * arr[j]
                + f(i, k, arr, dp) 
                + f(k + 1, j, arr, dp);
        if(steps < mini)
            mini = steps;
    }

    return dp[i][j] = mini;
}

int matrixChainMultiplication(int* arr, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
    return f(1, n, arr, dp);
}




/************************ Tabulation ***********************/
#include<vector>

int matrixChainMultiplication(int* arr, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for(int i = n; i >= 1; i--) {
        for(int j = i + 1; j <= n; j++) {
            int mini = 1e9;
            for(int k = i; k < j; k++) {
                int steps = arr[i - 1] * arr[k] * arr[j] + dp[i][k] + dp[k + 1][j];
                mini = min(mini, steps);
            }
            dp[i][j] = mini;
        }
    }

    return dp[1][n];
}
