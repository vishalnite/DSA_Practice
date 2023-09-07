/*
Find the length of the longest common substring. It is the continuation of longest common subsequence.
Here we need to take care that substrings are contiguous, so we should not perform max(f(i - 1, j), f(i, j - 1)) as this disrupt contiguous property.
So just put a zero if characters do not match.
*/

/************** Tabulation ****************/
int lcs(string &str1, string &str2){
    int n = str1.size();
    int m = str2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    int ans = 0;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
                ans = max(ans, dp[i][j]);
            } else
                dp[i][j] = 0;
        }
    }

    return ans;
}