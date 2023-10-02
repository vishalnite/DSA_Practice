/*
Find the minimum partitions required such that each substring after partitioning is a palindrome.

- This is another kind of partition DP problem (not MCM)
- We use front partitioning
- While traversing the string we will check whether the first partition is a palindrome or not.
- If it is then add 1 to answer and check for the remaining string.
- Base case is when i reaches n then we need to return 0 as there cannot be made a partition.
*/

/******************** Recursion *********************/
bool isPalindrome(int i, int j, string &str) {
    while(i < j) {
        if(str[i] != str[j])
            return false;
        i++;
        j--;
    }
    return true;
}

int f(int i, int n, string &str) {
    if(i == n)
        return 0;

    int minCost =INT_MAX;
    for(int j = i; j < n; j++) {
        if(isPalindrome(i, j, str)) {
            int cost = 1 + f(j + 1, n, str);
            minCost = min(minCost, cost);
        }
    }

    return minCost;
}

int palindromePartitioning(string str)
{
    int n = str.size();
    return f(0, n, str) - 1;
}





/******************** Memoization *********************/
bool isPalindrome(int i, int j, string &str) {
    while(i < j) {
        if(str[i] != str[j])
            return false;
        i++;
        j--;
    }
    return true;
}

int f(int i, int n, string &str, vector<int> &dp) {
    if(i == n)
        return 0;

    if(dp[i] != -1)
        return dp[i];

    int minCost =INT_MAX;
    for(int j = i; j < n; j++) {
        if(isPalindrome(i, j, str)) {
            int cost = 1 + f(j + 1, n, str, dp);
            minCost = min(minCost, cost);
        }
    }

    return dp[i] = minCost;
}

int palindromePartitioning(string str)
{
    int n = str.size();
    vector<int> dp(n, -1);
    return f(0, n, str, dp) - 1;
}





/******************** Tabulation *********************/
bool isPalindrome(int i, int j, string &str) {
    while(i < j) {
        if(str[i] != str[j])
            return false;
        i++;
        j--;
    }
    return true;
}

int palindromePartitioning(string str)
{
    int n = str.size();
    vector<int> dp(n + 1, 0);
    
    for(int i = n - 1; i >= 0; i--) {
        int minCost = INT_MAX;
        for(int j = i; j < n; j++) {
            if(isPalindrome(i, j, str)) {
                int cost = 1 + dp[j + 1];
                minCost = min(minCost, cost);
            }
        }
        dp[i] = minCost;
    }
    
    return dp[0] - 1;
}
