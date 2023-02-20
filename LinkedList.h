//
// Created by Admin on 2/11/2023.
//

#ifndef TEMPLATED_LINKED_LIST_LINKEDLIST_H
#define TEMPLATED_LINKED_LIST_LINKEDLIST_H

//
// Created by Admin on 2/11/2023.
//




#include <iostream>
#include <vector>
template <typename T>
class LinkedList{
public:
    struct Node{
        T data;
        Node* next;
        Node* prev;

    };
    // behaviors
    void PrintForward() const;
    void PrintReverse() const;
    void PrintForwardRecursive(const Node* node) const;
    void PrintReverseRecursive(const Node* node) const;
    // accessors
    unsigned int NodeCount() const;
    void FindAll(std::vector<Node*>& outData, const T& value) const;
    const Node* Find(const T& data) const;
    Node* Find(const T& data);
    const Node* GetNode(unsigned  int index) const;
    Node* GetNode(unsigned  int index);
    Node* Head();
    const Node* Head() const;
    Node* Tail();
    const Node * Tail() const;
    // insertion
    void AddHead(const T& data);
    void AddTail(const T& data);
    void AddNodesHead(const T* data, unsigned int count);
    void AddNodesTail(const T* data, unsigned int count);
    void InsertAfter(Node* node, const T& data);
    void InsertBefore(Node* node, const T& data);
    void InsertAt(const T& data, unsigned int index);
    // removal
    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(const T&data);
    bool RemoveAt(unsigned int index);
    void Clear();
    // operators
    const T& operator[](unsigned int index) const;
    T& operator[](unsigned  int index);
    bool operator==(const LinkedList<T>& rhs) const;
    LinkedList<T>& operator=(const LinkedList<T>& rhs);
    // construction/destruction
    LinkedList();
    LinkedList(const LinkedList<T>& list);
    ~LinkedList();

private:
    Node* _head;
    Node* _tail;
    unsigned int node_count;

};

template <typename T>
LinkedList<T>::LinkedList() {
    _head = nullptr;
    _tail = nullptr;
    node_count = 0;
}

template <typename T>
void LinkedList<T>::Clear(){
    Node* currNode =_head;
    Node* tempNode = nullptr;
    while (currNode != nullptr){
        tempNode = currNode->next;
        delete currNode;
        currNode = tempNode;

    }
    _head = nullptr;
    _tail = nullptr;
    node_count = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list){

    node_count = 0;
    AddHead(list._head->data);
    Node* currNode =list._head->next;
    while (currNode != nullptr){
        AddTail(currNode->data);
        currNode = currNode->next;
    }
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> &rhs){
    Clear();
    node_count =0;
    AddHead(rhs._head->data);
    Node* currNode =rhs._head->next;
    while (currNode != nullptr){
        AddTail(currNode->data);
        currNode = currNode->next;
    }
    return *this;
}


template <typename T>
LinkedList<T>::~LinkedList(){
    Node* currNode = _head;
    Node* delNode = currNode;
    while (currNode !=nullptr){
        currNode = currNode->next;
        delete delNode;
        delNode = currNode;
    }

    node_count = 0;
}

template <typename T>
bool LinkedList<T>::RemoveHead() {
    if (_head != nullptr){
        Node* temp_head = _head;
        _head = _head->next;

        if (_head != nullptr){
            _head->prev = nullptr;}else{ _tail=nullptr;}
        delete temp_head;
        node_count --;
        return true;
    }
    else {return false;}
}


template <typename T>
bool LinkedList<T>::RemoveTail() {

    if (_tail != nullptr){
        Node* temp_tail = _tail;
        _tail = _tail->prev;

        if (_tail != nullptr){
            _tail->next= nullptr;}else{ _head=nullptr;}
        delete temp_tail;
        node_count --;
        return true;
    }
    else {return false;}
}

template <typename T>
unsigned int LinkedList<T>::Remove(const T &data)  {
    Node* currNode = _head;
    unsigned int removedNode = 0;
    Node* tempNode = nullptr;
    while (currNode != nullptr){
        if (currNode->data == data){
            tempNode = currNode->next;
            currNode->prev->next =currNode->next;
            currNode->next->prev = currNode->prev;
            delete currNode;
            currNode = tempNode;
            node_count--;
            removedNode++;
        }else{currNode=currNode->next;}


    }
    return removedNode;
}
template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
    Node* currNode = _head;
    unsigned int tempCounter = 0;

    while (currNode != nullptr){
        if (index == tempCounter){

            currNode->prev->next =currNode->next;
            currNode->next->prev = currNode->prev;
            delete currNode;
            node_count--;
            return true;
        }
        currNode = currNode->next;
        tempCounter++;
    }
    return false;

}
template<typename T>
void LinkedList<T>::PrintForwardRecursive(const Node *node) const {

    if (node == nullptr){
        //  std::cout << "Done with recursion"<<std::endl;
    }else{
        std::cout << node->data << std::endl;
        PrintForwardRecursive(node->next);
    }
}
template<typename T>
void LinkedList<T>::PrintReverseRecursive(const Node *node) const {
    if (node == nullptr){
        //  std::cout << "Done with recursion"<<std::endl;
    }else{
        std::cout << node->data << std::endl;
        PrintReverseRecursive(node->prev);
    }
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
    return _head;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
    return _head;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
    return _tail;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
    return _tail;
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T> &rhs) const {
    Node* currNode = _head;
    Node* compareNode = rhs._head;
    if (node_count != rhs.node_count){
        return false;
    }
    while (currNode != nullptr){
        if(currNode->data != compareNode->data){
            return false;
        }
        compareNode = compareNode->next;
        currNode = currNode->next;
    }
    return true;
}

template <typename T>
void LinkedList<T>::InsertBefore(Node *node, const T &data) {

    if (node->prev == nullptr){
        AddHead(data);
    }else{
        Node* temp = new Node();
        temp->data = data;
        temp->prev = node->prev;
        temp->next = node;
        node->prev->next = temp;
        node->prev = temp;
        node_count ++;
    }

}


template <typename T>
void LinkedList<T>::InsertAfter(Node *node, const T &data) {
    if (node->next == nullptr){
        AddTail(data);
    }else{
        Node* temp = new Node();
        temp->data = data;
        temp->next = node->next;
        temp->prev = node;
        node->next->prev = temp;
        node->next = temp;
        node_count ++;
    }

}


template <typename T>
void LinkedList<T>::InsertAt(const T &data, unsigned int index) {
    if (index>node_count){throw std::out_of_range("Index is out of range");}else if (index == node_count){
        AddTail(data);
    }else{
        Node* currNode = _head;
        unsigned int temp_count = 0;
        while (currNode != nullptr){
            if (index== temp_count){
                InsertBefore(currNode, data);
                break;
            }

            currNode = currNode->next;
            temp_count ++;
        }

    }
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned  int index){
    if (index>=node_count){throw std::out_of_range("Index is out of range");}else{
        Node* currNode = _head;
        unsigned int temp_count= 0;
        while (currNode != nullptr){
            if (index == temp_count){
                return currNode;
            }
            currNode = currNode->next;
            temp_count ++;
        }
    }
}


template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
    if (index>=node_count){throw std::out_of_range("Index is out of range");}else{
        Node* currNode = _head;
        unsigned int temp_count= 0;
        while (currNode != nullptr){
            if (index == temp_count){
//                T* ptr = currNode->data;
//                std::cout << currNode->data << std::endl;
                return currNode;
//                break;
            }
            currNode = currNode->next;
            temp_count ++;
        }

    }
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {
    if (index>=node_count){throw std::out_of_range("Index is out of range");}else{
        Node* currNode = _head;
        unsigned int temp_count= 0;
        while (currNode != nullptr){
            if (index == temp_count){
//                T* ptr = currNode->data;
//                std::cout << currNode->data << std::endl;
                return currNode->data;
//                break;
            }
            currNode = currNode->next;
            temp_count ++;
        }

    }
}
template <typename T>
const  T &LinkedList<T>::operator[](unsigned int index) const  {
    if (index>=node_count){throw std::out_of_range("Index is out of range");}else{
        Node* currNode = _head;
        unsigned int temp_count= 0;
        while (currNode != nullptr){
            if (index == temp_count){
//                T* ptr = currNode->data;
//                std::cout << currNode->data << std::endl;
                return currNode->data;
//                break;
            }
            currNode = currNode->next;
            temp_count ++;
        }

    }
}
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T &data) const {
    Node* currNode = _head;
    while (currNode != nullptr){
        if (currNode->data == data){
            return currNode;
        }
        currNode = currNode->next;
    }
    return nullptr;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T &data) {
    Node* currNode = _head;
    while (currNode != nullptr){
        if (currNode->data == data){
            return currNode;
        }
        currNode = currNode->next;
    }
    return nullptr;
}

template <typename T>
void LinkedList<T>::FindAll(std::vector<Node *> &outData, const T &value) const {
    Node* currNode = _head;
    while (currNode != nullptr){
        if (currNode->data == value){
            outData.push_back(currNode);

        }
        currNode = currNode->next;
    }

}


template <typename T>
void LinkedList<T>::AddHead(const T &data) {
    Node* temp = new Node();
    temp->data = data;
    temp->prev = nullptr;
    temp->next = nullptr;
    if (node_count == 0){
        _head = temp;
        _tail = temp;

    }else{
        _head->prev = temp;
        temp->next = _head;
        if (node_count==1){
            _tail->prev = temp;
        }
        _head = temp;

    }
    node_count ++;

}

template <typename T>
void LinkedList<T>::AddTail(const T &data) {
    Node* temp = new Node();
    temp->data = data;
    temp->prev = nullptr;
    temp->next = nullptr;
    if (node_count==0){
        _head = temp;
        _tail = temp;
    }else{
        _tail->next = temp;
        temp->prev = _tail;
        if (node_count==1){
            _head->next = temp;
        }
        _tail = temp;
    }
    node_count++;

}

template <typename T>
void LinkedList<T>::AddNodesHead(const T *data, unsigned int count) {

    for (unsigned int i = count-1; count>=0; i--){
        AddHead(data[i]);
        if (i==0){ break;}
    }

}

template <typename T>
void LinkedList<T>::AddNodesTail(const T *data, unsigned int count) {
    for (unsigned int i = 0; i<count; i++){
        AddTail(data[i]);
    }
}

template <typename T>
unsigned int LinkedList<T>::NodeCount() const {
    return node_count;
}

template <typename T>
void LinkedList<T>::PrintForward() const {
    Node* currNode = _head;
    while (currNode != nullptr){
        std::cout << currNode->data << std::endl;
        currNode = currNode->next;
    }
}

template <typename T>
void LinkedList<T>::PrintReverse() const {
    Node* currNode = _tail;
    while (currNode != nullptr){
        std::cout << currNode->data << std::endl;
        currNode = currNode->prev;
    }
}

#endif //TEMPLATED_LINKED_LIST_LINKEDLIST_H
