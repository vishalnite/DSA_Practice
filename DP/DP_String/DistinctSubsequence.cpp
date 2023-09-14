/*
Different pattern than LCS -- String Matching
Find the number of times the given subsequence is present in the string. 

Start matching the characters and if they are equal then there can be two cases
 - Both the indices move or only the string index move
If they do not match then only the string index move
Base cases --   Return 1 if subsequence exhausts
                Return 0 if string exhausts
*/

/********************* Recursion *********************/
int MOD = 1e9 + 7;

int finddistinct(int i, int j, string &str, string &sub) {
	if(j < 0)
		return 1;
	if(i < 0)
		return 0;

	if(str[i] == sub[j]) {
		return (finddistinct(i - 1, j - 1, str, sub) + finddistinct(i - 1, j, str, sub)) % MOD;
	}

	return finddistinct(i - 1, j, str, sub) % MOD;
}

int distinctSubsequences(string &str, string &sub)
{
	int n = str.size(), m = sub.size();
	return finddistinct(n - 1, m - 1, str, sub);
}



/********************* Memoization *********************/
int MOD = 1e9 + 7;

int finddistinct(int i, int j, string &str, string &sub, vector<vector<int>> &dp) {
	if(j < 0)
		return 1;
	if(i < 0)
		return 0;

	if(dp[i][j] != -1)
		return dp[i][j];

	if(str[i] == sub[j]) {
		return dp[i][j] = (finddistinct(i - 1, j - 1, str, sub, dp) 
		+ finddistinct(i - 1, j, str, sub, dp)) % MOD;
	}

	return dp[i][j] = finddistinct(i - 1, j, str, sub, dp) % MOD;
}

int distinctSubsequences(string &str, string &sub)
{
	int n = str.size(), m = sub.size();
	vector<vector<int>> dp(n, vector<int>(m, -1));
	return finddistinct(n - 1, m - 1, str, sub, dp);
}




/********************* Tabulation *********************/
// We cannot have negative index so we shift dp array by 1
// carefully write the base case
//The values can get very large so we may be required to use larger data types
int MOD = 1e9 + 7;

int distinctSubsequences(string &str, string &sub)
{
	int n = str.size(), m = sub.size();
	vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
	
	for(int i = 0; i <= n; i++)
		dp[i][0] = 1;

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(str[i - 1] == sub[j - 1]) {
				dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD;
			}
			else {
				dp[i][j] = dp[i - 1][j] % MOD;
			}
		}
	}

	return dp[n][m];
}




/********************* Space Optimization *********************/
// 1D array optimization -- just observe carefully by using the tabulation matrix
int MOD = 1e9 + 7;

int distinctSubsequences(string &str, string &sub)
{
	int n = str.size(), m = sub.size();
	vector<int> dp(m + 1, 0);
	
	dp[0] = 1;

	for(int i = 1; i <= n; i++) {
		for(int j = m; j >= 1; j--) {
			if(str[i - 1] == sub[j - 1]) {
				dp[j] = (dp[j - 1] + dp[j]) % MOD;
			}
		}
	}

	return dp[m];
}
