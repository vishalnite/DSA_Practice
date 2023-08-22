/*
Find the minimum absolute difference between the partitions of the subarray.
Use subset sum equal to k method to compute what are the targets possible(target here is the total sum)
After finding the total sum check which target are possile, compute s1 and s2 and find the minimum absolute difference 
*/

//Optimization -- take target upto sum / 2 only
//Can also be space optimized
/******************* Tabulation **********************/
int minSubsetSumDifference(vector<int>& arr, int n)
{
	int sum = 0;
	for(int i : arr) {
		sum += i;
	}

	int k = sum / 2;
	vector<vector<bool>> dp(n, vector<bool>(k + 1, 0));

	for(int i = 0; i < n; i++) {
		dp[i][0] = true;
	}
	if(arr[0] <= k)
		dp[0][arr[0]] = true;

	for(int i = 1; i < n; i++) {
		for(int target = 1; target <= k; target++) {
			bool notTake = dp[i - 1][target];
			bool take = false;
			if(arr[i] <= target)
				take = dp[i - 1][target - arr[i]];

			dp[i][target] = take | notTake;
		}
	}

	int mini = 1e9;
	for(int i = 0; i <= k; i++) {
		if(dp[n - 1][i] == true) {
			int s1 = i;
			int s2 = sum - i;
			mini = min(mini, abs(s2 - s1));
		}
	}

	return mini;
}
