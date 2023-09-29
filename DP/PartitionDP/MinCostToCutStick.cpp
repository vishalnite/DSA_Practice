/*
Find the minimum cost to cut the stick. We can cut the stick in any order but the cost will be the current length of the stick.

Intuition:
We can take the whole stick as a block and partition it in all possible ways and then find the minimum cost.

- Before doing that insert 0 at the front and N at the end.
- Also sort the order because the formula A[j + 1] - A[i - 1] will give us the current length of the stick and it also ensures that each part after
    cutting is independent.
- Remember we are using the size of the cuts array.
*/

/********************** Recursion ************************/
#include <bits/stdc++.h> 

int f(int i, int j, vector<int> &cuts) {
    if(i > j)
        return 0;

    int mini = 1e9;
    for(int ind = i; ind <= j; ind++) {
        int cost = cuts[j + 1] - cuts[i - 1] + f(i, ind - 1, cuts) + f(ind + 1, j, cuts);
        mini = min(mini, cost);
    }

    return mini;
}

int cost(int n, int c, vector<int> &cuts){
    cuts.push_back(n);
    cuts.insert(cuts.begin(), 0);
    sort(cuts.begin(), cuts.end());

    return f(1, c, cuts);
}




/********************** Memoization ************************/
#include <bits/stdc++.h> 

int f(int i, int j, vector<int> &cuts, vector<vector<int>> &dp) {
    if(i > j)
        return 0;

    if(dp[i][j] != -1)
        return dp[i][j];

    int mini = 1e9;
    for(int ind = i; ind <= j; ind++) {
        int cost = cuts[j + 1] - cuts[i - 1] + f(i, ind - 1, cuts, dp) + f(ind + 1, j, cuts, dp);
        mini = min(mini, cost);
    }

    return dp[i][j] = mini;
}

int cost(int n, int c, vector<int> &cuts){
    cuts.push_back(n);
    cuts.insert(cuts.begin(), 0);
    sort(cuts.begin(), cuts.end());
    vector<vector<int>> dp(c + 1, vector<int>(c + 1, -1));

    return f(1, c, cuts, dp);
}




/********************** Tabulation ************************/
#include <bits/stdc++.h> 

int cost(int n, int c, vector<int> &cuts){
    cuts.push_back(n);
    cuts.insert(cuts.begin(), 0);
    sort(cuts.begin(), cuts.end());
    vector<vector<int>> dp(c + 2, vector<int>(c + 2, 0));

    for(int i = c; i >= 1; i--) {
        for(int j = 1; j <= c; j++) {
            if(i > j)
                continue;

            int mini = 1e9;
            for(int ind = i; ind <= j; ind++) {
                int cost = cuts[j + 1] - cuts[i - 1] + dp[i][ind - 1] + dp[ind + 1][j];
                mini = min(mini, cost);
            }
            dp[i][j] = mini;
        }
    }

    return dp[1][c];
}
