/*
Given a grid of 0, 1. We need to find the largest rectangle area containing only 1.

Pre-requisite:
Maximum rectangle in a histogram -- This problem was solved LSE and RSE using stack
We use the optimized version of it, which uses only one pass.

Each row of the matrix can be considered a histogram and thus the above approach can be applied to each row to find the maximum area.
*/

#include<bits/stdc++.h>

// Maximum reactangle in a histogram problem
int maxRectangle(vector<int> &heights, int n) {
	stack<int> st;
	int maxi = 0;

	for(int i = 0; i <= n; i++) {
		while(!st.empty() && (i == n || heights[st.top()] >= heights[i])) {
			int height = heights[st.top()];
			st.pop();
			int width;
			if(st.empty())
				width = i;
			else 
				width = (i - st.top() - 1);
			maxi = max(maxi, width * height);
		} 
		st.push(i);
	}

	return maxi;
}

int maximalAreaOfSubMatrixOfAll1(vector<vector<int>> &mat, int n, int m){
	vector<int> heights(m, 0);
	int maxi = 0;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(mat[i][j] == 1) 
				heights[j]++;
			else	
				heights[j] = 0;
		}
		int area = maxRectangle(heights, m);
		maxi = max(maxi, area);
	}

	return maxi;
}