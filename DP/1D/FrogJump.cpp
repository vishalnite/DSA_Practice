/*
Find the minimum energy that is required to reach from stair 1 to N. The frog can jump 1 or 2 stairs at a time. The energy released is the 
difference between the height of stairs.
*/


/************************ Recursive Solution **************************/
#include <bits/stdc++.h> 

int minEnergy(int n, vector<int> &heights) {
    if(n == 0)
        return 0;

    int left = minEnergy(n - 1, heights)  + abs(heights[n] - heights[n - 1]);

    int right = INT_MAX;
    if(n > 1) {
        right = minEnergy(n - 2, heights) + abs(heights[n] - heights[n - 2]);
    }

    return min(left, right);
}

int frogJump(int n, vector<int> &heights)
{
    return minEnergy(n - 1, heights, dp);
}


/************************ Memoization **************************/
#include <bits/stdc++.h> 

int minEnergy(int n, vector<int> &heights, vector<int> &dp) {
    if(n == 0)
        return 0;

    if(dp[n] != -1)
        return dp[n];

    int left = minEnergy(n - 1, heights, dp)  + abs(heights[n] - heights[n - 1]);

    int right = INT_MAX;
    if(n > 1) {
        right = minEnergy(n - 2, heights, dp) + abs(heights[n] - heights[n - 2]);
    }

    return dp[n] = min(left, right);
}

int frogJump(int n, vector<int> &heights)
{
    vector<int> dp(n, -1);

    minEnergy(n - 1, heights, dp);

    return dp[n - 1];
}


/************************ Tabulation **************************/
#include <bits/stdc++.h> 

int frogJump(int n, vector<int> &heights)
{
    vector<int> dp(n, 0);

    for(int i = 1; i < n; i++) {
        int left = dp[i - 1] + abs(heights[i] - heights[i - 1]);
        
        int right = INT_MAX;
        if(i > 1) {
            right = dp[i - 2] + abs(heights[i] - heights[i - 2]);
        }

        dp[i] = min(left, right);
    }

    return dp[n - 1];
}


/************************ Space Optimization **************************/
#include <bits/stdc++.h> 

int frogJump(int n, vector<int> &heights)
{
    int prev = 0, prev2 = 0;

    for(int i = 1; i < n; i++) {
        int left = prev + abs(heights[i] - heights[i - 1]);
        
        int right = INT_MAX;
        if(i > 1) {
            right = prev2 + abs(heights[i] - heights[i - 2]);
        }

        prev2 = prev;
        prev = min(left, right);
    }

    return prev;
}
