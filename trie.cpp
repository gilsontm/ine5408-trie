#include <cstdint>
#include <stdexcept>  // C++ Exceptions


namespace structures {

typedef struct data_s {
    unsigned long position,
    unsigned long length
} data_t;


class Trie {
 public:
    Trie();

    ~Trie();

    void insert();

    data_t find(char* word);

 private:
    class Node {
     public:
        Node(const char letter):
            letter_{letter}
        {}

        void position(unsigned long position){
            position_{position}
        }

        void length(unsigned long length) {
            length_ = length;
        }

        Node* children() {
            return children_;
        }

        unsigned long position() {
            return position_;
        }

        unsigned long length() {
            return length_;
        }

     private:
        char letter_;
        Node* children_[26];
        unsigned long position_;
        unsigned long length_;
    }


}

}