#include <iostream>
#include <fstream>
#include "./trie.cpp"

using namespace std;
using namespace structures;

bool validateWord(string word) {
    for (char c : word) {
        if (c < 97 || c > 122) {
            cout << word << endl;
            return false;
        }
    }
    return true;
}

Trie* buildTrie(string filename) {
    ifstream file;
    file.open(filename);

    string line;
    string stream = "";
    string word = "";
    long begin = -1;
    unsigned long current = 0;

    Trie* trie = new Trie();

    while (getline(file, line)) {
        for (char c : line) {
            if (c == '[') {
                if (begin >= 0) {
                    if (validateWord(word))
                        trie->insert(word.c_str(), begin, current - begin - 1);
                }
                begin = current;
                stream = "";
            } else if (c == ']') {
                word = stream;
            } else {
                stream += c;
            }
            current++;
        }
        current++;
    }
    if (validateWord(word))
        trie->insert(word.c_str(), begin, current - begin - 1);
    file.close();
    return trie;
}

int main() {
    string filename;
    string word;
    Data data;

    cin >> filename;  // entrada

    Trie* trie = buildTrie(filename);
    
    while (1) {  // leitura das palavras ate' encontrar "0"
        cin >> word;

        if (word.compare("0") == 0) {
            break;
        }

        data = trie->find(word.c_str());

        if (!data.found)
            cout << "is not prefix" << endl;
        else if (data.length == 0) 
            cout << "is prefix" << endl;
        else
            cout << data.position << " " << data.length << endl;
    }
    return 0;
}
