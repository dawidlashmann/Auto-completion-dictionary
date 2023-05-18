# Auto-completion-dictionary

## About
This project works as a auto-completing dictionary based on given `query`.

A `database` (implemented as a .txt file) can be used to load words at the start of the programm. 
Note that the `database` is not crucial for the programm to work, as words can by added by hand and wiped as the programm finishes.
If no .txt file is provided, the code will behave as if no database file was intended for usage.

While keeping in mind that the given `database` of words can be very large in the real world, I choose `TrieNode` as the main datastructure.
The reason behind it is a fast search time, and a sufficiently efficient memory usage.

## Using the programm
The class `Trie` has 3 functions:
* `add` which adds the word to the dictionary. If a `database` was prior provided, the word will be added there at the exit.
* `remove` which removes the word form the dicionary. If a `database` was prior provided, the word will be removed from there at the exit.
* `candidates` which returs a `std::vector` of candidates which fit the provided `query`

The programm has a terminal gui, which lets you choose your action in an infinite loop. To save a modified database please make sure to exit the programm by typing 0 in the menu.


