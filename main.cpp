#include <iostream>
#include <fstream>
#include "./trie.cpp"

using namespace std;
using namespace structures;


//! Namespace que engloba as funções do trabalho.
/*!
    O namespace functions engloba as funções buildTrie e validateWord,
    utilizadas no trabalho.
*/
namespace functions {
    //! Função que valida uma palavra encontrada.
    /*!
        \param word uma string para ser verificada.
        \return um boolean: true caso a palavra seja válida, false caso contrário.

        Para o caso de dicionários que não seguem o padrão de que
        palavras-chave, entre colchetes, devem conter somente caracteres 
        de 'a' a 'z' (97 a 122 em ASCII), se faz necessário validar
        que as palavras encontradas pela função buildTrie realmente
        cumpram essa especificação.
    */
    bool validateWord(string word) {
        for (char c : word) {
            if (c < 97 || c > 122) {
                // cout << word << endl;
                return false;
            }
        }
        return true;
    }

    //! Função que instancia e constroi uma árvore Trie a partir de um arquivo dicionário.
    /*!
        \param filename uma string que representa o caminho para o arquivo dicionário.
        \return um ponteiro para uma árvore Trie, construída a partir do dicionário especificado.

        Essa função percorre o arquivo dicionário, buscando encontrar palavras-chave
        entre colchetes, seguidas de suas definições, como em um dicionário.
        Ao encontrar uma palavra, ela é validada pela função validateWord, e caso
        seja válida, sua posição e o tamanho da sua linha são inseridos na Trie.
    */
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
}  // namespace functions


using namespace functions;

int main() {
    string filename;
    string word;
    Data data;

    cin >> filename;

    Trie* trie = buildTrie(filename);
    
    while (1) {
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
