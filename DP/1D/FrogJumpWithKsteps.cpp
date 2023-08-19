/*
Follow up to Frog Jump problem. Instead of two steps there are k steps.
We cannot space optimize it because in the worst case k = n. We can carry a list of size k to space optimize it but it is not required.
*/

/************************ Recursive Solution **************************/
int func(int n, int k, vector<int> &heights) {
    if(n == 0)
        return 0;

    int minCost = INT_MAX;
    for(int i = 1; i <= k; i++) {
        if(n - i >= 0) {
            int cost = func(n - i, k, heights) + abs(heights[n] - heights[n - i]);
            minCost = min(minCost, cost);
        }
    }

    return minCost;
}

int minimizeCost(int n, int k, vector<int> &height){ 
    return func(n - 1, k, height);
}


/************************ Memoization **************************/
int func(int n, int k, vector<int> &heights, vector<int> &dp) {
    if(n == 0)
        return 0;

    if(dp[n] != -1)
        return dp[n];

    int minCost = INT_MAX;
    for(int i = 1; i <= k; i++) {
        if(n - i >= 0) {
            int cost = func(n - i, k, heights, dp) + abs(heights[n] - heights[n - i]);
            minCost = min(minCost, cost);
        }
    }

    return dp[n] = minCost;
}

int minimizeCost(int n, int k, vector<int> &height){
    vector<int> dp(n, -1);
    dp[0] = 0;
    
    func(n - 1, k, height, dp);
    return dp[n - 1];
}


/************************ Tabulation **************************/
int minimizeCost(int n, int k, vector<int> &height){
    vector<int> dp(n, 0);
    
    for(int i = 1; i < n; i++) {
        int minCost = INT_MAX;
        for(int j = 1; j <= k; j++) {
            if(i - j >= 0) {
                int cost = dp[i - j] + abs(height[i] - height[i - j]);
                minCost = min(minCost, cost);
            }
        }
        dp[i] = minCost;
    }
    
    return dp[n - 1];
}

