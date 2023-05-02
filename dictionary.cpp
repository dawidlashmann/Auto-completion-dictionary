#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <utility>

// Struct of each node
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
    // read from database file
    root = new TrieNode;
    database.open(filename, std::ios::in);
    if (database.is_open())
    {
        std::string temp;
        while (getline(database, temp))
        {
            this->add(temp);
        }
        database.close();
        // open file to write to
        database.open(filename, std::ios::out | std::ios::trunc);
    }
}

Trie::~Trie()
{
    // write to file
    if (database.is_open())
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
}

// add word to the TrieNode Tree
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

// remove word from TrieNode tree
void Trie::remove(const std::string &word)
{
    TrieNode *current_node = root;
    std::vector<std::pair<char, TrieNode *>> path;
    path.reserve(word.length());
    for (char letter : word)
    {
        if (current_node->children.find(letter) == current_node->children.end())
        {
            std::cout << "This word is not in the database\n";
            return;
        }
        path.emplace_back(std::pair<char, TrieNode *>{letter, current_node});
        current_node = current_node->children[letter];
    }
    current_node->is_end_of_word = false;
    for (int node = path.size() - 1; node >= 0; node--)
    {
        // if node in path does not have any childrens free allocated memory
        if (path.at(node).second->children[path.at(node).first]->children.empty() && !path.at(node).second->children[path.at(node).first]->is_end_of_word)
        {
            delete path.at(node).second->children[path.at(node).first];
            path.at(node).second->children.erase(path.at(node).first);
        }
        else
        {
            break;
        }
    }
}

// returns vector of candidate words
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

// traverse through the TrieNode Tree
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
    Trie dictionary("database.txt");

    bool loop = 1;
    while (loop)
    {
        system("clear");
        // system("cls");
        std::string query;
        int choice;
        std::cout << "Select action:\n"
                  << "1 - add word to database\n"
                  << "2 - remove word from database\n"
                  << "3 - Show query candidates\n\n"
                  << "0 - exit\n\n";
        std::cin >> choice;

        switch (choice)
        {
        case 0:
            loop = 0;
            break;
        case 1:
            std::cout << "Type in a word to add:\n";
            std::cin >> query;
            dictionary.add(query);
            break;
        case 2:
            std::cout << "Type in a word to remove:\n";
            std::cin >> query;
            dictionary.remove(query);
            break;
        case 3:
            std::cout << "Type in your query:\n";
            std::cin >> query;
            std::cout << "\nCandidates:\n";
            for (auto word : dictionary.candidates(query))
            {
                std::cout << word << std::endl;
            }
            break;
        }
        if (loop)
        {
            std::cout << "\nPress enter to continue\n";
            std::cin.ignore();
            std::cin.get();
        }
    }
}
