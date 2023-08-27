/*
Find the maximum value that can be achieved by putting items in the bag of maximum capacity. [0/1 Knapsack problem]
[Greedy won't work since the values are not uniform]
[Base case is when we are at index 0 so, we can either take the item if its capacity is less than equal to max capcity, or we do not take the item] 
*/

/********************* Recursion *********************/
#include <bits/stdc++.h> 

int maxValue(int ind, int weight, vector<int> &w, vector<int> &v) {
	if(ind == 0) {
		if(w[0] <= weight)
			return v[0];
		else	
			return 0;
	}

	int notTake = 0 + maxValue(ind - 1, weight, w, v);
	int take = INT_MIN;

	if(w[ind] <= weight) {
		take = v[ind] + maxValue(ind - 1, weight - w[ind], w, v);
	}

	return max(take, notTake);
}

int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	return maxValue(n - 1, maxWeight, weight, value);
}




/********************* Memoization *********************/
#include <bits/stdc++.h> 

int maxValue(int ind, int weight, vector<int> &w, vector<int> &v, vector<vector<int>> &dp) {
	if(ind == 0) {
		if(w[0] <= weight)
			return v[0];
		else	
			return 0;
	}

	if(dp[ind][weight] != -1)
		return dp[ind][weight];

	int notTake = 0 + maxValue(ind - 1, weight, w, v, dp);
	int take = INT_MIN;

	if(w[ind] <= weight) {
		take = v[ind] + maxValue(ind - 1, weight - w[ind], w, v, dp);
	}

	return dp[ind][weight] = max(take, notTake);
}

int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	vector<vector<int>> dp(n, vector<int>(maxWeight + 1, -1));
	return maxValue(n - 1, maxWeight, weight, value, dp);
}




/********************* Tabulation *********************/
#include <bits/stdc++.h> 

int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	vector<vector<int>> dp(n, vector<int>(maxWeight + 1, 0));
	
	for(int w = weight[0]; w <= maxWeight; w++) {
		dp[0][w] = value[0];
	}

	for(int ind = 1; ind < n; ind++) {
		for(int w = 0; w <= maxWeight; w++) {
			int notTake = 0 + dp[ind - 1][w];
			int take = INT_MIN;

			if(weight[ind] <= w) {
				take = value[ind] + dp[ind - 1][w - weight[ind]];
			}

			dp[ind][w] = max(take, notTake);
		}
	}

	return dp[n - 1][maxWeight];
}




/********************* Space Optimization *********************/
/* 
Single array space optimization is possible if we start filling rows from right to left. 
Because we can observe that we are using [w - wt[ind]].
*/
#include <bits/stdc++.h> 

int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	vector<int> prev(maxWeight + 1, 0);
	
	for(int w = weight[0]; w <= maxWeight; w++) {
		prev[w] = value[0];
	}

	for(int ind = 1; ind < n; ind++) {
		for(int w = maxWeight; w >= 0; w--) {
			int notTake = 0 + prev[w];
			int take = INT_MIN;

			if(weight[ind] <= w) {
				take = value[ind] + prev[w - weight[ind]];
			}

			prev[w] = max(take, notTake);
		}
	}

	return prev[maxWeight];
}