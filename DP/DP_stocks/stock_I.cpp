/*
DP on stocks -- We must do space optimization
The stock can be bought and sold only once and we need to return the maximum profit that can be achieved from this.

It can be solved constructively but it comes under DP because DP basically means remenbering the past.
If I am selling a stock on the ith day then obviously I want to buy it on a day from (1 -- (i - 1)) and the price should be minimum.
*/

#include <bits/stdc++.h> 
int maximumProfit(vector<int> &prices){
    
    int n = prices.size();
    int minPrice = prices[0];
    int maxProfit = 0;

    for(int i = 1; i < n; i++) {
        int profit = prices[i] - minPrice;
        maxProfit = max(maxProfit, profit);
        minPrice = min(minPrice, prices[i]);
    }

    return maxProfit;

}