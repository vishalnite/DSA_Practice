/*
Find all the unique paths from (0, 0) to (m - 1, n - 1) in a grid if the possible moves are right and down only. The grid contains obstacles 
represented by -1. Answer can be large so do modulus of 1e9 + 7.
[Count all ways -- Resursion -- We can move from (m - 1, n - 1) to (0, 0) -- depends upon preference]
*/

/********************* Recursion ***********************/
int MOD = 1e9 + 7;

int countPaths(int i, int j, vector<vector<int>> &mat) {
    if(i == 0 && j == 0)
        return 1;
    if(i < 0 || j < 0 || mat[i][j] == -1)
        return 0;

    int up = countPaths(i - 1, j, mat) % MOD;
    int left = countPaths(i, j - 1, mat) % MOD;

    return  (up + left) % MOD;
}

int mazeObstacles(int n, int m, vector<vector<int>> &mat) {
    return countPaths(n - 1, m - 1, mat);
}


/********************* Memoization ***********************/
int MOD = 1e9 + 7;

int countPaths(int i, int j, vector<vector<int>> &mat, vector<vector<int>> &dp) {
    if(i == 0 && j == 0)
        return 1;
    if(i < 0 || j < 0 || mat[i][j] == -1)
        return 0;

    if(dp[i][j] != -1)
        return dp[i][j];

    int up = countPaths(i - 1, j, mat, dp) % MOD;
    int left = countPaths(i, j - 1, mat, dp) % MOD;

    return  dp[i][j] = (up + left) % MOD;
}

int mazeObstacles(int n, int m, vector<vector<int>> &mat) {
    vector<vector<int>> dp(n, vector<int>(m, -1));
    countPaths(n - 1, m - 1, mat, dp);

    return dp[n - 1][m - 1];
}


/********************* Tabulation ***********************/
int MOD = 1e9 + 7;

int mazeObstacles(int n, int m, vector<vector<int>> &mat) {
    vector<vector<int>> dp(n, vector<int>(m, 0));
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = 1;
                continue;
            }
            if(mat[i][j] == -1) {
                dp[i][j] = 0;
                continue;
            }

            int up = 0, left = 0;
            if(i > 0)
                up = dp[i - 1][j];
            if(j > 0)
                left = dp[i][j - 1];

            dp[i][j] = (up + left) % MOD;
        }
    }

    return dp[n - 1][m - 1];
}


/********************* Space Optimization ***********************/
//Just need to keep track of previous row and at each step prev row and prev element in the same row is required
int MOD = 1e9 + 7;

int mazeObstacles(int n, int m, vector<vector<int>> &mat) {
    vector<int> prev(m, 0);
    
    for(int i = 0; i < n; i++) {
        vector<int> temp(m);
        for(int j = 0; j < m; j++) {
            if (i == 0 && j == 0) {
                temp[j] = 1;
                continue;
            }
            if(mat[i][j] == -1) {
                temp[j] = 0;
                continue;
            }

            int left = 0;
            int up = prev[j];
            if(j > 0)
                left = temp[j - 1];

            temp[j] = (up + left) % MOD;
        }
        prev = temp;
    }

    return prev[m - 1];
}