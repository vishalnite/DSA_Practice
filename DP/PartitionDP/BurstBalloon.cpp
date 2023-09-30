/*
Very interesting problem -- In partition DP we go from the complete block to the individual block making independent sub problems. But here we 
cannot do that beacuse the subproblems made after partition will depend on each other.

Now, how to solve this???
Think of solving this problem from the backward direction i.e, we got from the last balloon to the first. In that case we will be able to treat each 
subproblem as independent.

- Add 1 to the start and end of the array
- Find the max from all possible partitions
- Number of coins is found out by a[i - 1] * a[ind] * a[j + 1]
*/

/****************** Recursion ****************/
int f(int i, int j, vector<int> &arr) {
    if(i > j)
        return 0;

    int maxi = INT_MIN;
    for(int ind = i; ind <= j; ind++) {
        int coins = arr[i - 1] * arr[ind] * arr[j + 1] 
                    + f(i, ind - 1, arr) 
                    + f(ind + 1, j, arr);
        maxi = max(maxi, coins);
    }

    return maxi;
}

int burstBalloons(vector<int> &arr){
    int n = arr.size();
    arr.push_back(1);
    arr.insert(arr.begin(), 1);
    return f(1, n, arr);
}



/****************** Memoization ****************/
int f(int i, int j, vector<int> &arr, vector<vector<int>> & dp) {
    if(i > j)
        return 0;

    if(dp[i][j] != -1)
        return dp[i][j];

    int maxi = INT_MIN;
    for(int ind = i; ind <= j; ind++) {
        int coins = arr[i - 1] * arr[ind] * arr[j + 1] 
                    + f(i, ind - 1, arr, dp) 
                    + f(ind + 1, j, arr, dp);
        maxi = max(maxi, coins);
    }

    return dp[i][j] = maxi;
}

int burstBalloons(vector<int> &arr){
    int n = arr.size();
    arr.push_back(1);
    arr.insert(arr.begin(), 1);
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));

    return f(1, n, arr, dp);
}



/****************** Tabulation ****************/
// Starting j from i to avoid covering the case when (i > j)
int burstBalloons(vector<int> &arr){
    int n = arr.size();
    arr.push_back(1);
    arr.insert(arr.begin(), 1);
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

    for(int i = n; i >= 1; i--) {
        for(int j = i; j <= n; j++) {
            int maxi = INT_MIN;
            for(int ind = i; ind <= j; ind++) {
                int coins = arr[i - 1] * arr[ind] * arr[j + 1] + dp[i][ind - 1] + dp[ind + 1][j];
                maxi = max(maxi, coins);
            }

            dp[i][j] = maxi;
        }
    }

    return dp[1][n];
}