/*
Find the maximum sum of the subsequence from the given array if no adjacent elements are allowed.
[Resursion -- pick or not pick]
*/

/********************* Recursion ************************/
#include <bits/stdc++.h> 

int getMaxSum(int ind, vector<int> &nums) {

    if(ind == 0)
        return nums[0];
    if(ind == -1)
        return 0;

    int pick = nums[ind] + getMaxSum(ind - 2, nums);
    int notPick = 0 + getMaxSum(ind - 1, nums);

    return max(pick, notPick);
}

int maximumNonAdjacentSum(vector<int> &nums){
    int n = nums.size();
    return getMaxSum(n - 1, nums);
}


/********************* Memoization ************************/
#include <bits/stdc++.h> 

int getMaxSum(int ind, vector<int> &nums, vector<int> &dp) {

    if(ind == 0)
        return dp[ind] = nums[0];
    if(ind == -1)
        return 0;

    if(dp[ind] != -1)
        return dp[ind];

    int pick = nums[ind] + getMaxSum(ind - 2, nums, dp);
    int notPick = 0 + getMaxSum(ind - 1, nums, dp);

    return dp[ind] = max(pick, notPick);
}

int maximumNonAdjacentSum(vector<int> &nums){
    int n = nums.size();
    vector<int> dp(n, -1);
    getMaxSum(n - 1, nums, dp);

    return dp[n - 1];
}


/********************* Tabulation ************************/
#include <bits/stdc++.h> 

int maximumNonAdjacentSum(vector<int> &nums){
    int n = nums.size();
    vector<int> dp(n);
    dp[0] = nums[0];

    for(int i = 1; i < n; i++) {
        int pick = nums[i];
        if(i > 1)
            pick += dp[i - 2];

        int notPick = 0 + dp[i - 1];

        dp[i] = max(pick, notPick);
    }

    return dp[n - 1];
}


/********************* Space Optimization ************************/
#include <bits/stdc++.h> 

int maximumNonAdjacentSum(vector<int> &nums){
    int n = nums.size();
    int prev = nums[0];
    int prev2 = 0;

    for(int i = 1; i < n; i++) {
        int pick = nums[i];
        if(i > 1)
            pick += prev2;

        int notPick = 0 + prev;

        int curi = max(pick, notPick);
        prev2 = prev;
        prev = curi;
    }

    return prev;
}