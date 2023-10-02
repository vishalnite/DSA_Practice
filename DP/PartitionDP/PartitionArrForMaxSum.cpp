/*
Find the maximum sum that can be obtained after partitioning the array. Each partition of the array can be at max K size and all the 
elements of each partition changes to the maximum element in the partition.

- This problem is similar to palindrome partitioning and is solved using front partition.
- We will keep track of the length of the partition and the maximum element of the partition.
- Inside the loop we try to calculate the maximum sum by using (len * maxElem) and call the function again for the next partition.
- At the end just return the maximum sum obtained from each possible partitioning.
*/

/***************** Recursion ******************/
int f(int i, int n, vector<int> &arr, int k) {
    if(i == n)
        return 0;

    int len = 0;
    int maxElem = INT_MIN;
    int maxi = INT_MIN;

    for(int j = i; j < min(n, i + k); j++) {
        len++;
        maxElem = max(maxElem, arr[j]);
        int sum = len * maxElem + f(j + 1, n, arr, k);
        maxi = max(maxi, sum);
    }

    return maxi;
}

int maximumSubarray(vector<int> &arr, int k){
    int n = arr.size();
    return f(0, n, arr, k);
}




/***************** Memoization ******************/
int f(int i, int n, vector<int> &arr, int k, vector<int> &dp) {
    if(i == n)
        return 0;

    if(dp[i] != -1)
        return dp[i];

    int len = 0;
    int maxElem = INT_MIN;
    int maxi = INT_MIN;

    for(int j = i; j < min(n, i + k); j++) {
        len++;
        maxElem = max(maxElem, arr[j]);
        int sum = len * maxElem + f(j + 1, n, arr, k, dp);
        maxi = max(maxi, sum);
    }

    return dp[i] = maxi;
}

int maximumSubarray(vector<int> &arr, int k){
    int n = arr.size();
    vector<int> dp(n, -1);
    return f(0, n, arr, k, dp);
}




/***************** Tabulation ******************/
int maximumSubarray(vector<int> &arr, int k){
    int n = arr.size();
    vector<int> dp(n + 1, 0);

    for(int i = n - 1; i >= 0; i--) {
        int len = 0;
        int maxElem = INT_MIN;
        int maxi = INT_MIN;

        for(int j = i; j < min(n, i + k); j++) {
            len++;
            maxElem = max(maxElem, arr[j]);
            int sum = len * maxElem + dp[j + 1];
            maxi = max(maxi, sum);
        }

        dp[i] = maxi;
    }

    return dp[0];
}