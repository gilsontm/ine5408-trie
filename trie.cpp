#include <stdexcept>  // C++ Exceptions
#include <cstring>

//! Namespace que engloba as estruturas do trabalho.
/*!
    O namespace structures engloba a struct Data e a classe Trie.
 */
namespace structures {

    //! Struct que encapsula o retorno do método find da classe Trie.
    /*!
        Contém os campos position, length e found. O atributo position
        representa a posição da palavra no dicionário. Length representa
        o comprimento da linha em que a palavra se encontra, e found é
        um valor booleano que determina se a palavra foi encontrada na
        árvore ou não.
     */
    struct Data {
        Data() {
            position = length = 0;
            found = false;
        }

        Data(unsigned long position_, unsigned long length_, bool found_) {
            position = position_;
            length = length_;
            found = found_;
        }

        unsigned long position;
        unsigned long length;
        bool found;
    };


    //! Classe que implementa a árvore de prefixos "retrieval".
    /*!
        A árvore Trie é implementada de forma a cada nó possuir até
        26 filhos (um para cada letra do alfabeto). O nó raiz é usado
        como um nó sentinela, que apenas faz a ligação com os outros nós
        da árvore, e não representa nenhum caracter.
        Percorrer a árvore numa certa ordem de filhos (0 a 25) equivale
        a percorrer as letras ('a' a 'z') de uma palavra. Desse modo, é 
        possível indexar o final de palavras como os nós mais inferiores
        da árvore. Quando uma palavra é inserida na árvore, um caminho 
        de nós é criado para representar aquela palavra. No último nó
        desse caminho, são guardadas as informações acerca da posição
        e do tamanho da linha da palavra no dicionário.
    */
    class Trie {
     public:
        Trie() {
            root_ = nullptr;
        }

        ~Trie() {
            if (root_ != nullptr)
                delete root_;
        }


        //! Método que insere palavras na árvore.
        /*!
            \param word Uma sequência de caracteres que representa a palavra a ser inserida.
            \param position A posição da palavra no dicionário.
            \param length O tamanho da linha em que a palavra se encontra.

            Verifica se a palavra não é vazia. Se for, lança uma exceção;
            caso contrário, chama o método insert do nó raiz.
            O método find do nó navega pela árvore, criando filhos quando
            necessário, para que ao final se tenha um caminho de nós que 
            representa a palavra que foi inserida.
            Consiste em diminuir a palavra em um caracter a cada chamada, 
            e passar a palavra reduzida para um filho, que executa o
            mesmo processo até a palavra ter tamanho zero. Quando não há
            mais caracteres na palavra, significa que aquele é o último
            nó do caminho, e as informações de posição e comprimento devem
            ser armazenadas ali.
        */
        void insert(const char* word, unsigned long position, unsigned long length) {
            if (strlen(word) == 0)
                throw std::runtime_error("invalid string");

            if (root_ == nullptr)
                root_ = new Node();
            root_->insert(word, position, length);
        }


        //! Método que busca palavras na árvore.
        /*!
            Checa se o nó raiz existe, e se existir, chama o método find
            do nó raiz. Cada nó, por sua vez, chama o método find em um de
            seus filhos, reduzindo a palavra a cada chamada.
            Se a palavra chegar ao tamanho zero, o último nó do caminho 
            foi encontrado, e portanto a palavra foi encontrada na árvore.
            Nesse caso, retorna-se a posição e o comprimento armazenados
            naquele nó.
            Se não houverem filhos suficientes para continuar no caminho
            especificado pela palavra, então a palavra não está presente
            na árvore.
        */
        Data find(const char* word) {
            if (root_ == nullptr) 
                return Data();
            return root_->find(word);
        }

     private:
        class Node {
        public:
            Node() { 
                for (int i = 0; i < 26; i++) 
                    children_[i] = nullptr;
                position_ = 0u;
                length_ = 0u;
            }

            ~Node() {
                for (int i = 0; i < 26; i++)
                    if (children_[i] != nullptr)
                        delete children_[i];
            }

            void insert(const char* word, unsigned long position, unsigned long length) {
                if (strlen(word) == 0) {
                    position_ = position;
                    length_ = length;
                } else {
                    Node* child = children_[int(word[0]) - 97];
                    if (child == nullptr) {
                        child = new Node();
                        children_[int(word[0]) - 97] = child;
                    }
                    child->insert(word + 1, position, length);
                }
            }

            Data find(const char* word) {
                if (strlen(word) == 0)
                    return Data(position_, length_, true);

                Node* child = children_[int(word[0]) - 97];
                if (child != nullptr)
                    return child->find(word + 1);
                return Data();
            }

        private:
            unsigned long position_{0u};
            unsigned long length_{0u};
            Node* children_[26];
        };
        Node* root_;
    };
}  // namespace structures


