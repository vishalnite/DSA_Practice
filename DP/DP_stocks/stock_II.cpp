/*
We can perform any number of transactions but the transactions should be performed one at a time. If we already have a stock then we need to sell
it first.

We can have two states whether we want to buy the stock or sell it. So we need to carry a state for it. Be careful with the states.
*/

/******************* Recursion **********************/
long f(int ind, int buy, long *values, int n) {
    if(ind == n)
        return 0;

    long profit = 0;
    if(buy) {
        profit = max(-values[ind] + f(ind + 1, 0, values, n),
                                    f(ind + 1, 1, values, n));
    }
    else {
        profit = max(values[ind] + f(ind + 1, 1, values, n),
                                    f(ind + 1, 0, values, n));
    }

    return profit;
}

long getMaximumProfit(long *values, int n)
{
    return f(0, 1, values, n);
}



/******************* Memoization **********************/
#include<vector>

long f(int ind, int buy, long *values, int n, vector<vector<long>> &dp) {
    if(ind == n)
        return 0;

    if(dp[ind][buy] != -1)
        return dp[ind][buy];

    long profit = 0;
    if(buy) {
        profit = max(-values[ind] + f(ind + 1, 0, values, n, dp),
                                    f(ind + 1, 1, values, n, dp));
    }
    else {
        profit = max(values[ind] + f(ind + 1, 1, values, n, dp),
                                    f(ind + 1, 0, values, n, dp));
    }

    return dp[ind][buy] = profit;
}

long getMaximumProfit(long *values, int n)
{
    vector<vector<long>> dp(n + 1, vector<long>(2, -1));
    return f(0, 1, values, n, dp);
}



/******************* Tabulation **********************/
#include<vector>

long getMaximumProfit(long *values, int n)
{
    vector<vector<long>> dp(n + 1, vector<long>(2, 0));
    
    for(int ind = n - 1; ind >= 0; ind--) {
        for(int buy = 0; buy <= 1; buy++) {
            long profit = 0;
            if(buy) {
                profit = max(-values[ind] + dp[ind + 1][0], dp[ind + 1][1]);
            }
            else {
                profit = max(values[ind] + dp[ind + 1][1], dp[ind + 1][0]);
            }

            dp[ind][buy] = profit;
        }
    }

    return dp[0][1];
}



/******************* Space Optimization **********************/
//Using Two 2-sized array -- space - O(1) only but it can be done using 4 variables
#include<vector>

long getMaximumProfit(long *values, int n)
{
    vector<long> ahead(2, 0), cur(2, 0);
    
    for(int ind = n - 1; ind >= 0; ind--) {
        for(int buy = 0; buy <= 1; buy++) {
            long profit = 0;
            if(buy) {
                profit = max(-values[ind] + ahead[0], ahead[1]);
            }
            else {
                profit = max(values[ind] + ahead[1], ahead[0]);
            }

            cur[buy] = profit;
        }
        ahead = cur;
    }

    return ahead[1];
}