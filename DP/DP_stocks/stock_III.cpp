/*
Similar to stock II problem but the maximum transaction allowed is only 2.

Here we need to keep track of three variables and apply recursion accordingly. [dp[n][2][3] -- but(0/1) -- cap(0/1/2)]
There is another way where we make use of dp[n][4].
- 4 defines the transactions [B S B S]
- Even indices for buy and odd indices for sell
*/

/********************* Recursion **********************/
int f(int ind, int buy, int cap, vector<int> &prices, int n) {
    if(ind == n || cap == 0)
        return 0; 

    if(buy) {
        return max(-prices[ind] + f(ind + 1, 0, cap, prices, n), 
                    f(ind + 1, 1, cap, prices, n));
    }
    else {
        return max(prices[ind] + f(ind + 1, 1, cap - 1, prices, n),
                    f(ind + 1, 0, cap, prices, n));
    }
}

int maxProfit(vector<int>& prices)
{
    int n = prices.size();
    return f(0, 1, 2, prices, n);
}



/********************* Memoization **********************/
int f(int ind, int buy, int cap, vector<int> &prices, int n, vector<vector<vector<int>>> &dp) {
    if(ind == n || cap == 0)
        return 0; 

    if(dp[ind][buy][cap] != -1)
        return dp[ind][buy][cap];

    if(buy) {
        return dp[ind][buy][cap] = max(-prices[ind] + f(ind + 1, 0, cap, prices, n, dp), 
                    f(ind + 1, 1, cap, prices, n, dp));
    }
    else {
        return dp[ind][buy][cap] = max(prices[ind] + f(ind + 1, 1, cap - 1, prices, n, dp),
                    f(ind + 1, 0, cap, prices, n, dp));
    }
}

int maxProfit(vector<int>& prices)
{
    int n = prices.size();
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>> (2, vector<int>(3, -1)));
    return f(0, 1, 2, prices, n, dp);
}



/********************* Tabulation **********************/
// Tabulation gave TLE
int maxProfit(vector<int>& prices)
{
    int n = prices.size();
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>> (2, vector<int>(3, 0)));
    
    for(int ind = n - 1; ind >= 0; ind--) {
        for(int buy = 0; buy <= 1; buy++) {
            for(int cap = 1; cap <= 2; cap++) {
                if(buy) {
                    dp[ind][buy][cap] = max(-prices[ind] + dp[ind + 1][0][cap], dp[ind + 1][1][cap]);
                }
                else {
                    dp[ind][buy][cap] = max(prices[ind] + dp[ind + 1][1][cap - 1], dp[ind + 1][0][cap]);
                }
            }
        }
    }
    
    return dp[0][1][2];
}



/********************* Space Optimization **********************/
// Ran perfectly
int maxProfit(vector<int>& prices)
{
    int n = prices.size();
    vector<vector<int>> after(2, vector<int>(3, 0)), cur(2, vector<int>(3, 0));
    
    for(int ind = n - 1; ind >= 0; ind--) {
        for(int buy = 0; buy <= 1; buy++) {
            for(int cap = 1; cap <= 2; cap++) {
                if(buy) {
                    cur[buy][cap] = max(-prices[ind] + after[0][cap], after[1][cap]);
                }
                else {
                    cur[buy][cap] = max(prices[ind] + after[1][cap - 1], after[0][cap]);
                }
            }
        }
        after = cur;
    }
    
    return after[1][2];
}