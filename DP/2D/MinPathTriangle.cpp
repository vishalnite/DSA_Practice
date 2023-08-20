/*
Given a triangle grid. Find the minimum cost required to reach from (0, 0) to the last row. At each element in a row i, we can move either
(i + 1, 0) or (i + 1, j + 1) -- down or diagonal.
[Same as minimum path sum -- but there is a variable end point]
[Start from (0, 0)]
[In tabulation, go from (n, n) -> (0, 0) -- opposite of recursion]
*/


/*************** Recursion ******************/
#include <bits/stdc++.h> 

int getMinTotal(int i, int j, vector<vector<int>> &triangle, int n) {
        if(i == n - 1) {
            return triangle[i][j];
        }

        int down = triangle[i][j] + getMinTotal(i + 1, j, triangle, n);
        int diagonal = triangle[i][j] + getMinTotal(i + 1, j + 1, triangle, n);

        return min(down, diagonal);
    }

int minimumPathSum(vector<vector<int>>& triangle, int n){
	return getMinTotal(0, 0, triangle, n);
}


/*************** Memoization ******************/
#include <bits/stdc++.h> 

int getMinTotal(int i, int j, vector<vector<int>> &triangle, int n, vector<vector<int>> &dp) {
    if(i == n - 1) {
        return triangle[i][j];
    }

    if(dp[i][j] != -1)
        return dp[i][j];

    int down = triangle[i][j] + getMinTotal(i + 1, j, triangle, n, dp);
    int diagonal = triangle[i][j] + getMinTotal(i + 1, j + 1, triangle, n, dp);

    return dp[i][j] = min(down, diagonal);
}

int minimumPathSum(vector<vector<int>>& triangle, int n){
	vector<vector<int>> dp(n, vector<int>(n, -1));
	return getMinTotal(0, 0, triangle, n, dp);
}


/*************** Tabulation ******************/
#include <bits/stdc++.h> 

int minimumPathSum(vector<vector<int>>& triangle, int n){
	vector<vector<int>> dp(n, vector<int>(n, 0));
	
    for(int i = 0; i < n; i++) {
        dp[n - 1][i] = triangle[n - 1][i];
    }

    for(int i = n - 2; i >= 0; i--) {
        for(int j = 0; j <= i; j++) {
            int down = triangle[i][j] + dp[i + 1][j];
            int diagonal = triangle[i][j] + dp[i + 1][j + 1];

            dp[i][j] = min(down, diagonal);
        }
    }

    return dp[0][0];
}


/*************** Space Optimization ******************/
#include <bits/stdc++.h> 

int minimumPathSum(vector<vector<int>>& triangle, int n){
	vector<int> front(n);
	
    for(int i = 0; i < n; i++) {
        front[i] = triangle[n - 1][i];
    }

    for(int i = n - 2; i >= 0; i--) {
        vector<int> cur;
        for(int j = 0; j <= i; j++) {
            int down = triangle[i][j] + front[j];
            int diagonal = triangle[i][j] + front[j + 1];

            cur.push_back(min(down, diagonal));
        }
        front = cur;
    }

    return front[0];
}