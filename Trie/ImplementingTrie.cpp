/*
TRIE Data structure -- one of the toughest data structures

TRIE - basically used for autocomplete and spell checker
It implements 3 functionalities

Basic structure of trie
struct Node {
    Node *links[26];
    bool isEnd;
};

A trie will always have a root node

- Insert(word) -- Insert a given word into the TRIE data structure
We start with the root node and if the character is present then we move to the next trie
If it is not present then create a new reference trie from the given character


- Search(word) -- Search whether a given word exists in trie
Start searching from the root node
If the character is not present then return a false
otherwise move ahead
At the end if we find that isEnd is set as true then return true


- StartsWith(word) -- Search whether a word starts with the given word or not
Similar to Search(word) but at the end we do not check whether it is end or not. Just return a true after loop gets over.


- Write a readable code by implementing methods in the Node class
*/

/************************* Coding Ninjas ************************/
/*
Definition of TrieNode class.

class TrieNode {
public:
    TrieNode * children[26];
    bool isEnd;
    TrieNode()
    {
        isEnd=false;
        for(int i=0;i<26;i++)
            children[i]=NULL;
    }

};*/

void solution::insert(string word)
{
    TrieNode *node = root;

    for(int i = 0; i < word.length(); i++) {
        int idx = word[i] - 'a';
        if(node->children[idx] == NULL) {
            node->children[idx] = new TrieNode;
        }
        node = node->children[idx];
    }

    node->isEnd = true;
}

bool solution::search(string word)
{
    TrieNode *node = root;

    for(int i = 0; i < word.length(); i++) {
        int idx = word[i] - 'a';
        if(!node->children[idx])
            return false;
        node = node->children[idx];
    }

    return node->isEnd;
}

bool solution::startsWith(string word)
{
    TrieNode *node = root;

    for(int i = 0; i < word.length(); i++) {
        int idx = word[i] - 'a';
        if(!node->children[idx])
            return false;
        node = node->children[idx];
    }

    return true;
}


/************************** Leetcode *****************************/
// Readable code
struct Node {
    Node *links[26];
    bool flag = false;

    bool containsKey(char ch) {
        return links[ch - 'a'];
    }

    void put(char ch) {
        links[ch - 'a'] = new Node();
    }

    Node *get(char ch) {
        return links[ch - 'a'];
    }

    void setEnd() {
        flag = true;
    }

    bool isEnd() {
        return flag;
    }
};

class Trie {
    Node *root;
public:
    Trie() {
        root = new Node();
    }
    
    void insert(string word) {
        Node *node = root;
        for(int i = 0; i < word.length(); i++) {
            if(!node->containsKey(word[i])) {
                node->put(word[i]);
            }
            node = node->get(word[i]);
        }

        node->setEnd();
    }
    
    bool search(string word) {
        Node *node = root;
        for(int i = 0; i < word.length(); i++) {
            if(!node->containsKey(word[i]))
                return false;
            node = node->get(word[i]);
        }

        return node->isEnd();
    }
    
    bool startsWith(string prefix) {
        Node *node = root;
        for(int i = 0; i < prefix.length(); i++) {
            if(!node->containsKey(prefix[i]))
                return false;
            node = node->get(prefix[i]);
        }

        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */