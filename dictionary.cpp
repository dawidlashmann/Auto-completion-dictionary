#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>

struct TrieNode
{
    bool is_end_of_word = false;
    // if a database is big we could reserve memory on creation: children.reserve(26)
    std::unordered_map<char, TrieNode *> children;
};

class Trie
{
public:
    Trie(const std::string &);

    void add(const std::string &);
    void remove(const std::string &);
    std::vector<std::string> candidates(const std::string &);

    ~Trie();

private:
    void traverse(TrieNode *, const std::string &, const std::string &, std::vector<std::string> &);

private:
    TrieNode *root;
    std::fstream database;
};

Trie::Trie(const std::string &filename)
{
    root = new TrieNode;
    database.open(filename, std::ios::in);
    if (database.is_open())
    {
        std::string temp;
        while (getline(database, temp))
        {
            this->add(temp);
        }
    }
    database.close();
    database.open(filename, std::ios::trunc);
}

Trie::~Trie()
{
    for (auto &node : root->children)
    {
        std::string temp(1, node.first);
        for (auto word : this->candidates(temp))
        {
            database << word << std::endl;
        }
    }
    database.close();
}

void Trie::add(const std::string &word)
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
    TrieNode *current_node = root;
    std::vector<TrieNode *> path;
    path.reserve(word.length());
    for (char letter : word)
    {
        if (current_node->children.find(letter) == current_node->children.end())
        {
            std::cout << "This word is not in the database\n";
            return;
        }
        current_node = current_node->children[letter];
        path.emplace_back(current_node);
    }
    current_node->is_end_of_word = false;
    for (int node = path.size() - 1; node >= 0; node--)
    {
        if (path.at(node)->children.empty())
        {
        }
        else
        {
            break;
        }
    }
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

    traverse(current_node, query, "", auto_completed_queries);

    return auto_completed_queries;
}

void Trie::traverse(TrieNode *current_node, const std::string &prefix, const std::string &current_txt, std::vector<std::string> &result)
{
    if (current_node->is_end_of_word)
    {
        result.push_back(prefix + current_txt);
    }
    for (auto &next_node : current_node->children)
    {
        traverse(next_node.second, prefix, current_txt + (char)next_node.first, result);
    }
}

int main()
{
    Trie dictionary("databa.txt");
    dictionary.add("car");
    dictionary.add("carpet");
    dictionary.add("java");
    dictionary.add("javascript");
    dictionary.add("internet");
    dictionary.add("foo");
    dictionary.remove("foo");

    while (!std::cin.fail())
    {
        system("clear");
        //system("cls");
        std::string query;
        std::cout << "Type in your query:\n";
        std::cin >> query;
        std::cout << "\nCandidates:\n";
        for (auto word : dictionary.candidates(query))
        {
            std::cout << word << std::endl;
        }
        std::cin.ignore();
        std::cout << "\nPress enter to continue...\n";
        std::cin.get();
    }
}
