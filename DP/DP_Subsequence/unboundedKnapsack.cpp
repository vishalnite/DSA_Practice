/*
0/1 knapsack problem but we can pick an item any number of times
*/

/********************* Recursion **********************/
int maxProfit(int ind, int w, vector<int> &profit, vector<int> &weight) {
    if(ind == 0) {
        return ((int)(w / weight[0])) * profit[0];
    }

    int notTake = 0 + maxProfit(ind - 1, w, profit, weight);
    int take = 0;
    if(weight[ind] <= w) {
        take = profit[ind] + maxProfit(ind, w - weight[ind], profit, weight);
    }

    return max(take, notTake);
}

int unboundedKnapsack(int n, int w, vector<int> &profit, vector<int> &weight){
    return maxProfit(n - 1, w, profit, weight);    
}



/********************* Memoization **********************/
int maxProfit(int ind, int w, vector<int> &profit, vector<int> &weight, vector<vector<int>> &dp) {
    if(ind == 0) {
        return ((int)(w / weight[0])) * profit[0];
    }

    if(dp[ind][w] != -1)
        return dp[ind][w];

    int notTake = 0 + maxProfit(ind - 1, w, profit, weight, dp);
    int take = 0;
    if(weight[ind] <= w) {
        take = profit[ind] + maxProfit(ind, w - weight[ind], profit, weight, dp);
    }

    return dp[ind][w] = max(take, notTake);
}

int unboundedKnapsack(int n, int w, vector<int> &profit, vector<int> &weight){
    vector<vector<int>> dp(n, vector<int>(w + 1, -1));
    return maxProfit(n - 1, w, profit, weight, dp);    
}



/********************* Tabulation **********************/
int unboundedKnapsack(int n, int w, vector<int> &profit, vector<int> &weight){
    vector<vector<int>> dp(n, vector<int>(w + 1, 0));

    for(int W = 0; W <= w; W++) {
        dp[0][W] = ((int)(W / weight[0])) * profit[0];
    }

    for(int ind = 1; ind < n; ind++) {
        for(int W = 0; W <= w; W++) {
            int notTake = 0 + dp[ind - 1][W];
            int take = 0;
            if(weight[ind] <= W) {
                take = profit[ind] + dp[ind][W - weight[ind]];
            }

            dp[ind][W] = max(take, notTake);
        }
    }

    return dp[n - 1][w];    
}



/********************* Space Optimization **********************/
// Single array optimization is possible
int unboundedKnapsack(int n, int w, vector<int> &profit, vector<int> &weight){
    vector<int> prev(w + 1, 0);

    for(int W = 0; W <= w; W++) {
        prev[W] = ((int)(W / weight[0])) * profit[0];
    }

    for(int ind = 1; ind < n; ind++) {
        for(int W = 0; W <= w; W++) {
            int notTake = 0 + prev[W];
            int take = 0;
            if(weight[ind] <= W) {
                take = profit[ind] + prev[W - weight[ind]];
            }

            prev[W] = max(take, notTake);
        }
    }

    return prev[w];    
}
