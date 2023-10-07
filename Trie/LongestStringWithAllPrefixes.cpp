/*
Given an array of strings. Return the longest complete string from the array.
A complete string in one whose all prefixes are available in the array.
Also if there are more than one complete string of same length then return lexicographically smallest one.

- To solve this problem, insert all the strings in a trie data structure.
- Also create a function that checks if all the prefixes of the string exists or not
*/

#include <bits/stdc++.h> 

struct Node {
    Node *links[26];
    bool flag = false;

    bool containsKey(char ch) {
        return links[ch - 'a'];
    }

    Node *get(char ch) {
        return links[ch - 'a'];
    }

    void put(char ch, Node *node) {
        links[ch - 'a'] = node;
    }

    void setEnd() {
        flag = true;
    }

    bool isEnd() {
        return flag;
    }
};

class Trie {
    private: 
        Node *root;
    public:
        Trie() {
            root = new Node();
        }

        void insert(string &word) {
            Node *node = root;
            for(int i = 0; i < word.length(); i++) {
                if(!node->containsKey(word[i])) {
                    node->put(word[i], new Node());
                }
                node = node->get(word[i]);
            }
            node->setEnd();
        }

        bool checkPrefixExists(string &word) {
            Node *node = root;
            for(int i = 0; i < word.length(); i++) {
                if(node->containsKey(word[i])) {
                    node = node->get(word[i]);
                    if(node->isEnd() == false)
                        return false;
                }
                else 
                    return false;
            }

            return true;
        }
};

string completeString(int n, vector<string> &a){
    Trie *t = new Trie;
    for(string it : a) {
        t->insert(it);
    }

    string longest = "";

    for(string it : a) {
        if(t->checkPrefixExists(it)) {
            if(it.length() > longest.length()) 
                longest = it;
            else if(it.length() == longest.length() && it < longest)
                longest = it;
        }
    }

    if(longest == "")
        return "None";
    return longest;
}