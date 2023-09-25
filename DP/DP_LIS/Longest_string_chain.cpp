/*
Find the length of the longest string chain that can be formed from the given array of strings.
String chain is a sequence of strings where each string can be formed by adding one character in its predecessor.

If we observe carefully then it is similar to LIS problem, except here we need to check if the difference between strings is only 1 character.
So if we can implement that function then it becomes easy.
Also we need to sort the strings array as we are told to find a sequence.
*/

bool checkPossible(string &s1, string &s2) {
    if(s1.size() !=  s2.size() + 1)
        return false;

    int first = 0, second = 0;
    while(first < s1.size()) {
        if(s1[first] == s2[second]) {
            first++;
            second++;
        }
        else {
            first++;
        }
    }

    if(first == s1.size() && second == s2.size())
        return true;
    return false;
}

static bool comp(string &s1, string &s2) {
    return s1.size() < s2.size();
}

int longestStrChain(vector<string> &arr){
    int n = arr.size();
    vector<int> dp(n, 1);
    int maxi = 1;

    sort(arr.begin(), arr.end(), comp);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++) {
            if(checkPossible(arr[i], arr[j]) && dp[i] < 1 + dp[j]) {
                dp[i] = 1 + dp[j];
            }
        }
        maxi = max(maxi, dp[i]);
    }

    return maxi;
}