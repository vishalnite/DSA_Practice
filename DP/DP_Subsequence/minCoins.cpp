/*
Find the minimum number of coins required to form a denomination. 
[Greedy won't work since there is no uniformity]
[Use DP on subsequence like knapsack problem]
[Thumb rule -- Whenever there is an unlimited supply of something then at take case do not move from the index instead reduce the target]
*/


/******************** Recursion *********************/
#include <bits/stdc++.h>

int findMinElements(int ind, int target, vector<int> &num) {
    if(ind == 0) {
        if(target % num[0] == 0)
            return target / num[0];
        else 
            return 1e9;
    }

    int notTake = 0 + findMinElements(ind - 1, target, num);
    int take = 1e9;
    if(num[ind] <= target) {
        take = 1 + findMinElements(ind, target - num[ind], num);
    }

    return min(take, notTake);
}

int minimumElements(vector<int> &num, int x)
{
    int n = num.size();
    
    int ans = findMinElements(n - 1, x, num);

    if(ans == 1e9)
        return -1;
    return ans;
}



/******************** Memoization *********************/
#include <bits/stdc++.h>

int findMinElements(int ind, int target, vector<int> &num, vector<vector<int>> &dp) {
    if(ind == 0) {
        if(target % num[0] == 0)
            return target / num[0];
        else 
            return 1e9;
    }

    if(dp[ind][target] != -1)
        return dp[ind][target];

    int notTake = 0 + findMinElements(ind - 1, target, num, dp);
    int take = 1e9;
    if(num[ind] <= target) {
        take = 1 + findMinElements(ind, target - num[ind], num, dp);
    }

    return dp[ind][target] = min(take, notTake);
}

int minimumElements(vector<int> &num, int x)
{
    int n = num.size();
    vector<vector<int>> dp(n, vector<int>(x + 1, -1));
    int ans = findMinElements(n - 1, x, num, dp);

    if(ans == 1e9)
        return -1;
    return ans;
}



/******************** Tabulation *********************/
#include <bits/stdc++.h>

int minimumElements(vector<int> &num, int x)
{
    int n = num.size();
    vector<vector<int>> dp(n, vector<int>(x + 1, 1e9));
    
    for(int tar = 0; tar <= x; tar++) {
        if(tar % num[0] == 0)
            dp[0][tar] = tar / num[0];
    }

    for(int ind = 1; ind < n; ind++) {
        for(int tar = 0; tar <= x; tar++) {
            int notTake = 0 + dp[ind - 1][tar];
            int take = 1e9;

            if(num[ind] <= tar) {
                take = 1 + dp[ind][tar - num[ind]];
            }

            dp[ind][tar] = min(take, notTake);
        }
    }

    if(dp[n - 1][x] == 1e9)
        return -1;
    return dp[n - 1][x];
}



/******************** Space Optimization *********************/
/* Single array optimization -- Simple observation */
#include <bits/stdc++.h>

int minimumElements(vector<int> &num, int x)
{
    int n = num.size();
    vector<int> prev(x + 1, 1e9);
    
    for(int tar = 0; tar <= x; tar++) {
        if(tar % num[0] == 0)
            prev[tar] = tar / num[0];
    }

    for(int ind = 1; ind < n; ind++) {
        for(int tar = 0; tar <= x; tar++) {
            int notTake = 0 + prev[tar];
            int take = 1e9;

            if(num[ind] <= tar) {
                take = 1 + prev[tar - num[ind]];
            }

            prev[tar] = min(take, notTake);
        }
    }

    if(prev[x] == 1e9)
        return -1;
    return prev[x];
}