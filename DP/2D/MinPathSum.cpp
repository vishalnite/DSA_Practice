/*
Find the minimum path sum to reach from (0, 0) to (N - 1, M - 1).
[Similar to grid unique path but when you move out of grid then return a very large value(1e9 -- INT_MAX gives wrong answer)]
*/

/********************** Recursion ***************************/
#include <bits/stdc++.h> 

int getMinPathSum(int i, int j, vector<vector<int>> &grid) {
    if(i == 0 && j == 0) {
        return grid[i][j];
    }

    if(i < 0 || j < 0) {
        return 1e9;
    }

    int up = grid[i][j] + getMinPathSum(i - 1, j, grid);
    int left = grid[i][j] + getMinPathSum(i, j - 1, grid);

    return min(up, left);
}

int minSumPath(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    return getMinPathSum(n - 1, m - 1, grid);
}


/********************** Memoization ***************************/
#include <bits/stdc++.h> 

int getMinPathSum(int i, int j, vector<vector<int>> &grid, vector<vector<int>> &dp) {
    if(i == 0 && j == 0) {
        return grid[i][j];
    }

    if(i < 0 || j < 0) {
        return 1e9;
    }

    if(dp[i][j] != -1)
        return dp[i][j];

    int up = grid[i][j] + getMinPathSum(i - 1, j, grid, dp);
    int left = grid[i][j] + getMinPathSum(i, j - 1, grid, dp);

    return dp[i][j] = min(up, left);
}

int minSumPath(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<int>> dp(n, vector<int>(m, -1));

    return getMinPathSum(n - 1, m - 1, grid, dp);
}


/********************** Tabulation ***************************/
#include <bits/stdc++.h> 

int minSumPath(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<int>> dp(n, vector<int>(m, 0));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(i == 0 && j == 0) {
                dp[i][j] = grid[i][j];
            }
            else {
                int up = 1e9, left = 1e9;
                if(i > 0)
                    up = grid[i][j] + dp[i - 1][j];
                if(j > 0)
                    left = grid[i][j] + dp[i][j - 1];

                dp[i][j] = min(up, left);
            }
        }
    }

    return dp[n - 1][m - 1];
}


/********************** Space Optimization ***************************/
#include <bits/stdc++.h> 

int minSumPath(vector<vector<int>> &grid) {
    int n = grid.size();
    int m = grid[0].size();

    vector<int> prev(m, 0);

    for(int i = 0; i < n; i++) {
        vector<int> cur(m);
        for(int j = 0; j < m; j++) {
            if(i == 0 && j == 0) {
                cur[j] = grid[i][j];
            }
            else {
                int up = 1e9, left = 1e9;
                if(i > 0)
                    up = grid[i][j] + prev[j];
                if(j > 0)
                    left = grid[i][j] + cur[j - 1];

                cur[j] = min(up, left);
            }
        }
        prev = cur;
    }

    return prev[m - 1];
}