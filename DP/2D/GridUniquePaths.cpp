/*
Find all the unique paths from (0, 0) to (m - 1, n - 1) in a grid if the possible moves are right and down only.
[Count all ways -- Resursion -- We can move from (m - 1, n - 1) to (0, 0) -- depends upon preference]
*/

/********************* Recursion ***********************/
#include <bits/stdc++.h> 

int countPaths(int i, int j) {
	if(i == 0 && j == 0)
		return 1;
	if(i < 0 || j < 0)
		return 0;

	int up = countPaths(i - 1, j);
	int left = countPaths(i, j - 1);

	return up + left;
}

int uniquePaths(int m, int n) {
	return countPaths(m - 1, n - 1);
}


/********************* Memoization ***********************/
#include <bits/stdc++.h> 

int countPaths(int i, int j, vector<vector<int>> &dp) {
	if(i == 0 && j == 0)
		return dp[i][j] = 1;
	if(i < 0 || j < 0)
		return 0;

	if(dp[i][j] != -1)
		return dp[i][j];

	int up = countPaths(i - 1, j, dp);
	int left = countPaths(i, j - 1, dp);

	return dp[i][j] = up + left;
}

int uniquePaths(int m, int n) {
	vector<vector<int>> dp(m, vector<int>(n, -1));
	countPaths(m - 1, n - 1, dp);

	return dp[m - 1][n - 1];
}


/********************* Tabulation ***********************/
#include <bits/stdc++.h> 

int uniquePaths(int m, int n) {
	vector<vector<int>> dp(m, vector<int>(n, 0));
	
	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			if(i == 0 && j == 0) {
				dp[i][j] = 1;
				continue;
			}

            int up = 0, left = 0;
			if(i > 0)
				up = dp[i - 1][j];
			if(j > 0)
				left = dp[i][j - 1];

			dp[i][j] = up + left;
		}
	}

	return dp[m - 1][n - 1];
}


/********************* Space Optimization ***********************/
//Just need to keep track of previous row and at each step prev row and prev element in the same row is required
#include <bits/stdc++.h> 

int uniquePaths(int m, int n) {
	vector<int> dp(n, 0);
	
	for(int i = 0; i < m; i++) {
		vector<int> temp(n);
		for(int j = 0; j < n; j++) {
			if(i == 0 && j == 0) {
				temp[j] = 1;
				continue;
			}

			temp[j] = dp[j];
            if(j > 0) {
				temp[j] += temp[j - 1];
			}
		}
		dp = temp;
	}

	return dp[n - 1];
}