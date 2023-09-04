/*
Find the number of ways to make change from the given denominations. There is an infinite supply of coins of each denomination.
[Whenever there is a problem of infinite supply don't move after taking the value]
*/

/********************** Recursion *********************/
long countWays(int ind, int *denominations, int value) {
    if(value == 0)
        return 1;
    if(ind == 0) {
        if(value % denominations[0] == 0)
            return 1;
        else
            return 0;
    }

    long notTake = countWays(ind - 1, denominations, value);
    long take = 0;
    if(denominations[ind] <= value) {
        take = countWays(ind, denominations, value - denominations[ind]);
    }

    return notTake + take;
}

long countWaysToMakeChange(int *denominations, int n, int value)
{
    return countWays(n - 1, denominations, value);
}



/********************** Memoization *********************/
#include<vector>

long countWays(int ind, int *denominations, int value, vector<vector<long>> &dp) {
    if(value == 0)
        return 1;
    if(ind == 0) {
        if(value % denominations[0] == 0)
            return 1;
        else
            return 0;
    }

    if(dp[ind][value] != -1)
        return dp[ind][value];

    long notTake = countWays(ind - 1, denominations, value, dp);
    long take = 0;
    if(denominations[ind] <= value) {
        take = countWays(ind, denominations, value - denominations[ind], dp);
    }

    return dp[ind][value] = notTake + take;
}

long countWaysToMakeChange(int *denominations, int n, int value)
{
    vector<vector<long>> dp(n, vector<long>(value + 1, -1));
    countWays(n - 1, denominations, value, dp);
    return dp[n - 1][value];
}



/********************** Tabulation *********************/
#include<vector>

long countWaysToMakeChange(int *denominations, int n, int value)
{
    vector<vector<long>> dp(n, vector<long>(value + 1, 0));

    for(int i = 0; i < n; i++) {
        dp[i][0] = 1;
    }

    for(int j = 1; j <= value; j++) {
        if(j % denominations[0] == 0) 
            dp[0][j] = 1;
    }

    for(int i = 1; i < n; i++) {
        for(int j = 1; j <= value; j++) {
            long notTake = dp[i - 1][j];
            long take = 0;
            if(denominations[i] <= j) {
                take = dp[i][j - denominations[i]];
            }

            dp[i][j] = take + notTake;
        }
    }

    return dp[n - 1][value];
}



/********************** Space Optimization *********************/
#include<vector>

long countWaysToMakeChange(int *denominations, int n, int value)
{
    vector<long> prev(value + 1, 0), cur(value + 1, 0);

    prev[0] = cur[0] = 1;

    for(int j = 1; j <= value; j++) {
        if(j % denominations[0] == 0) 
            prev[j] = 1;
    }

    for(int i = 1; i < n; i++) {
        for(int j = 1; j <= value; j++) {
            long notTake = prev[j];
            long take = 0;
            if(denominations[i] <= j) {
                take = cur[j - denominations[i]];
            }

            cur[j] = take + notTake;
        }
        prev = cur;
    }

    return prev[value];
}