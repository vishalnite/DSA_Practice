/*
Find the shortest common supersequence which contains both the strings as subsequence.
First find the LCS of both the strings, it will give us the minimum length of the supersequence.
Then use printing the LCS method to determine one of the shortest supersequences from the tabulation.
*/

/******************** Using Tabulation **********************/
#include <bits/stdc++.h> 
string shortestSupersequence(string a, string b)
{
	//LCS
	int n = a.size(), m = b.size();
	vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if(a[i - 1] == b[j - 1]) {
				dp[i][j] = 1 + dp[i - 1][j - 1];
			}
			else {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}


	//Printing LCS
	string ans = "";
	int i = n, j = m;

	while(i > 0 && j > 0) {
		if(a[i - 1] == b[j - 1]) {
			ans.push_back(a[i - 1]);
			i--;
			j--;
		}
		else if(dp[i - 1][j] > dp[i][j - 1]) {
			ans.push_back(a[i - 1]);
			i--;
		}
		else {
			ans.push_back(b[j - 1]);
			j--;
		}
	}

	//Remaining characters
	while(i > 0) {
		ans.push_back(a[i - 1]);
		i--;
	}

	while(j > 0) {
		ans.push_back(b[j - 1]);
		j--;
	}

	reverse(ans.begin(), ans.end());
	return ans;
}