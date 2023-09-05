/*
Given a rod of length N units. The rod can be cut into different sizes and each size is associated with a price. Find the maximum cost that
can be achieved by cutting the rods.
[This problem may look different first time but if we carefully observe and consider index of price array similar to the weight array in knapsack
problem then it can be easily solved -- unbounded knapsack]
[Remember to keep evaluations in a variable as it may give wrong answer while running the code]
*/

/****************** Recursion ********************/
int maxCost(int ind, int N, vector<int> &price) {
	if(ind == 0) {
		return N * price[0];
	}

	int notTake = 0 + maxCost(ind - 1, N, price);
	int take = 0;
	int rodLength = ind + 1;
	if(rodLength <= N) {
		take = price[ind] + maxCost(ind, N - rodLength, price);
	}

	return max(take, notTake);
}

int cutRod(vector<int> &price, int n)
{
	return maxCost(n - 1, n, price);
}





/****************** Memoization ********************/
int maxCost(int ind, int N, vector<int> &price, vector<vector<int>> &dp) {
	if(ind == 0) {
		return N * price[0];
	}

	if(dp[ind][N] != -1)
		return dp[ind][N];

	int notTake = 0 + maxCost(ind - 1, N, price, dp);
	int take = 0;
	int rodLength = ind + 1;
	if(rodLength <= N) {
		take = price[ind] + maxCost(ind, N - rodLength, price, dp);
	}

	return dp[ind][N] = max(take, notTake);
}

int cutRod(vector<int> &price, int n)
{
	vector<vector<int>> dp(n, vector<int>(n + 1, -1));
	return maxCost(n - 1, n, price, dp);
}





/****************** Tabulation ********************/
int cutRod(vector<int> &price, int n)
{
	vector<vector<int>> dp(n, vector<int>(n + 1, 0));

	for(int N = 1; N <= n; N++) {
		dp[0][N] = N * price[0];
	}

	for(int ind = 1; ind < n; ind++) {
		for(int N = 0; N <= n; N++) {
			int notTake = 0 + dp[ind - 1][N];
			int take = 0;
			int rodLength = ind + 1;
			if(rodLength <= N) {
				take = price[ind] + dp[ind][N - rodLength];
			}

			dp[ind][N] = max(take, notTake);
		}
	}

	return dp[n - 1][n];
}





/****************** Space Optimization ********************/
// single array optimization
int cutRod(vector<int> &price, int n)
{
	vector<int> prev(n + 1, 0);

	for(int N = 1; N <= n; N++) {
		prev[N] = N * price[0];
	}

	for(int ind = 1; ind < n; ind++) {
		for(int N = 0; N <= n; N++) {
			int notTake = 0 + prev[N];
			int take = 0;
			int rodLength = ind + 1;
			if(rodLength <= N) {
				take = price[ind] + prev[N - rodLength];
			}

			prev[N] = max(take, notTake);
		}
	}

	return prev[n];
}
