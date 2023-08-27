/*
Count the number of subsets with sum K. 
[General rule, whenever there is a count problem from base case return 1 or 0 and add the pick and not pick cases]
[Similar to find subset with sum K problem]

We have done it for constraints [1 <= arr[i] < n].
But if we give {0, 0, 1} with k = 1 then it will return 1 instead of 4

Possible Solutions:
- Count number of zeroes and calculate pow(2, cnt) and multiply with the original answer
- OR change the base case to try to go deep into recursion
    if(ind == 0) {
        if(sum == 0 && arr[0] == 0) return 2;
        if(sum == 0 || sum == num[0]) return 1;
        return 0;
    }
    
For Tabulation -
    if(arr[0] == 0) dp[0][0] = 2;
    else dp[0][0] = 1;

    if(arr[0] != 0 && arr[0] <= k) {
        dp[0][arr[0]] = 1;
    }
*/

/**************** Recursion *******************/
int MOD = 1e9 + 7;

int countWays(int ind, int sum, vector<int> &arr) {
	if(sum == 0)
		return 1;
	if(ind == 0)
		return (arr[ind] == sum);

	int notTake = countWays(ind - 1, sum, arr);
	int take = 0;
	if(arr[ind] <= sum)
		take = countWays(ind - 1, sum - arr[ind], arr);

	return (notTake + take) % MOD;
}

int findWays(vector<int>& arr, int k)
{
	int n = arr.size();
	return countWays(n - 1, k, arr);
}



/**************** Memoization *******************/
int MOD = 1e9 + 7;

int countWays(int ind, int sum, vector<int> &arr, vector<vector<int>> &dp) {
	if(sum == 0)
		return 1;
	if(ind == 0)
		return (arr[ind] == sum);

	if(dp[ind][sum] != -1)
		return dp[ind][sum];

	int notTake = countWays(ind - 1, sum, arr, dp);
	int take = 0;
	if(arr[ind] <= sum)
		take = countWays(ind - 1, sum - arr[ind], arr, dp);

	return dp[ind][sum] = (notTake + take) % MOD;
}

int findWays(vector<int>& arr, int k)
{
	int n = arr.size();
	vector<vector<int>> dp(n, vector<int>(k + 1, -1));
	return countWays(n - 1, k, arr, dp);
}





/**************** Tabulation *******************/
int MOD = 1e9 + 7;

int findWays(vector<int>& arr, int k)
{
	int n = arr.size();
	vector<vector<int>> dp(n, vector<int>(k + 1, 0));
	
	for(int i = 0; i < n; i++) {
		dp[i][0] = 1;
	}

	if(arr[0] <= k) {
		dp[0][arr[0]] = 1;
	}

	for(int ind = 1; ind < n; ind++) {
		for(int sum = 1; sum <= k; sum++) {
			int notTake = dp[ind - 1][sum];
			int take = 0;
			if(arr[ind] <= sum) {
				take = dp[ind - 1][sum - arr[ind]];
			}

			dp[ind][sum] = (notTake + take) % MOD;
		}
	}

	return dp[n - 1][k];
}





/**************** Space Optimization *******************/
int MOD = 1e9 + 7;

int findWays(vector<int>& arr, int k)
{
	int n = arr.size();
	vector<int> prev(k + 1, 0), cur(k + 1, 0);
	
	prev[0] = cur[0] = 1;

	if(arr[0] <= k) {
		prev[arr[0]] = 1;
	}

	for(int ind = 1; ind < n; ind++) {
		for(int sum = 1; sum <= k; sum++) {
			int notTake = prev[sum];
			int take = 0;
			if(arr[ind] <= sum) {
				take = prev[sum - arr[ind]];
			}

			cur[sum] = (notTake + take) % MOD;
		}
		prev = cur;
	}

	return prev[k];
}




