/*
Find the minimum insertions required to make the string pallindrome.
One thing we know for sure is if we reverse the string and append it at the end then it is a pallindrome. So, the maximum insertion required is
the length of the string.
How to approach -- Keep the longest pallindrome subsequence as it is and thus the insertions required is the leftover part of the string.
*/

/*************** Tabulation ***************/
class Solution {
public:
    int minInsertions(string s) {
        int n = s.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        int ans = 0;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(s[i - 1] == s[n - j]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                    ans = max(ans, dp[i][j]);
                }
                else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        return n - ans;
    }
};