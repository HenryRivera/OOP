//  Created by Henry Rivera on 4/26/19.
//  File Name: rec12.cpp
//  Description: Doubly linked list class implementation
//  Copyright © 2019 Henry Rivera. All rights reserved

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
    friend ostream& operator<<(ostream& os, const List& rhs){
        Node* p = rhs.hp->next;
        while (p != rhs.tp){
            os << p->data << ' ';
            p = p->next;
        }
        return os;
    }
    struct Node {
        Node(int data = 0, Node* next = nullptr, Node* prior = nullptr)
        : data(data), next(next), prior(prior){}
        int data;
        Node* next;
        Node* prior;
    };
public:
    List() : theSize(0){
        hp = new Node();
        tp = new Node(0, nullptr, hp);
        hp->next = tp;
        hp->prior = nullptr;
    }
    
    size_t size() const{
        return theSize;
    }
    
    const int front() const{
        return hp->next->data;
    }
    
    
    const int back() const{
        return tp->prior->data;
    }
    
    
    
    int& front(){
        return hp->next->data;
    }
    
    
    int& back(){
        return tp->prior->data;
    }
    
    
    
    void push_back(int data){
        Node* someData = new Node(data);
        if (theSize == 0){
            someData->prior = hp;
            someData->next = tp;
            hp->next = someData;
            tp->prior = someData;
        }
        else{
            Node* p = hp;
            while (p->next != tp){
                p = p->next;
            }
            p->next = someData;
            someData->prior = p;
            someData->next = tp;
            tp->prior = someData;
        }
        ++theSize;
    }
    
    
    
    void pop_back(){
        if (theSize == 0) { return; }
        Node* p = tp->prior;
        Node* newLast = tp->prior->prior;
        newLast->next = tp;
        tp->prior = newLast;
        delete p;
        
        --theSize;
    }
    
    
    
    void push_front(int data){
        Node* someData = new Node(data);
        if (theSize == 0){
            someData->prior = hp;
            someData->next = tp;
            hp->next = someData;
            tp->prior = someData;
        }
        else{
            Node* newSecond = hp->next;
            hp->next = someData;
            someData->prior = hp;
            someData->next = newSecond;
            newSecond->prior = someData;
        }
        ++theSize;
    }
    
    
    
    void pop_front(){
        if (theSize == 0) { return; }
        Node* p = hp->next;
        Node* newFirst = p->next;
        hp->next = newFirst;
        newFirst->prior = hp;
        delete p;
        
        --theSize;
    }
    
    
    
    void clear(){
        while (theSize != 0){
            pop_back();
        }
    }
    
    
    
    int operator[](size_t index) const {
        if (index > theSize){
            cerr << "Index not in list" << endl;
            exit(1);
        }
        Node* p = hp->next;
        for (size_t i = 0; i <= index; ++i){
            if (i == index){
                return p->data;
            }
            p = p->next;
        }
        cerr << "Index not in list" << endl;
        exit(1);
    }
    
    
    
    int& operator[](size_t index) {
        if (index > theSize){
            cerr << "Index not in list" << endl;
            exit(1);
        }
        Node* p = hp->next;
        for (size_t i = 0; i <= index; ++i){
            if (i == index){
                return p->data;
            }
            p = p->next;
        }
        cerr << "Index not in list" << endl;
        exit(1);
    }
    
    class Iterator{
        friend List;
        friend bool operator!=(const Iterator& lhs, const Iterator& rhs){
            return lhs.curr != rhs.curr;
        }
    public:
        Iterator(Node* pointer) : curr(pointer) {}
        
        Iterator& operator++(){
            curr = curr->next;
            return *this;
        }
        int& operator*(){
            return curr->data;
        }
    private:
        Node* curr;
    };
    
    
    
    Iterator begin() { return Iterator(hp->next); }
    Iterator end() { return Iterator(tp); }
    
    
    Iterator insert(Iterator ind, int data){
        Node* p = new Node(data);
        Node* oldPrev = ind.curr->prior;
        oldPrev->next = p;
        p->prior = oldPrev;
        p->next = ind.curr;
        ind.curr->prior = p;
        ++theSize;
        return Iterator(p);
    }
    
    
    
    Iterator erase(Iterator ind) {
        Node* del = ind.curr;
        Node* res = ind.curr->next;
        res->prior = del->prior;
        del->prior->next = res;
        delete del;
        theSize--;
        return Iterator(res);
        
    }
private:
    size_t theSize;
    Node* hp;
    Node* tp;
};

// Task 1
void printListInfo(const List& myList) {
    cout << "size: " << myList.size()
    << ", front: " << myList.front()
    << ", back(): " << myList.back()
    << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List& theList){
//     theList.front() = 17;
//     theList.back() = 42;
// }

void changeFrontAndBack(List& theList){
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}

int main() {
    
    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    
    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";
    
    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";
    
    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";
    
    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";
    
    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
    << "the data in the third item in the list\n"
    << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);
    
    
    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::Iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";
    
    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
    << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";
    
    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";
}
