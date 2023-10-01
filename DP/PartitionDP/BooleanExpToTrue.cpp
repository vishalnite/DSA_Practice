/*
Another problem on partition DP. It is very similar to MCM.
Here we want to find the number of ways to evaluate the boolean expression to be true.
Ultimately we want it to be true. The expression contains (T, F, &, |, ^).

- We can make partition at (i + 1 to j - 1 indices because operator is present in between two operands)
- To solve individual sub problems we can think of two base cases
    - When i > j return 0
    - when i == j return true if it is true else false
- Now make partitions and at each partition find the number of ways to make lT, rT, lF, rF
- Based on the operator find the number of ways

- There are three states that we need to maintain (i, j, isTrue)
*/


/***************** Recursion *****************/
#define ll long long int
int MOD = 1e9 + 7;

ll f(int i, int j, int isTrue, string &exp) {
    if(i > j)
        return 0;
    if(i == j) {
        if(isTrue)
            return exp[i] == 'T';
        else
            return exp[i] == 'F';
    }

    ll ways = 0;

    for(int ind = i + 1; ind <= j - 1; ind++) {
        ll lT = f(i, ind - 1, 1, exp);
        ll lF = f(i, ind - 1, 0, exp);
        ll rT = f(ind + 1, j, 1, exp);
        ll rF = f(ind + 1, j, 0, exp);

        if(exp[ind] == '&') {
            if(isTrue) {
                ways = (ways + (lT * rT) % MOD) % MOD;
            }
            else {
                ways = (ways + (lT * rF) % MOD + (lF * rT) % MOD + (lF * rF) % MOD) % MOD;
            }
        }
        else if(exp[ind] == '|') {
            if(isTrue) {
                ways = (ways + (lT * rF) % MOD + (lF * rT) % MOD + (lT * rT) % MOD) % MOD;
            }
            else {
                ways = (ways + (lF * rF) % MOD) % MOD;
            }
        }
        else {
            if(isTrue) {
                ways = (ways + (lT * rF) % MOD + (lF * rT) % MOD) % MOD;
            }
            else {
                ways = (ways + (lT * rT) % MOD + (lF * rF) % MOD) % MOD;
            }
        }
    }

    return ways;
}

int evaluateExp(string &exp) {
    int n = exp.size();
    return f(0, n - 1, 1, exp);
}




/***************** Memoization *****************/
#define ll long long int
int MOD = 1e9 + 7;

ll f(int i, int j, int isTrue, string &exp, vector<vector<vector<ll>>> &dp) {
    if(i > j)
        return 0;
    if(i == j) {
        if(isTrue)
            return exp[i] == 'T';
        else
            return exp[i] == 'F';
    }

    if(dp[i][j][isTrue] != -1)
        return dp[i][j][isTrue];

    ll ways = 0;

    for(int ind = i + 1; ind <= j - 1; ind++) {
        ll lT = f(i, ind - 1, 1, exp, dp);
        ll lF = f(i, ind - 1, 0, exp, dp);
        ll rT = f(ind + 1, j, 1, exp, dp);
        ll rF = f(ind + 1, j, 0, exp, dp);

        if(exp[ind] == '&') {
            if(isTrue) {
                ways = (ways + (lT * rT) % MOD) % MOD;
            }
            else {
                ways = (ways + (lT * rF) % MOD + (lF * rT) % MOD + (lF * rF) % MOD) % MOD;
            }
        }
        else if(exp[ind] == '|') {
            if(isTrue) {
                ways = (ways + (lT * rF) % MOD + (lF * rT) % MOD + (lT * rT) % MOD) % MOD;
            }
            else {
                ways = (ways + (lF * rF) % MOD) % MOD;
            }
        }
        else {
            if(isTrue) {
                ways = (ways + (lT * rF) % MOD + (lF * rT) % MOD) % MOD;
            }
            else {
                ways = (ways + (lT * rT) % MOD + (lF * rF) % MOD) % MOD;
            }
        }
    }

    return dp[i][j][isTrue] = ways;
}

int evaluateExp(string &exp) {
    int n = exp.size();
    vector<vector<vector<ll>>> dp(n, vector<vector<ll>>(n, vector<ll>(2, -1)));
    return f(0, n - 1, 1, exp, dp);
}




/***************** Tabulation *****************/
#define ll long long int
int MOD = 1e9 + 7;

int evaluateExp(string &exp) {
    int n = exp.size();
    vector<vector<vector<ll>>> dp(n, vector<vector<ll>>(n, vector<ll>(2, 0)));
    
    for(int i = 0; i < n; i++) {
        dp[i][i][1] = exp[i] == 'T';
        dp[i][i][0] = exp[i] == 'F';
    }

    for(int i = n - 1; i >= 0; i--) {
        for(int j = i + 1; j < n; j++) {
            for(int isTrue = 0; isTrue <= 1; isTrue++) {
                
                ll ways = 0;
                for(int ind = i + 1; ind <= j - 1; ind++) {
                    ll lT = dp[i][ind - 1][1];
                    ll lF = dp[i][ind - 1][0];
                    ll rT = dp[ind + 1][j][1];
                    ll rF = dp[ind + 1][j][0];

                    if(exp[ind] == '&') {
                        if(isTrue) {
                            ways = (ways + (lT * rT) % MOD) % MOD;
                        }
                        else {
                            ways = (ways + (lT * rF) % MOD + (lF * rT) % MOD + (lF * rF) % MOD) % MOD;
                        }
                    }
                    else if(exp[ind] == '|') {
                        if(isTrue) {
                            ways = (ways + (lT * rF) % MOD + (lF * rT) % MOD + (lT * rT) % MOD) % MOD;
                        }
                        else {
                            ways = (ways + (lF * rF) % MOD) % MOD;
                        }
                    }
                    else {
                        if(isTrue) {
                            ways = (ways + (lT * rF) % MOD + (lF * rT) % MOD) % MOD;
                        }
                        else {
                            ways = (ways + (lT * rT) % MOD + (lF * rF) % MOD) % MOD;
                        }
                    }
                }

                dp[i][j][isTrue] = ways;
            }
        }
    }
    
    return dp[0][n - 1][1];
}

