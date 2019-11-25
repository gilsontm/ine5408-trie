#include <stdexcept>  // C++ Exceptions
#include <cstring>

namespace structures {

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

    class Trie {
     public:
        Trie() {
            root_ = nullptr;
        }

        ~Trie() {
            if (root_ != nullptr)
                delete root_;
        }

        void insert(const char* word, unsigned long position, unsigned long length) {
            if (strlen(word) == 0)
                throw std::runtime_error("invalid string");

            if (root_ == nullptr)
                root_ = new Node();
            root_->insert(word, position, length);
        }

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


