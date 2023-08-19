/*
Find the maximum amount the thief can rob from a stree if no two adjacent houses can be robbed. Street is circular i.e, last and first house are
adjacent.
[Same as Maximum Subsequence Sum with no adjacent elements -- Create two auxiliary arrays(remove either first or last index)]

T.C - O(N)
S.C - O(2N)
*/

#include <bits/stdc++.h> 

long long maxRobbedAmount(vector<int> &house) {
    int n = house.size();
    long long prev = house[0];
    long long prev2 = 0;

    for(int i = 1; i < n; i++) {
        long long pick = house[i];
        if(i > 1)
            pick += prev2;
        long long notPick = 0 + prev;

        long long curi = max(pick, notPick);
        prev2 = prev;
        prev = curi;
    }

    return prev;
}

long long int houseRobber(vector<int>& valueInHouse)
{
    vector<int> temp1, temp2;
    int n = valueInHouse.size();

    if(n == 1)
        return valueInHouse[0];

    for(int i = 0; i < n; i++) {
        if(i != 0)
            temp1.push_back(valueInHouse[i]);
        if(i != n - 1)
            temp2.push_back(valueInHouse[i]);
    }

    return max(maxRobbedAmount(temp1), maxRobbedAmount(temp2));
}