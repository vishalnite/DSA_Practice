/*
Find the number of LIS.
The number of LIS can be found by keeping the number in a count array.

If we find a subsequence greater than the previous then just copy the previous count to the current count.
Else if we find a subsequence with the same length as the previous then add the previous count to the current count.
Keep a track of length of the LIS

At the end sum all the count with the LIS.

[For better understanding dry run the code]
*/

int findNumberOfLIS(vector<int> &arr)
{
    int n = arr.size();
    vector<int> dp(n, 1), count(n, 1);
    int maxi = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++) {
            if(arr[j] < arr[i] && dp[i] < 1 + dp[j]) {
                dp[i] = 1 + dp[j];
                count[i] = count[j];
            }
            else if(arr[j] < arr[i] && dp[i] == 1 + dp[j]) {
                count[i] += count[j];
            }
        }
        maxi = max(maxi, dp[i]);
    }

    int ans = 0;
    for(int i = 0; i < n; i++) {
        if(dp[i] == maxi) {
            ans += count[i];
        }
    }

    return ans;
}