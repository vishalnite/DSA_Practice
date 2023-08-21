/*
Chocolate Pickup -- Find the maximum chocolate that can be picked by Alice(0, 0) and Bob(0, c - 1) from a grid. If both of them reach the 
same cell then it is taken only once.
[3D DP problem -- because the number of paremeters passed is 3]
[When j1 == j2 -- take only once -- else add both of them]
[Total 9 moves are possible at each step -- Take the maximum among them]
[Out of bound condition should come before base condition]
*/

/****************** Recursion *********************/
#include <bits/stdc++.h>

int f(int i, int j1, int j2, int r, int c, vector<vector<int>> &grid) {
    if(j1 < 0 || j1 >= c || j2 < 0 || j2 >= c) {
        return -1e9;
    } 
    
    if(i == r - 1) {
        if(j1 == j2) 
            return grid[i][j1];
        else 
            return grid[i][j1] + grid[i][j2];
    }

    int maxi = INT_MIN;
    for(int di = -1; di <= 1; di++) {
        for(int dj = -1; dj <= 1; dj++) {
            int ans;
            if(j1 == j2) {
                ans = grid[i][j1] + f(i + 1, j1 + di, j2 + dj, r, c, grid);
            }
            else {
                ans = grid[i][j1] + grid[i][j2] + f(i + 1, j1 + di, j2 + dj, r, c, grid);
            }

            maxi = max(maxi, ans);
        }
    }

    return maxi;
}

int maximumChocolates(int r, int c, vector<vector<int>> &grid) {
    return f(0, 0, c - 1, r, c, grid);
}


/****************** Memoization *********************/
#include <bits/stdc++.h>

int f(int i, int j1, int j2, int r, int c, vector<vector<int>> &grid, 
vector<vector<vector<int>>> &dp) {
    if(j1 < 0 || j1 >= c || j2 < 0 || j2 >= c) {
        return -1e9;
    }
    
    if(i == r - 1) {
        if(j1 == j2) 
            return grid[i][j1];
        else 
            return grid[i][j1] + grid[i][j2];
    }

    if(dp[i][j1][j2] != -1)
        return dp[i][j1][j2];

    int maxi = INT_MIN;
    for(int di = -1; di <= 1; di++) {
        for(int dj = -1; dj <= 1; dj++) {
            int ans;
            if(j1 == j2) {
                ans = grid[i][j1] + f(i + 1, j1 + di, j2 + dj, r, c, grid, dp);
            }
            else {
                ans = grid[i][j1] + grid[i][j2] + f(i + 1, j1 + di, j2 + dj, r, c, grid, dp);
            }

            maxi = max(maxi, ans);
        }
    }

    return dp[i][j1][j2] = maxi;
}

int maximumChocolates(int r, int c, vector<vector<int>> &grid) {
    //dp[r][c][c]
    vector<vector<vector<int>>> dp(r, vector<vector<int>>(c, vector<int>(c, -1)));
    return f(0, 0, c - 1, r, c, grid, dp);
}


/****************** Tabulation *********************/
#include <bits/stdc++.h>

int maximumChocolates(int r, int c, vector<vector<int>> &grid) {
    //dp[r][c][c]
    vector<vector<vector<int>>> dp(r, vector<vector<int>>(c, vector<int>(c, 0)));
    
    for(int j1 = 0; j1 < c; j1++) {
        for(int j2 = 0; j2 < c; j2++) {
            if(j1 == j2) 
                dp[r - 1][j1][j2] = grid[r - 1][j1];
            else 
                dp[r - 1][j1][j2] = grid[r - 1][j1] + grid[r - 1][j2];
        }
    }

    for(int i = r - 2; i >= 0; i--) {
        for(int j1 = 0; j1 < c; j1++) {
            for(int j2 = 0; j2 < c; j2++) {
                int maxi = INT_MIN;

                for(int di = -1; di <= 1; di++) {
                    for(int dj = -1; dj <= 1; dj++) {
                        int ans;

                        if(j1 == j2) 
                            ans = grid[i][j1];
                        else 
                            ans = grid[i][j1] + grid[i][j2];

                        if(j1 + di < 0 || j1 + di >= c 
                        || j2 + dj < 0 || j2 + dj >= c)
                            ans += -1e9;
                        else
                            ans += dp[i + 1][j1 + di][j2 + dj];

                        maxi = max(maxi, ans);
                    }
                }

                dp[i][j1][j2] = maxi;
            }
        }
    }
    
    return dp[0][0][c - 1];
}


/****************** Space Optimization *********************/
#include <bits/stdc++.h>

int maximumChocolates(int r, int c, vector<vector<int>> &grid) {
    //dp[r][c][c]
    vector<vector<int>> prev(c, vector<int>(c, 0));
    
    for(int j1 = 0; j1 < c; j1++) {
        for(int j2 = 0; j2 < c; j2++) {
            if(j1 == j2) 
                prev[j1][j2] = grid[r - 1][j1];
            else 
                prev[j1][j2] = grid[r - 1][j1] + grid[r - 1][j2];
        }
    }

    for(int i = r - 2; i >= 0; i--) {
        vector<vector<int>> cur(c, vector<int>(c));
        for(int j1 = 0; j1 < c; j1++) {
            for(int j2 = 0; j2 < c; j2++) {
                int maxi = INT_MIN;

                for(int di = -1; di <= 1; di++) {
                    for(int dj = -1; dj <= 1; dj++) {
                        int ans;

                        if(j1 == j2) 
                            ans = grid[i][j1];
                        else 
                            ans = grid[i][j1] + grid[i][j2];

                        if(j1 + di < 0 || j1 + di >= c 
                        || j2 + dj < 0 || j2 + dj >= c)
                            ans += -1e9;
                        else
                            ans += prev[j1 + di][j2 + dj];

                        maxi = max(maxi, ans);
                    }
                }

                cur[j1][j2] = maxi;
            }
        }
        prev = cur;
    }
    
    return prev[0][c - 1];
}