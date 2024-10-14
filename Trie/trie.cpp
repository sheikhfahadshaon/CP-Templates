#include <bits/stdc++.h>
using namespace std;

struct Node
{
    Node *links[26];
    bool flag = false; // determines if it's the end node

    bool containsKey(int ind)
    {
        return (links[ind] != NULL);
    }

    void put(int ind, Node *node)
    {
        links[ind] = node;
    }

    Node *get(int ind)
    {
        return links[ind];
    }

    void setEnd()
    {
        flag = true;
    }

    bool isEnd()
    {
        return flag;
    }
};

class Trie
{
private:
    Node *root;

public:
    Trie()
    {
        root = new Node();
    }

    void insert(string word)
    {
        Node *node = root;
        for (int i = 0; i < word.length(); i++)
        {
            if (!node->containsKey(word[i] - 'a'))
                node->put(word[i] - 'a', new Node());
            node = node->get(word[i] - 'a');
        }
        node->setEnd();
    }

    bool search(string word)
    {
        Node *node = root;
        for (int i = 0; i < word.length(); i++)
        {
            if (!node->containsKey(word[i] - 'a'))
                return false;
            node = node->get(word[i] - 'a');
        }

        return node->isEnd();
    }

    bool startsWith(string prefix)
    {
        Node *node = root;
        for (int i = 0; i < prefix.length(); i++)
        {
            if (!node->containsKey(prefix[i] - 'a'))
                return false;
            node = node->get(prefix[i] - 'a');
        }

        return true;
    }
};