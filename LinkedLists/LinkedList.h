#pragma once
#pragma once
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

template <typename T>
class LinkedList {
public:
    struct Node {
        T data;
        Node* next;
        Node* previous;

        Node() {
            next = nullptr;
            previous = nullptr;
        }
        Node(T data) {
            next = nullptr;
            previous = nullptr;
            this->data = data;
        }
    };
    // Default constructor and Deconstructor
    LinkedList();
    ~LinkedList();
    LinkedList<T>& operator=(const LinkedList<T>& rhs);
    LinkedList(const LinkedList<T>& list);

    // Ways to add info to the container
    // Insertions
    void AddHead(const T& value);
    void AddTail(const T& data);
    void AddNodesHead(const T* data, unsigned int count);
    void AddNodesTail(const T* data, unsigned int count);

    void InsertAfter(Node* node, const T& data);
    void InsertBefore(Node* node, const T& data);
    void InsertAt(const T& data, unsigned int index);

    //Accessors
    unsigned int NodeCount() const;
    void FindAll(vector<Node*>& outData, const T& value) const;
    const Node* Find(const T& data) const;
    Node* Find(const T& da);
    const Node* GetNode(unsigned int index) const;
    Node* GetNode(unsigned int index);
    Node* Head();
    const Node* Head() const;
    Node* Tail();
    const Node* Tail() const;

    //Behaviors
    // Ways to see the data in the container
    void PrintForward() const;
    void PrintReverse() const;

    void PrintForwardRecursive(const Node* node) const;
    void PrintReverseRecursive(const Node* node) const;

    // Removal
    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(const T& data);
    bool RemoveAt(unsigned int index);
    void Clear();

    // Operators
    const T& operator[](unsigned int index) const;
    T& operator[](unsigned int index);
    bool operator==(const LinkedList<T>& rhs);


private:
    // Points to top element of the stack
    Node* head = nullptr;
    Node* tail = nullptr;
    int count = 0;
};

// Default Constructor
template <typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
    count = 0;
}
// Deconstructor
template <typename T>
LinkedList<T>::~LinkedList() {
    Clear();
}


// Creates new Node at the front of the list to store the passed in parameter
template<typename T>
void LinkedList<T>::AddHead(const T& value) {
    Node* currentNode = new Node();
    currentNode->data = value;
    currentNode->next = nullptr;
    currentNode->previous = nullptr;

    if (head == nullptr) {
        head = currentNode;
        tail = currentNode;
        head->next = nullptr;
        head->previous = nullptr;
    }
    else if (head != nullptr) {
        head->previous = currentNode;
        if (count == 1) {
            tail->previous = currentNode;
        }
        currentNode->next = head;
        head = currentNode;
    }
    count++;
}

// Creates a new Node at the end of the list to store the passed in parameter
template<typename T>
void LinkedList<T>::AddTail(const T& data) {
    Node* currentNode = new Node();
    currentNode->data = data;
    currentNode->next = nullptr;
    currentNode->previous = nullptr;

    if (tail == nullptr) {
        head = currentNode;
        tail = currentNode;
        head->next = nullptr;
        head->previous = nullptr;
    }
    else if (tail != nullptr) {
        tail->next = currentNode;
        if (count == 1) {
            head->next = currentNode;
        }
        currentNode->previous = tail;
        currentNode->next = nullptr;
        tail = currentNode;
    }
    count++;
}

// Given an array of values, insert a node for each of those at the beginning 
// of the list, maintaining the original order.
template<typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count) {
    for (int i = (int)count - 1; i >= 0; i--) {
        AddHead(data[i]);
    }
}

// Given an array of values, insert a node for each of those at the end 
// of the list, maintaining the original order.
template<typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count) {
    for (int i = 0; i < (int)count; i++) {
        AddTail(data[i]);
    }
}

//inser new node before indicated node
template<typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = node;
    newNode->previous = node->previous;

    node->previous->next = newNode;
    node->previous = newNode;
    count++;
}

//Goven a pointer to a node, create a new node to store the passed in
//value after indicated node
template<typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = node->next;

    node->next->previous = newNode;
    node->next = newNode;
}

//Inserts new Node to store first paramenterat index of locarion
template<typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {
    if (index > count) {
        throw out_of_range("Index is out of range");
    }
    else if (index == count) {
        Node* newNode = new Node();
        newNode->data = data;
        tail->next = newNode;
        newNode->previous = tail;
        newNode->next = nullptr;
        tail = newNode;


        count++;
    }
    else {
        Node* newNode = new Node();

        Node* selectNode = Head();
        newNode->data = data;

        int currentCount = 0;

        while (currentCount < index) {
            selectNode = selectNode->next;
            currentCount++;
        }
        newNode->previous = selectNode->previous;
        newNode->next = selectNode;

        if (selectNode->previous != nullptr) {
            selectNode->previous->next = newNode;
        }
        else {
            head = newNode;
        }

        selectNode->previous = newNode;
        count++;
    }

}

// How many things are stored in this list
template<typename T>
unsigned int LinkedList<T>::NodeCount()const {
    return count;
}

//Iterator through all the nodes and print out their values, one a time
template<typename T>
void LinkedList<T>::PrintForward()const {
    Node* currentNode = head;
    while (currentNode != nullptr) {
        cout << currentNode->data << endl;
        currentNode = currentNode->next;
    }
}

//Interate through the nodes and print backwards
template<typename T>
void LinkedList<T>::PrintReverse()const {
    Node* currentNode = tail;
    while (currentNode != nullptr) {
        cout << currentNode->data << endl;
        currentNode = currentNode->previous;
    }
}

//Returns the head pointer. Const and non-const versions
template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
    return head;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
    return head;
}

//Returns the tail pointer. Const and non-const versions
template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
    return tail;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail()const {
    return tail;
}

//Given an index, return a pointer to the node at that index. Throws an exception
//type out_of_range if the index is out of range. Const and non-const versions.
template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
    if (index >= count) {
        throw out_of_range("Index is out of range");
    }
    else {
        Node* currentNode = head;
        int indexCount = 0;
        while (indexCount != index) {
            currentNode = currentNode->next;
            indexCount++;
        }
    }
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index)const {
    if (index >= count) {
        throw out_of_range("Index is out of range");
    }
    else {
        Node* currentNode = head;
        int indexCount = 0;
        while (indexCount != index) {
            currentNode = currentNode->next;
            indexCount++;
        }
    }
}

//operator finding the FIRST node based on a value

//Overloaded subscript operator. Takes an index, and returns data from the index
//node. Throws out_of_range exception for an invalid index. Const and non const version
template<typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {
    if (index > count) {
        throw out_of_range("Incorrect Index");
    }

    int indexCount = 0;
    Node* currentNode = head;
    while (indexCount != index) {
        currentNode = currentNode->next;
        indexCount++;
    }

    return currentNode->data;
}

template<typename T>
T& LinkedList<T>::operator[](unsigned int index) {
    if (index > count) {
        throw out_of_range("Incorrect Index");
    }

    int indexCount = 0;
    Node* currentNode = head;
    while (indexCount != index) {
        currentNode = currentNode->next;
        indexCount++;
    }

    //currentNode = currentNode->data
    return currentNode->data;
}

template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) {
    Node* currentNode = head;
    Node* rhsCurrent = rhs.head;
    bool isEqual = true;

    if (rhs.count == count) {

        for (int i = 0; i < count; i++) {

            if (currentNode->data != rhsCurrent->data) {
                isEqual = false;
                break;
            }

            currentNode = currentNode->next;
            rhsCurrent = rhsCurrent->next;

        }
        return isEqual;
    }
    else if (rhs.count != count) {
        return false;
    }
}

//Find the FIRST node with a data value matching the passed in paramenter, 
//returning a pointer to that node. Returns nullptr if no matching node found
template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const {
    Node* currentNode = Head();
    bool match = false;
    while (currentNode->next != nullptr && !match) {

        if (currentNode->data == data) {
            match = true;
            return currentNode = currentNode->next;
        }
    }
    if (match) {
        return currentNode->previous;
    }
    else {
        return nullptr;
    }
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) {
    Node* currentNode = Head();
    bool match = false;
    while (currentNode->next != nullptr && !match) {

        if (currentNode->data == data) {
            match = true;
        }
        currentNode = currentNode->next;
    }
    if (match) {
        return currentNode->previous;
    }
    else {
        return nullptr;
    }
}

//Find ALL nodes based on a value
//Find allnodes which match the passed in parameter value and store a 
//pointer to that node in the passed in vector. Use a parameter liek this
//(passing a something in by reference, and storing data for later use) is called
//output parameter
template<typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const {
    Node* currentNode = head;
    for (int i = 0; i < count; i++) {
        if (currentNode->data == value) {
            outData.push_back(currentNode);
        }
        currentNode = currentNode->next;
    }
}

//Copy Constructor: sets "this" to a copy of the passed in LinkedList.
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
    head = nullptr;
    tail = nullptr;
    Node* currentNode = list.head;
    while (currentNode != nullptr) {
        AddTail(currentNode->data);
        currentNode = currentNode->next;
    }
}

// Copy assignment operator
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
    head = nullptr;
    tail = nullptr;
    Node* currentNode = rhs.head;
    //while(currentNode != nullptr){
    for (int i = 0; i < rhs.count; i++) {
        AddTail(currentNode->data);
        currentNode = currentNode->next;
    }
    return *this;
}


// Deletes All Nodes and Node count
template<typename T>
void LinkedList<T>::Clear() {
    Node* ptr = head;
    Node* currentPtr;

    while (ptr != nullptr) {
        currentPtr = ptr->next;
        delete ptr;
        ptr = currentPtr;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
}

// Removals

template<typename T>
bool LinkedList<T>::RemoveHead() {


    if (head == nullptr) {
        return false;
    }
    else if (head->next == nullptr) {
        Node* currentNode = head;
        delete currentNode;
        head = nullptr;
        tail = nullptr;
        count--;
        return true;
    }
    else {
        Node* currentNode = head;
        head = head->next;


        delete currentNode;
        count--;
        head->previous = nullptr;

        return true;
    }
}

template<typename T>
bool LinkedList<T>::RemoveTail() {


    if (head == nullptr) {
        return false;
    }
    else if (tail->previous == nullptr) {
        Node* currentNode = tail;
        delete currentNode;
        head = nullptr;
        tail = nullptr;
        count--;
        return true;
    }
    else {
        Node* currentNode = tail;
        tail = tail->previous;
        delete currentNode;
        count--;
        tail->next = nullptr;

        return true;
    }
}

template<typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {



    if (index == 0) {

        RemoveHead();
        return true;
    }
    else if (index >= count) {
        return false;
    }
    else if (index == count - 1) {
        RemoveTail();
        return true;
    }
    else {
        Node* currentNode = head;
        for (int i = 0; i < index; i++) {
            currentNode = currentNode->next;
        }
        currentNode->next->previous = currentNode->previous;
        currentNode->previous->next = currentNode->next;
        delete currentNode;
        count--;
        return true;
    }


    /*if(currentNode->next == nullptr){
      currentNode->previous->next = nullptr;
    }
    else if(currentNode->previous == nullptr){
      currentNode->next->previous =nullptr;
    }
    else{
      currentNode->previous->next = currentNode->next;
      currentNode->next->previous = currentNode->previous;
    }
    delete currentNode;
    count--;
    return true;
  }
  else{
    //return false;
  } */
}

template<typename T>
unsigned int LinkedList<T>::Remove(const T& data) {
    Node* currentNode = head;
    int numRemoved = 0;
    while (currentNode != nullptr) {
        if (currentNode->data == data) {
            if (currentNode->next == nullptr) {
                currentNode->previous->next = nullptr;
            }
            else if (currentNode->previous == nullptr) {
                currentNode->next->previous = nullptr;
            }

            else {
                currentNode->previous->next = currentNode->next;
                currentNode->next->previous = currentNode->previous;
            }

            Node* newNode = currentNode->next;
            delete currentNode;
            currentNode = newNode;
            numRemoved++;
        }
        else {
            currentNode = currentNode->next;
        }
    }

    count = count - numRemoved;
    return numRemoved;
}

// Recursion print Functions
template<typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {


    if (node != nullptr) {
        cout << node->data << endl;
        node = node->next;
        PrintForwardRecursive(node);
    }

}


template<typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const {
    if (node != nullptr) {
        cout << node->data << endl;
        node = node->previous;
        PrintReverseRecursive(node);
    }
}