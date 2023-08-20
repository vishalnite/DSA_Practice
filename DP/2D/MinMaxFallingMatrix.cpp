/*
Find the maximum path sum that can be obtained from the first row to the last row in a matrix. 
[Variable starting and variable ending point]
[Explore all starting or ending points] 
*/

/****************** Recursion *********************/
#include <bits/stdc++.h> 

int f(int i, int j, vector<vector<int>> &matrix, int n, int m) {
    if(j < 0 || j >= m) {
        return -1e9;
    }
    
    if(i == 0) {
        return matrix[i][j];
    }

    int ul = matrix[i][j] + f(i - 1, j - 1, matrix, n, m);
    int u = matrix[i][j] + f(i - 1, j, matrix, n, m);
    int ur = matrix[i][j] + f(i - 1, j + 1, matrix, n, m);

    return max(ul, max(u, ur));
}

int getMaxPathSum(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    int m = matrix[0].size();
    int maxPathSum = INT_MIN;

    for(int j = 0; j < m; j++) {
        int curMax = f(n - 1, j, matrix, n, m);
        maxPathSum = max(maxPathSum, curMax);
    }

    return maxPathSum;
}


/****************** Memoization *********************/
#include <bits/stdc++.h> 

int f(int i, int j, vector<vector<int>> &matrix, int n, int m, vector<vector<int>> &dp) {
    if(j < 0 || j >= m) {
        return -1e9;
    }
    
    if(i == 0) {
        return matrix[i][j];
    }

    if(dp[i][j] != -1)
        return dp[i][j];

    int ul = matrix[i][j] + f(i - 1, j - 1, matrix, n, m, dp);
    int u = matrix[i][j] + f(i - 1, j, matrix, n, m, dp);
    int ur = matrix[i][j] + f(i - 1, j + 1, matrix, n, m, dp);

    return dp[i][j] = max(ul, max(u, ur));
}

int getMaxPathSum(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    int m = matrix[0].size();
    int maxPathSum = INT_MIN;

    vector<vector<int>> dp(n, vector<int>(m, -1));

    for(int j = 0; j < m; j++) {
        int curMax = f(n - 1, j, matrix, n, m, dp);
        maxPathSum = max(maxPathSum, curMax);
    }

    return maxPathSum;
}


/****************** Tabulation *********************/
#include <bits/stdc++.h> 

int getMaxPathSum(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    int m = matrix[0].size();
    int maxPathSum = INT_MIN;

    vector<vector<int>> dp(n, vector<int>(m));

    for(int j = 0; j < m; j++) {
        dp[0][j] = matrix[0][j];
    }

    for(int i = 1; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int u = -1e9, ul = -1e9, ur = -1e9;
            if(j > 0)
                ul = matrix[i][j] + dp[i - 1][j - 1];
            if(j < m - 1) 
                ur = matrix[i][j] + dp[i - 1][j + 1];

            u = matrix[i][j] + dp[i - 1][j];
            dp[i][j] = max(u, max(ul, ur));
        }
    }

    for(int j = 0; j < m; j++) {
        maxPathSum = max(dp[n - 1][j], maxPathSum);
    }

    return maxPathSum;
}


/****************** Space Optimization *********************/
#include <bits/stdc++.h> 

int getMaxPathSum(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    int m = matrix[0].size();
    int maxPathSum = INT_MIN;

    vector<int> prev(m);

    for(int j = 0; j < m; j++) {
        prev[j] = matrix[0][j];
    }

    for(int i = 1; i < n; i++) {
        vector<int> cur(m);
        for(int j = 0; j < m; j++) {
            int u = -1e9, ul = -1e9, ur = -1e9;
            if(j > 0)
                ul = matrix[i][j] + prev[j - 1];
            if(j < m - 1) 
                ur = matrix[i][j] + prev[j + 1];

            u = matrix[i][j] + prev[j];
            cur[j] = max(u, max(ul, ur));
        }
        prev = cur;
    }

    for(int j = 0; j < m; j++) {
        maxPathSum = max(prev[j], maxPathSum);
    }

    return maxPathSum;
}