/*
This concept is very important when solving XOR problems using trie.
Given an array find the maximum XOR that can be obtained by operating it against a given number x.

- To solve this problem
    Create trie node 
    struct Node {
        Node *links[2]; //binary bits 0/1
    };

    This trie will be at max of length 32
 - Insert every element of the array in the trie in binary form
 - Now we want the bits from left to right to be opposite of the bit of x to get maximum
 - Therefore keep eliminating elements that do not fit this condition. If there are no desired elements then take what's available.

 Similarly to solve this problem,
 Insert array 1 in trie.
 Now for each element in array 2, find the maxXOR from the trie.

T.C - O(N x 32) + O(M x 32)
S.C - Not sure in case of tries [worst case -- not possible -- O(N x 32)]
*/

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

int maximumXor(vector<int> A)
{
    Trie t;
    int maxXOR = 0;

    for(int i : A) {
        t.insert(i);
    }

    for(int i : A) {
        maxXOR = max(maxXOR, t.getMax(i));
    }

    return maxXOR;
}