/*
Implement more trie functions like CountWordsEqualTo(), CountPrefixEqualTo(), eraseWord()

Now this can be done in similar way but the trie definition will change:
struct Node {
    Node *links[26];
    int countEnds = 0;
    int countPrefix = 0;
};
*/

#include <bits/stdc++.h> 

struct Node {
    Node *links[26];
    int countEndsWith = 0;
    int countPrefix = 0;

    bool containsKey(char ch) {
        return links[ch - 'a'];
    }

    void put(char ch, Node *node) {
        links[ch - 'a'] = node;
    }

    Node *get(char ch) {
        return links[ch - 'a'];
    }

    void increaseCount() {
        countEndsWith++;
    }

    void increasePrefix() {
        countPrefix++;
    }

    void decreaseCount() {
        countEndsWith--;
    }

    void decreasePrefix() {
        countPrefix--;
    }

    int getWordCount() {
        return countEndsWith;
    }

    int getPrefixCount() {
        return countPrefix;
    }
};

class Trie{
private:
    Node *root;
public:
    Trie(){
        root = new Node();
    }

    void insert(string &word){
        Node *node = root;
        for(int i = 0; i < word.length(); i++) {
            if(!node->containsKey(word[i])) 
                node->put(word[i], new Node());
            node = node->get(word[i]);
            node->increasePrefix();
        }
        node->increaseCount();
    }

    int countWordsEqualTo(string &word){
        Node *node = root;
        for(int i = 0; i < word.length(); i++) {
            if(!node->containsKey(word[i]))
                return 0;
            node = node->get(word[i]);
        }
        return node->getWordCount();
    }

    int countWordsStartingWith(string &word){
        Node *node = root;
        for(int i = 0; i < word.length(); i++) {
            if(!node->containsKey(word[i]))
                return 0;
            node = node->get(word[i]);
        }
        return node->getPrefixCount();
    }

    void erase(string &word){
        Node *node = root;
        for(int i = 0; i < word.length(); i++) {
            if(!node->containsKey(word[i]))
                return;
            node = node->get(word[i]);
            node->decreasePrefix();
        }
        node->decreaseCount();
    }
};
