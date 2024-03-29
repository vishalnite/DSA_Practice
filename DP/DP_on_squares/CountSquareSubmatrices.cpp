/*
Count the number of square submatrices that contain only 1.

Generally, in DP on squares we use tabulation method because it is intuitive.
- Make another matrix with same size as the original array
- Copy first row and first column
- Now take the minimum of (previous row's cell, previous column's cell, previous diagonal cell) and add a 1
- This is because our DP array is basically storing the number of squares that can be made upto index(i, j)
- Dry run the code for better understanding
*/

int countSquares(int n, int m, vector<vector<int>> &arr) {
    vector<vector<int>> dp(n, vector<int>(m, 0));

    for(int j = 0; j < m; j++) 
        dp[0][j] = arr[0][j];

    for(int i = 0; i < n; i++) 
        dp[i][0] = arr[i][0];

    for(int i = 1; i < n; i++) {
        for(int j = 1; j < m; j++) {
            if(arr[i][j] == 1) {
                dp[i][j] = min({dp[i - 1][j], dp[i - 1][j - 1], dp[i][j - 1]}) + 1;
            }
        }
    }

    int ans = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            ans += dp[i][j];
        }
    }

    return ans;
}