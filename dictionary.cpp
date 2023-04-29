#include <iostream>
#include <unordered_map>
#include <vector>

#define alphabet 26

struct TrieNode
{
    bool is_end_of_word;
    std::unordered_map<char, TrieNode *> children;
};

class Trie
{
public:
    Trie();

    void insert(const std::string &);
    void remove(const std::string &);
    std::vector<std::string> candidates;

    ~Trie(){};

private:
    TrieNode *root;
};

void Trie::insert(const std::string &query)
{
    TrieNode *current_node = root;
    for (char letter : query)
    {
        if (current_node->children.find(letter) == current_node->children.end())
        {
            current_node->children[letter] = new TrieNode;
        }
        current_node = current_node->children[letter];
    }
    current_node->is_end_of_word = true;
}

void Trie::remove(const std::string &query)
{
    
}

int main()
{
    return 0;
}
