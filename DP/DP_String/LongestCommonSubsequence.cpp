/*
Find the length of the longest common subsequence of two strings.
[Method to write recurrence remains same but here we have two indices]
[If characters match we add 1 otherwise we explore both possibilities but reducing either one of them and take their max]
[In base case if we reach the end of string then return 0]
*/

/******************* Recursion ********************/
int lcsUtil(int ind1, int ind2, string s, string t) {
	if(ind1 < 0 || ind2 < 0)
		return 0;

	if(s[ind1] == t[ind2])
		return 1 + lcsUtil(ind1 - 1, ind2 - 1, s, t);

	return max(lcsUtil(ind1 - 1, ind2, s, t), lcsUtil(ind1, ind2 - 1, s, t));
}

int lcs(string s, string t)
{
	int n = s.size();
	int m = t.size();
	return lcsUtil(n - 1, m - 1, s, t);
}



/******************* Memoization ********************/
#include<vector>

int lcsUtil(int ind1, int ind2, string s, string t, vector<vector<int>> &dp) {
	if(ind1 < 0 || ind2 < 0)
		return 0;

	if(dp[ind1][ind2] != -1)
		return dp[ind1][ind2];

	if(s[ind1] == t[ind2])
		return dp[ind1][ind2] = 1 + lcsUtil(ind1 - 1, ind2 - 1, s, t, dp);

	return dp[ind1][ind2] = max(lcsUtil(ind1 - 1, ind2, s, t, dp), lcsUtil(ind1, ind2 - 1, s, t, dp));
}

int lcs(string s, string t)
{
	int n = s.size();
	int m = t.size();
	vector<vector<int>> dp(n, vector<int>(m, -1));
	return lcsUtil(n - 1, m - 1, s, t, dp);
}



/******************* Tabulation ********************/
#include<vector>

int lcs(string s, string t)
{
	int n = s.size();
	int m = t.size();
	vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
	
	//Base case -- Since there is -1, shift it to right -- Make 1st row and col as 0

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(s[i - 1] == t[j - 1])
				dp[i][j] = 1 + dp[i - 1][j - 1];
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	
	return dp[n][m];
}



/******************* Space Optimization ********************/
#include<vector>

int lcs(string s, string t)
{
	int n = s.size();
	int m = t.size();
	vector<int> prev(m + 1, 0), cur(m + 1, 0);
	
	//Base case -- Since there is -1, shift it to right -- Make 1st row and col as 0

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(s[i - 1] == t[j - 1])
				cur[j] = 1 + prev[j - 1];
			else
				cur[j] = max(prev[j], cur[j - 1]);
		}
		prev = cur;
	}
	
	return prev[m];
}