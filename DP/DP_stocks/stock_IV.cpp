/*
Similar to stock III problem but here at most K transactions can be performed. We just need to change cap from 2 to k and it will work fine. 
But we will use the alternate method discussed. [using 2 * k number of operations]
*/

/******************* Recursion *******************/
#include <bits/stdc++.h> 

int f(int ind, int tranNo, vector<int> &prices, int n, int k) {
    if(ind == n || tranNo == 2 * k)
        return 0;

    if(tranNo % 2 == 0) {
        return max(-prices[ind] + f(ind + 1, tranNo + 1, prices, n, k),
                                    f(ind + 1, tranNo, prices, n, k));
    }
    else {
        return max(prices[ind] + f(ind + 1, tranNo + 1, prices, n, k),
                                    f(ind + 1, tranNo, prices, n, k));
    }
}

int maximumProfit(vector<int> &prices, int n, int k)
{
    return f(0, 0, prices, n, k);
}




/******************* Memoization *******************/
#include <bits/stdc++.h> 

int f(int ind, int tranNo, vector<int> &prices, int n, int k, vector<vector<int>> &dp) {
    if(ind == n || tranNo == 2 * k)
        return 0;

    if(dp[ind][tranNo] != -1)
        return dp[ind][tranNo];

    if(tranNo % 2 == 0) {
        return dp[ind][tranNo] = max(-prices[ind] + f(ind + 1, tranNo + 1, prices, n, k, dp),
                                    f(ind + 1, tranNo, prices, n, k, dp));
    }
    else {
        return dp[ind][tranNo] = max(prices[ind] + f(ind + 1, tranNo + 1, prices, n, k, dp),
                                    f(ind + 1, tranNo, prices, n, k, dp));
    }
}

int maximumProfit(vector<int> &prices, int n, int k)
{
    vector<vector<int>> dp(n, vector<int>(2 * k, -1));
    return f(0, 0, prices, n, k, dp);
}




/******************* Tabulation *******************/
#include <bits/stdc++.h> 

int maximumProfit(vector<int> &prices, int n, int k)
{
    vector<vector<int>> dp(n + 1, vector<int>(2 * k + 1, 0));
    
    for(int ind = n - 1; ind >= 0; ind--) {
        for(int tranNo = 2 * k - 1; tranNo >= 0; tranNo--) {
            if(tranNo % 2 == 0) {
                dp[ind][tranNo] = max(-prices[ind] + dp[ind + 1][tranNo + 1], dp[ind + 1][tranNo]);
            }
            else {
                dp[ind][tranNo] = max(prices[ind] + dp[ind + 1][tranNo + 1], dp[ind + 1][tranNo]);
            }
        }
    }
    
    return dp[0][0];
}




/******************* Space Optimization *******************/
#include <bits/stdc++.h> 

int maximumProfit(vector<int> &prices, int n, int k)
{
    vector<int> after(2 * k + 1, 0), cur(2 * k + 1, 0);
    
    for(int ind = n - 1; ind >= 0; ind--) {
        for(int tranNo = 2 * k - 1; tranNo >= 0; tranNo--) {
            if(tranNo % 2 == 0) {
                cur[tranNo] = max(-prices[ind] + after[tranNo + 1], after[tranNo]);
            }
            else {
                cur[tranNo] = max(prices[ind] + after[tranNo + 1], after[tranNo]);
            }
        }
        after = cur;
    }
    
    return after[0];
}
