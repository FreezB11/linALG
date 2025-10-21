/// @file: linkedlist.h
/// this will implement the linked list 
/// so that we can store the matrix
#include <cstddef>

template<typename T>
struct node{
    T* data;
    node* nxt;

    node(size_t n){
        data = new T[n];
    }

    ~node(){
        delete[] data;
    }
};

template<typename T>
class linkedlist{
private:
    // node<T>* head;
    size_t cols;
public:
    node<T>* head;
    linkedlist(){
        head = nullptr;
    };
    linkedlist(size_t rows, size_t cols) : head(nullptr), cols(cols){
        node<T>* prev = nullptr;
        for(size_t i = 0; i < rows; i++){
            node<T>* curr = new node<T>(cols);
            if(!head)
                head = curr;
            else
                prev->nxt = curr;
            prev = curr;
        }
    }

    ~linkedlist(){
        node<T>* curr = head;
        while(curr){
            node<T>* temp = curr->nxt;
            delete curr;
            curr = temp;
        }
    }
};