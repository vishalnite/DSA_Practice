/*
Find the length of the longest pallindromic subsequence.
[Brute Force -- Generate all subsequence and find the largest pallindrome]
[Optimal -- use DP -- If we observe carefully we can solve it using LCS -- just an extension of LCS]
[Find the LCS of the string from the front and the back]
*/

/************** Tabulation ***************/
#include <bits/stdc++.h> 
int longestPalindromeSubsequence(string s)
{
    int n = s.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(s[i - 1] == s[n - j])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    return dp[n][n];
}