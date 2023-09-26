/*
Find the length of the longest bitonic sequence. 
Bitonic sequence is [first strictly increasing and then strictly decreasing, strictly increasing, strictly decreasing]

A simple observation will be to look the array first from the start and then from the end.
We find LIS from the start and from the end. Bitonic sequence is technically a combination of both.
Add both LIS and LDS and subtract 1 from it as 1 element is common.
*/

int longestBitonicSubsequence(vector<int>& arr, int n)
{
	vector<int> dp1(n, 1);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < i; j++) {
			if(arr[j] < arr[i] && dp1[i] < 1 + dp1[j]) {
				dp1[i] = 1 + dp1[j];
			}
		}
	}

	vector<int> dp2(n, 1);
	for(int i = n - 1; i >= 0; i--) {
		for(int j = n - 1; j > i; j--) {
			if(arr[j] < arr[i] && dp2[i] < 1 + dp2[j]) {
				dp2[i] = 1 + dp2[j];
			}
		}
	}

	int maxi = 0;
	for(int i = 0; i < n; i++) {
		maxi = max(maxi, dp1[i] + dp2[i] - 1);
	}

	return maxi;
}
