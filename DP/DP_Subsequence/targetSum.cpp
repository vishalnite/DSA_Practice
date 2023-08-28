/*
Find the number of ways to assign + ot - to the elements in an array such that their sum is equal to the target.
[It can be solved by taking +ve and -ve to the target and following the normal flow of DP]
but... but... but...
[This problem can be rephrased as count partition with the given difference]
[We basically need to partition the array into positive and negative sets such that their difference is the target]
Amazing, right?
*/

/************* Tabulation *************/
#include <bits/stdc++.h> 
int targetSum(int n, int target, vector<int> &arr) {
    int totSum = 0;
    for(int i : arr) {
        totSum += i;
    }

    if(totSum - target < 0 || (totSum - target) % 2)
        return 0;

    int k = (totSum - target) / 2;

    vector<vector<int>> dp(n, vector<int>(k + 1, 0));

    if(arr[0] == 0) dp[0][0] = 2;
    else dp[0][0] = 1;

    if(arr[0] != 0 && arr[0] <= k)
        dp[0][arr[0]] = 1;

    for(int ind = 1; ind < n; ind++) {
        for(int tar = 0; tar <= k; tar++) {
            int notTake = dp[ind - 1][tar];
            int take = 0;

            if(arr[ind] <= tar) {
                take = dp[ind - 1][tar - arr[ind]];
            }

            dp[ind][tar] = notTake + take;
        }
    }

    return dp[n - 1][k];
}
