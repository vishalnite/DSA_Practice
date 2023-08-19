/*
A ninja can perform one out of three tasks in a day. He should not perform same activities on two consecutive days. What is the maximum 
points that the ninja can earn.
[Greedy will not work because at certain point in future it will get wrong]
[DP -- Try out all possible combinations of training schedule]
[At day 0, we do not have anything further, so this is the base case]
*/

/******************* Recursion **********************/
int findMaxPoints(int day, int last, vector<vector<int>> &points) {
    if(day == 0) {
        int maxi = 0;
        for(int task = 0; task < 3; task++) {
            if(task != last) {
                maxi = max(maxi, points[day][task]);
            }
        }

        return maxi;
    }

    int maxi = 0;
    for(int task = 0; task < 3; task++) {
        if(task != last) {
            int point = points[day][task] + findMaxPoints(day - 1, task, points);
            maxi = max(maxi, point);
        }
    }

    return maxi;
}

int ninjaTraining(int n, vector<vector<int>> &points)
{ 
    return findMaxPoints(n - 1, 3, points);
}


/******************* Memoization **********************/
int findMaxPoints(int day, int last, vector<vector<int>> &points,
vector<vector<int>> &dp) {
    if(day == 0) {
        int maxi = 0;
        for(int task = 0; task < 3; task++) {
            if(task != last) {
                maxi = max(maxi, points[day][task]);
            }
        }

        return maxi;
    }

    if(dp[day][last] != -1)
        return dp[day][last];

    int maxi = 0;
    for(int task = 0; task < 3; task++) {
        if(task != last) {
            int point = points[day][task] + findMaxPoints(day - 1, task, points, dp);
            maxi = max(maxi, point);
        }
    }

    return dp[day][last] = maxi;
}

int ninjaTraining(int n, vector<vector<int>> &points)
{
    vector<vector<int>> dp(n, vector<int>(4, -1));
    
    return findMaxPoints(n - 1, 3, points, dp);
}


/******************* Tabulation **********************/
int ninjaTraining(int n, vector<vector<int>> &points)
{
    vector<vector<int>> dp(n, vector<int>(4, 0));
    
    dp[0][0] = max(points[0][1], points[0][2]);
    dp[0][1] = max(points[0][0], points[0][2]);
    dp[0][2] = max(points[0][1], points[0][0]);
    dp[0][3] = max(points[0][0], max(points[0][1], points[0][2]));

    for(int day = 1; day < n; day++) {
        for(int last = 0; last < 4; last++) {
            dp[day][last] = 0;

            for(int task = 0; task < 3; task++) {
                if(task != last) {
                    int point = points[day][task] + dp[day - 1][task];
                    dp[day][last] = max(dp[day][last], point);
                } 
            }
        }
    }

    return dp[n - 1][3];
}


/******************* Space Optimization **********************/
int ninjaTraining(int n, vector<vector<int>> &points)
{
    vector<int> prev(4, 0);
    
    prev[0] = max(points[0][1], points[0][2]);
    prev[1] = max(points[0][0], points[0][2]);
    prev[2] = max(points[0][1], points[0][0]);
    prev[3] = max(points[0][0], max(points[0][1], points[0][2]));

    for(int day = 1; day < n; day++) {
        vector<int> temp(4);
        for(int last = 0; last < 4; last++) {
            temp[last] = 0;

            for(int task = 0; task < 3; task++) {
                if(task != last) {
                    int point = points[day][task] + prev[task];
                    temp[last] = max(temp[last], point);
                } 
            }
        }
        prev = temp;
    }

    return prev[3];
}