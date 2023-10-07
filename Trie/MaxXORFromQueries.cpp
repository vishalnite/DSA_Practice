/*
Given an array containing N elements. Also a list of queries consisting if (xi, ai) where xi is the number to find max XOR and ai
denotes that the elements taken from the array should be less than or equal to ai.

-- Finding max XOR remains same from previous problem -- Maximum XOR in an array

We will use offline queries to solve this problem
- Sort the given array and create a list containing elements as {ai, {xi, i}}.
- Also sort offline queries list.
- Offline queries ensure that we insert elements in trie upto ai, thus makes finding XOR easier.

*/

#include<algorithm>

struct Node {
	Node *links[2];

	bool containsKey(int bit) {
		return links[bit];
	}

	void put(int bit, Node *node) {
		links[bit] = node;
	}

	Node *get(int bit) {
		return links[bit];
	}
};

class Trie {
	private:
		Node *root;
	public:
		Trie() {
			root = new Node();
		}

		void insert(int num) {
			Node *node = root;

			for(int i = 31; i >= 0; i--) {
				int bit = (num >> i) & 1;
				if(!node->containsKey(bit)) {
					node->put(bit, new Node());
				}
				node = node->get(bit);
			}
		}

		int getMax(int num) {
			Node *node = root;
			int maxNum = 0;

			for(int i = 31; i >= 0; i--) {
				int bit = (num >> i) & 1;
				if(node->containsKey(1 - bit)) {
					maxNum = maxNum | (1 << i);
					node = node->get(1 - bit);
				}
				else {
					node = node->get(bit);
				}
			}

			return maxNum;
		}
};

vector<int> maxXorQueries(vector<int> &arr, vector<vector<int>> &queries){
	int n = arr.size();
	int q = queries.size();
	sort(arr.begin(), arr.end());

	vector<pair<int, pair<int, int>>> oQ;
	for(int i = 0; i < q; i++) {
		oQ.push_back({queries[i][1], {queries[i][0], i}});
	}

	sort(oQ.begin(), oQ.end());

	vector<int> ans(q, 0);
	Trie t;
	int ind = 0;

	for(int i = 0; i < q; i++) {
		int ai = oQ[i].first;
		int xi = oQ[i].second.first;
		int pos = oQ[i].second.second;

		while(ind < n && arr[ind] <= ai) {
			t.insert(arr[ind]);
			ind++;
		}

		if(ind == 0)
			ans[pos] = -1;
		else
			ans[pos] = t.getMax(xi);
	}

	return ans;
}