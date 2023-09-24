/*
Print LIS 
-- We use tabulation method with O(N) space complexity
*/

vector<int> printingLongestIncreasingSubsequence(vector<int> arr, int n) {
	vector<int> dp(n, 1), hash(n);
	int lastIndex = 0;
	int maxi = 0;

	for(int i = 0; i < n; i++) {
		hash[i] = i;
		for(int j = 0; j < i; j++) {
			if(arr[j] < arr[i] && 1 + dp[j] > dp[i]) {
				dp[i] = 1 + dp[j];
				hash[i] = j;
			}
		}
		if(dp[i] > maxi) {
			maxi = dp[i];
			lastIndex = i;
		}
	}

	vector<int> temp;
	temp.push_back(arr[lastIndex]);
	while(hash[lastIndex] != lastIndex) {
		lastIndex = hash[lastIndex];
		temp.push_back(arr[lastIndex]);
	}

	reverse(temp.begin(), temp.end());
	return temp;
}
