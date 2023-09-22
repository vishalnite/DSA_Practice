/*
Similar to stock II problem but here after every transaction there is a fee involved.
*/

/**************** Recursion *****************/
int f(int ind, int buy, vector<int> &prices, int n, int fee) {
	if(ind == n)
		return 0;

	if(buy) {
		return max(-prices[ind] + f(ind + 1, 0, prices, n, fee),
									f(ind + 1, 1, prices, n, fee));
	}
	else {
		return max(prices[ind] - fee + f(ind + 1, 1, prices, n, fee),
										f(ind + 1, 0, prices, n, fee));
	}
}

int maximumProfit(vector<int> &prices, int n, int fee)
{
	return f(0, 1, prices, n, fee);
}




/**************** Memoization *****************/
int f(int ind, int buy, vector<int> &prices, int n, int fee, vector<vector<int>> &dp) {
	if(ind == n)
		return 0;

	if(dp[ind][buy] != -1)
		return dp[ind][buy];

	if(buy) {
		return dp[ind][buy] = max(-prices[ind] + f(ind + 1, 0, prices, n, fee, dp),
									f(ind + 1, 1, prices, n, fee, dp));
	}
	else {
		return dp[ind][buy] = max(prices[ind] - fee + f(ind + 1, 1, prices, n, fee, dp),
										f(ind + 1, 0, prices, n, fee, dp));
	}
}

int maximumProfit(vector<int> &prices, int n, int fee)
{
	vector<vector<int>> dp(n, vector<int>(2, -1));
	return f(0, 1, prices, n, fee, dp);
}




/**************** Tabulation *****************/
int maximumProfit(vector<int> &prices, int n, int fee)
{
	vector<vector<int>> dp(n + 1, vector<int>(2, 0));
	
	for(int ind = n - 1; ind >= 0; ind--) {
		dp[ind][1] = max(-prices[ind] + dp[ind + 1][0], dp[ind + 1][1]);

		dp[ind][0] = max(prices[ind] - fee + dp[ind + 1][1], dp[ind + 1][0]);
	}
	
	return dp[0][1];
}




/**************** Space Optimization *****************/
int maximumProfit(vector<int> &prices, int n, int fee)
{
	vector<int> after(2, 0), cur(2, 0);
	
	for(int ind = n - 1; ind >= 0; ind--) {
		cur[1] = max(-prices[ind] + after[0], after[1]);

		cur[0] = max(prices[ind] - fee + after[1], after[0]);

		after = cur;
	}
	
	return after[1];
}
