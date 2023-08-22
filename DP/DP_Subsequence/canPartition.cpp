/*
Given an array, determine whether the array can be partitioned into two subsets with equal sum.
[Find the sum of all elements -- If it is odd then it is not possible]
[If it is even try to find the subset with target as sum / 2]
*/

/********************* Recursion **********************/
bool canPartitionUtil(int ind, int target, vector<int> &arr) {
	if(target == 0)
		return true;
	
	if(ind == 0)
		return (arr[0] == target);

	bool notTake = canPartitionUtil(ind - 1, target, arr);
	bool take = false;
	if(arr[ind] <= target) {
		take = canPartitionUtil(ind - 1, target - arr[ind], arr);
	}

	return take | notTake;
}

bool canPartition(vector<int> &arr, int n)
{
	int sum = 0;
	for(int i : arr) {
		sum += i;
	}

	if(sum % 2 != 0)
		return false;

	int target = sum / 2;

	return canPartitionUtil(n - 1, target, arr);
}




/********************* Memoization **********************/
bool canPartitionUtil(int ind, int target, vector<int> &arr, vector<vector<int>> &dp) {
	if(target == 0)
		return true;
	
	if(ind == 0)
		return (arr[0] == target);

	if(dp[ind][target] != -1)
		return dp[ind][target];

	bool notTake = canPartitionUtil(ind - 1, target, arr, dp);
	bool take = false;
	if(arr[ind] <= target) {
		take = canPartitionUtil(ind - 1, target - arr[ind], arr, dp);
	}

	return dp[ind][target] = take | notTake;
}

bool canPartition(vector<int> &arr, int n)
{
	int sum = 0;
	for(int i : arr) {
		sum += i;
	}

	if(sum % 2 != 0)
		return false;

	int target = sum / 2;
	vector<vector<int>> dp(n, vector<int>(target + 1, -1));

	return canPartitionUtil(n - 1, target, arr, dp);
}




/********************* Tabulation **********************/
bool canPartition(vector<int> &arr, int n)
{
	int sum = 0;
	for(int i : arr) {
		sum += i;
	}

	if(sum % 2 != 0)
		return false;

	int target = sum / 2;
	vector<vector<bool>> dp(n, vector<bool>(target + 1, 0));

	for(int i = 0; i < n; i++) {
		dp[i][0] = true;
	}
	dp[0][arr[0]] = true;

	for(int i = 1; i < n; i++) {
		for(int k = 1; k <= target; k++) {
			bool notTake = dp[i - 1][k];
			bool take = false;
			if(arr[i] <= k) {
				take = dp[i - 1][k - arr[i]];
			}

			dp[i][k] = take | notTake;
		}
	} 

	return dp[n - 1][target];
}




/********************* Space Optimization **********************/
bool canPartition(vector<int> &arr, int n)
{
	int sum = 0;
	for(int i : arr) {
		sum += i;
	}

	if(sum % 2 != 0)
		return false;

	int target = sum / 2;
	vector<bool> prev(target + 1, 0), cur(target + 1, 0);

	prev[0] = cur[0] = true;
	prev[arr[0]] = true;

	for(int i = 1; i < n; i++) {
		for(int k = 1; k <= target; k++) {
			bool notTake = prev[k];
			bool take = false;
			if(arr[i] <= k) {
				take = prev[k - arr[i]];
			}

			cur[k] = take | notTake;
		}
		prev = cur;
	} 

	return prev[target];
}
