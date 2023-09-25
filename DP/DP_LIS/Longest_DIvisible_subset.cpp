/*
Find the longest divisible subset. [subset is any combination of array elements]
Any pair from the array should be divisible -- (a, b) -- Either (a % b = 0) or (b % a = 0)

If we observe carefully this problem boils down to finding LIS if we sort the array.
Suppose [1, 3, 4, 8]
If 4 is divisible by 1 and 8 is divisible by 4 then 8 is obviously divisible by 1.

[Not Sure -- Thumb rule -- for any subset problem, sort the array and then try to think about solution]
*/

vector<int> divisibleSet(vector<int> &arr)
{
    int n = arr.size();
    vector<int> dp(n, 1), hash(n);
    int lastIndex = 0;
    int maxi = 1;

    sort(arr.begin(), arr.end());

    for(int i = 0; i < n; i++) {
        hash[i] = i;
        for(int j = 0; j < i; j++) {
            if(arr[i] % arr[j] == 0 && 1 + dp[j] > dp[i]) {
                dp[i] = 1 + dp[j];
                hash[i] = j;
            }
        }
        if(dp[i] > maxi) {
            maxi = dp[i];
            lastIndex = i;
        }
    }

    vector<int> ans;
    ans.push_back(arr[lastIndex]);
    while(hash[lastIndex] != lastIndex) {
        lastIndex = hash[lastIndex];
        ans.push_back(arr[lastIndex]);
    }

    reverse(ans.begin(), ans.end());
    return ans;
}