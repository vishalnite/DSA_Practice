/*
Count the number of ways to partition a set into two subsets such that s1 > s2 and the differnce between them is D.
----
s1 > s2
s1 = totSum - s2
s1 - s2 = d
totSum - s2 - s2 = d
s2 = (totSum - d)  / 2 [totSum - d >= 0 && totSum - d is even]

We also need to handle cases where the elements can be 0. And also take into account the cases when target is 0.
*/

/****************** Tabulation Problem *******************/
#include <bits/stdc++.h>

int countPartitions(int n, int d, vector<int> &arr) {
    int MOD = 1e9 + 7;

    int totSum = 0;
    for(int i : arr) {
        totSum += i;
    }

    if(totSum - d < 0 || (totSum - d) % 2)
        return 0;

    int k = (totSum - d) / 2;

    vector<vector<int>> dp(n, vector<int>(k + 1, 0));

    if(arr[0] == 0) dp[0][0] = 2;
    else dp[0][0] = 1;

    if(arr[0] != 0 && arr[0] <= k) {
        dp[0][arr[0]] = 1;
    }

    for(int ind = 1; ind < n; ind++) {
        for(int target = 0; target <= k; target++) {
            int notTake = dp[ind - 1][target];
            int take = 0;
            if(arr[ind] <= target) {
                take = dp[ind - 1][target - arr[ind]];
            }

            dp[ind][target] = (take + notTake) % MOD;
        }
    }

    return dp[n - 1][k];
}


