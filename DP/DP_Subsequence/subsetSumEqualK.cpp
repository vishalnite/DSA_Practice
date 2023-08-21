/*
Find whether the sum of elements in a subsequence equals K.
[DP on subsequence -- Brute -- Generate all subsequence using power set or recursion]
[Optimal -- Use DP -- Find base cases and then apply the necessary operations]
*/

/*************** Recursion ******************/
#include <bits/stdc++.h> 

bool isPossible(int ind, int target, vector<int> &arr) {
    if(target == 0)
        return true;
    
    if(ind == 0) 
        return (arr[0] == target);

    bool notTake = isPossible(ind - 1, target, arr);
    bool take = false;
    if(arr[ind] <= target) 
        take = isPossible(ind - 1, target - arr[ind], arr);

    return take | notTake;
}

bool subsetSumToK(int n, int k, vector<int> &arr) {
    return isPossible(n - 1, k, arr);
}


/*************** Memoization ******************/
#include <bits/stdc++.h> 

bool isPossible(int ind, int target, vector<int> &arr, vector<vector<int>> &dp) {
    if(target == 0)
        return true;
    
    if(ind == 0) 
        return (arr[0] == target);

    if(dp[ind][target] != -1)
        return dp[ind][target];

    bool notTake = isPossible(ind - 1, target, arr, dp);
    bool take = false;
    if(arr[ind] <= target) 
        take = isPossible(ind - 1, target - arr[ind], arr, dp);

    return dp[ind][target] = take | notTake;
}

bool subsetSumToK(int n, int k, vector<int> &arr) {
    vector<vector<int>> dp(n, vector<int>(k + 1, -1));
    return isPossible(n - 1, k, arr, dp);
}


/*************** Tabulation ******************/
#include <bits/stdc++.h> 

bool subsetSumToK(int n, int k, vector<int> &arr) {
    vector<vector<bool>> dp(n, vector<bool>(k + 1, 0));

    for(int i = 0; i < n; i++) 
        dp[i][0] = true;
    dp[0][arr[0]] = true;

    for(int i = 1; i < n; i++) {
        for(int target = 1; target <= k; target++) {
            bool notTake = dp[i - 1][target];
            bool take = false;
            if(arr[i] <= target) {
                take = dp[i - 1][target - arr[i]];
            }

            dp[i][target] = take | notTake;
        }
    }

    return dp[n - 1][k];
}


/*************** Space Optimization ******************/
#include <bits/stdc++.h> 

bool subsetSumToK(int n, int k, vector<int> &arr) {
    vector<bool> prev(k + 1, 0), cur(k + 1, 0);
    prev[0] = cur[0] = true;
    
    prev[arr[0]] = true;

    for(int i = 1; i < n; i++) {
        for(int target = 1; target <= k; target++) {
            bool notTake = prev[target];
            bool take = false;
            if(arr[i] <= target) {
                take = prev[target - arr[i]];
            }

            cur[target] = take | notTake;
        }
        prev = cur;
    }

    return prev[k];
}