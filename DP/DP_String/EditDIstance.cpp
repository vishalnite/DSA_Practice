/*
We can perform 3 operations on string1 -- insert, delete, replace.
Now find the minimum operations that can be performed on s1 to convert it into s2.

[We can always conver s1 to s2 in max (n + m) operations]

Sort of string matching type problem.
- When the characters match then just move the pointer in both the strings
- When they do not match, we can have 3 options
    - insert the charcter to match i.e, i, j - 1
    - delete the character to match it with the next i.e, i - 1, j
    - replace the character i.e, i - 1, j - 1
    - Take minimum of all these and add 1
*/

/************************* Recursion **************************/
class Solution {
private:
    int minDistanceUtil(int i, int j, string &word1, string &word2) {
        if(i < 0)
            return j + 1;
        if(j < 0)
            return i + 1;

        if(word1[i] == word2[j]) 
            return minDistanceUtil(i - 1, j - 1, word1, word2);

        return 1 + min(minDistanceUtil(i, j - 1, word1, word2),
                    min(minDistanceUtil(i - 1, j, word1, word2),
                        minDistanceUtil(i - 1, j - 1, word1, word2)
                    )
                );
    }
public:
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        return minDistanceUtil(n - 1, m - 1, word1, word2);
    }
};



/************************* Memoization **************************/
class Solution {
private:
    int minDistanceUtil(int i, int j, string &word1, string &word2, vector<vector<int>> &dp) {
        if(i < 0)
            return j + 1;
        if(j < 0)
            return i + 1;

        if(dp[i][j] != -1)
            return dp[i][j];

        if(word1[i] == word2[j]) 
            return dp[i][j] = minDistanceUtil(i - 1, j - 1, word1, word2, dp);

        return dp[i][j] = 1 + min(minDistanceUtil(i, j - 1, word1, word2, dp),
                    min(minDistanceUtil(i - 1, j, word1, word2, dp),
                        minDistanceUtil(i - 1, j - 1, word1, word2, dp)
                    )
                );
    }
public:
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return minDistanceUtil(n - 1, m - 1, word1, word2, dp);
    }
};



/************************* Tabulation **************************/
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        
        for(int j = 0; j <= m; j++)
            dp[0][j] = j;

        for(int i = 0; i <= n; i++)
            dp[i][0] = i;
        
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(word1[i - 1] == word2[j - 1]) 
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = 1 + min(dp[i - 1][j], 
                                    min(dp[i][j - 1], dp[i - 1][j - 1]));
            }
        }

        return dp[n][m];
    }
};



/************************* Space Optimization **************************/
// 1D array optimization is not possible as we are using both the arrays to compute the answer
class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        vector<int> prev(m + 1, 0), cur(m + 1, 0);
        
        for(int j = 0; j <= m; j++)
            prev[j] = j;
        
        for(int i = 1; i <= n; i++) {
            cur[0] = i;
            for(int j = 1; j <= m; j++) {
                if(word1[i - 1] == word2[j - 1]) 
                    cur[j] = prev[j - 1];
                else
                    cur[j] = 1 + min(prev[j], 
                                    min(cur[j - 1], prev[j - 1]));
            }
            prev = cur;
        }

        return prev[m];
    }
};