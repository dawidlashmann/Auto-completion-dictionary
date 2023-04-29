#include <iostream>
#include <memory>

#define alphabet 26

struct TrieNode
{
    bool is_end_of_word;
    TrieNode *next_char[alphabet];
};

class Trie
{
public:
    Trie() : root(std::make_unique<TrieNode>()){};
    
    void insert(std::string &);
    void remove(std::string &);
    // std::vector<std::string> candidates();

    ~Trie(){};

private:
    std::unique_ptr<TrieNode> root;
};

void Trie::insert(std::string &word)
{
}

void Trie::remove(std::string &word)
{
    
}

int main()
{
    return 0;
}
