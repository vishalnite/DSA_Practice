/*
Buy and sell stocks with a cooldown. Here we can perform infinite transactions but we cannot immediately buy another stock after selling one stock i.e, 
if we sell a stock at ith day then we can buy another stock on (i + 2)th day.
It is similar to stock II problem but with a cooldown.
*/

/**************** Recursion ********************/
int f(int ind, int buy, vector<int> &prices, int n) {
    if(ind >= n)
        return 0;

    if(buy) {
        return max(-prices[ind] + f(ind + 1, 0, prices, n), 
                                    f(ind + 1, 1, prices, n));
    }
    else {
        return max(prices[ind] + f(ind + 2, 1, prices, n),
                                    f(ind + 1, 0, prices, n));
    }
}

int stockProfit(vector<int> &prices){
    int n = prices.size();
    return f(0, 1, prices, n);
}



/**************** Memoization ********************/
int f(int ind, int buy, vector<int> &prices, int n, vector<vector<int>> &dp) {
    if(ind >= n)
        return 0;

    if(dp[ind][buy] != -1)
        return dp[ind][buy];

    if(buy) {
        return dp[ind][buy] = max(-prices[ind] + f(ind + 1, 0, prices, n, dp), 
                                    f(ind + 1, 1, prices, n, dp));
    }
    else {
        return dp[ind][buy] = max(prices[ind] + f(ind + 2, 1, prices, n, dp),
                                    f(ind + 1, 0, prices, n, dp));
    }
}

int stockProfit(vector<int> &prices){
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int>(2, -1));
    return f(0, 1, prices, n, dp);
}



/**************** Tabulation ********************/
int stockProfit(vector<int> &prices){
    int n = prices.size();
    vector<vector<int>> dp(n + 2, vector<int>(2, 0));

    for(int ind = n - 1; ind >= 0; ind--) {
        for(int buy = 0; buy <= 1; buy++) {
            if(buy) {
                dp[ind][buy] = max(-prices[ind] + dp[ind + 1][0], dp[ind + 1][1]);
            }
            else {
                dp[ind][buy] = max(prices[ind] + dp[ind + 2][1], dp[ind + 1][0]);
            }
        }
    }

    return dp[0][1];
}



/**************** Space Optimization ********************/
int stockProfit(vector<int> &prices){
    int n = prices.size();
    vector<int> after2(2, 0), after(2, 0), cur(2, 0);

    for(int ind = n - 1; ind >= 0; ind--) {
        for(int buy = 0; buy <= 1; buy++) {
            if(buy) {
                cur[buy] = max(-prices[ind] + after[0], after[1]);
            }
            else {
                cur[buy] = max(prices[ind] + after2[1], after[0]);
            }
        }
        after2 = after;
        after = cur;
    }

    return after[1];
}

// We can remove the inner loop because it will obviously run for buy = 1 & 0
int stockProfit(vector<int> &prices){
    int n = prices.size();
    vector<int> after2(2, 0), after(2, 0), cur(2, 0);

    for(int ind = n - 1; ind >= 0; ind--) {
        cur[1] = max(-prices[ind] + after[0], after[1]);
        
        cur[0] = max(prices[ind] + after2[1], after[0]);
        
        after2 = after;
        after = cur;
    }

    return after[1];
}