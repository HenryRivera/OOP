//  Created by Henry Rivera on 4/19/19.
//  File Name: rec11
//  Description: Linked lists basics
//  Copyright © 2019 Henry Rivera. All rights reserved

#include <iostream>
#include <vector>
using namespace std;

// Node to be used a part of linked list
struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};



void listDisplay(Node* hp){
    Node* p = hp;
    while (p != nullptr){
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}



// listInsertHead: adds a data item to the beginning of a [possibly empty] list
void listInsertHead(Node*& headPtr, int entry) {
    headPtr = new Node(entry, headPtr);
}



// listClear: frees up all the nodes in a list
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

// listBuild: constructs a list from a vector of data items. Note that
// you can use a curly-braced sequence.
// This may be useful for setting up test cases. Feel free to use it
// or not as you like.
// Example of using would be:
//    Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listInsertHead(result, vals[index - 1]);
    }
    return result;
}



void splice(Node* lst, Node* ind){
    Node* after = ind->next;
    Node* lstLast = lst;
    while (lstLast->next){
        lstLast = lstLast->next;
    }
    ind->next = lst;
    lstLast->next = after;
}



Node* isSubList(Node* search, Node* lookingIn){
    while (lookingIn){
        Node* p1 = lookingIn;
        Node* p2 = search;
        Node* ind = nullptr;
        while (p1 && p2 && p1->data == p2->data) {
            if (ind == nullptr){ind = p1;}
            p1 = p1->next;
            p2 = p2->next;
        }
        
        if (!p2) {
            listDisplay(ind);
            return ind;
            
        }
        if (!p1) {
            cout << "Failed to match" << endl;
            return nullptr;
        }
        lookingIn = lookingIn->next;
    }
    cout << "Failed to match" << endl;
    return nullptr;
}



int main() {
    Node* L1 = listBuild({5, 7, 9, 1});
    Node* L2 = listBuild({6, 3, 2});
    
    cout << "Part One:" << endl;
    cout << "L1: ";
    listDisplay(L1);
    cout << "L2: ";
    listDisplay(L2);
    
    cout << "Splicing L2 at target in L1" << endl;
    splice(L2, L1->next);
    
    cout << "L1: ";
    listDisplay(L1);
    cout << "L2: ";
    listDisplay(L2);
    
    cout << "=====================" << endl;
    cout << endl;
    cout << "Part Two: " << endl;
    cout << endl;
    
    Node* target = listBuild({ 1, 2, 3, 2, 3, 2, 4, 5, 6});
    Node* trial1 = listBuild({ 1 });
    Node* trial2 = listBuild({ 3, 9});
    Node* trial3 = listBuild({ 2, 3});
    Node* trial4 = listBuild({ 2, 4, 5, 6});
    Node* trial5 = listBuild({ 2, 3, 2, 4});
    Node* trial6 = listBuild({ 5, 6, 7 });
    Node* trial7 = listBuild({ 6 });
    
    
    cout << "Target: ";
    listDisplay(target);
    cout << endl;
    
    cout << "Attempt match: ";
    listDisplay(trial1);
    isSubList(trial1, target);
    cout << endl;
    
    cout << "Attempt match: ";
    listDisplay(trial2);
    isSubList(trial2, target);
    cout << endl;
    
    cout << "Attempt match: ";
    listDisplay(trial3);
    isSubList(trial3, target);
    cout << endl;
    
    cout << "Attempt match: ";
    listDisplay(trial4);
    isSubList(trial4, target);
    cout << endl;
    
    cout << "Attempt match: ";
    listDisplay(trial5);
    isSubList(trial5, target);
    cout << endl;
    
    cout << "Attempt match: ";
    listDisplay(trial6);
    isSubList(trial6, target);
    cout << endl;
    
    cout << "Attempt match: ";
    listDisplay(trial7);
    isSubList(trial7, target);
    cout << endl;
    
}
