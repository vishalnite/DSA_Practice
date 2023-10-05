/*
Count distinct substrings from the given string.

- This problem can be solve by generating all substrings and putting it into a set.
    This will take a large space for putting all the distinct substrings.

- Instead we can use trie to count distinct substrings because trie will take duplicates only once. We just need to put a character 
    if it is not already in the trie and increase the count as it will be distinct.
*/

struct Node {
    Node *links[26];

    bool containsKey(char ch) {
        return links[ch - 'a'];
    }

    void put(char ch, Node *node) {
        links[ch - 'a'] = node;
    }

    Node *get(char ch) {
        return links[ch - 'a'];
    }
};

int countDistinctSubstrings(string &s)
{
    int n = s.size();
    int cnt = 0;
    Node *root = new Node();

    for(int i = 0; i < n; i++) {
        Node *node = root;
        for(int j = i; j < n; j++) {
            if(!node->containsKey(s[j])) {
                cnt++;
                node->put(s[j], new Node());
            }
            node = node->get(s[j]);
        }
    }

    return cnt + 1;
}