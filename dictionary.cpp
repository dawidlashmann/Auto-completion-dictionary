#include <iostream>
#include <unordered_map>
#include <vector>

#define alphabet 26

struct TrieNode
{
    bool is_end_of_word = false;
    std::unordered_map<char, TrieNode *> children;
};

class Trie
{
public:
    Trie();

    void insert(const std::string &);
    void remove(const std::string &);
    std::vector<std::string> candidates(const std::string &);

    ~Trie(){};

private:
    char traverse(TrieNode *, const std::string &, char, std::vector<std::string>&);

private:
    TrieNode *root;
};

void Trie::insert(const std::string &word)
{
    TrieNode *current_node = root;
    for (char letter : word)
    {
        if (current_node->children.find(letter) == current_node->children.end())
        {
            current_node->children[letter] = new TrieNode;
        }
        current_node = current_node->children[letter];
    }
    current_node->is_end_of_word = true;
}

void Trie::remove(const std::string &word)
{
    ///
}

std::vector<std::string> Trie::candidates(const std::string &query)
{
    std::vector<std::string> auto_completed_queries;
    TrieNode *current_node = root;
    for (char letter : query)
    {
        if (current_node->children.find(letter) == current_node->children.end())
        {
            std::cout << "No candidates for this query\n";
            return auto_completed_queries;
        }
        current_node = current_node->children[letter];
    }

    return auto_completed_queries;
}

char Trie::traverse(TrieNode *current_node, const std::string &prefix, char node_char, std::vector<std::string>& result)
{
    static std::string current_txt = "";
    current_txt = current_txt + node_char;
    if (current_node->children.empty())
    {
        return node_char;
    }

    if (current_node->is_end_of_word)
    {
        result.emplace_back(prefix + current_txt);
    }

    for (auto &node : current_node->children)
    {
        result.emplace_back(prefix + traverse(node.second, prefix, node.first));
    }
}

int main()
{
    return 0;
}
