//  Created by Henry Rivera on 5/10/19.
//  File Name: rec14.cpp
//  Description: Lab on recursion
//  Copyright © 2019 Henry Rivera. All rights reserved

#include <iostream>
#include <string>
#include <vector>

using namespace std;


struct Node{
    Node(int data = 0, Node* next = nullptr): data(data), next(next){}
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



Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listInsertHead(result, vals[index - 1]);
    }
    return result;
}



struct TNode {
    TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
    : data(data), left(left), right(right) {}
    int data;
    TNode *left, *right;
};



// Write a recursive function to determine if a
// non-negative integer has an even number of ones
// in its binary representation. Return true
// if it does and false otherwise.
bool isEven(int n){
    // int count = 0;
    if (n == 0){
        return true;
    }
    else if (n == 1){
        return false;
    }
    else{
        bool tmp = isEven(n/2);
        if (n % 2 == 1){
            return !tmp;
        }
        else{
            return tmp;
        }
    }
}



// Write a recursive function to create and return
// a new list that is the sum of the values in the
// the two lists passed in. Do not assume that the
// two lists are the same length
Node* sumList(Node* lhs, Node* rhs) {
    if (lhs == nullptr && rhs == nullptr) {
        return nullptr;
    }
    else if (lhs==nullptr) {
        return new Node(rhs->data, sumList(lhs, rhs->next));
        
    }
    else if(rhs==nullptr){
        return new Node(lhs->data, sumList(lhs->next, rhs));
    }
    else {
        return new Node(lhs->data + rhs->data, sumList(lhs->next, rhs->next));
    }
}



// Write a recursive function to return the
// maximum of the values in a binary tree
int max(TNode* root){
    if (root == nullptr) {
        throw invalid_argument("Tree does not exist");
    }
    
    int right = root->data;
    int left = root->data;
    
    if (root->left == nullptr && root->right == nullptr) {
        return root->data;
    }
    
    if (root->right) {
        right = max(root->right);
    }
    
    if (root->left) {
        left = max(root->left);
    }
    
    if (left >= right && left >= root->data) {
        return left;
    }
    
    else if (left <= right && right >= root->data) {
        return right;
    }
    //(root->data >= left && root->data >= right)
    else{
        return root->data;
    }
}



// Write a recursive function called palindrome
bool palindrome(char* word, int len){
    if (len <= 1){
        return true;
    }
    else{
        if (*word == word[len-1]){
            bool tmp = palindrome(word+1, len-2);
            return tmp == true;
        }
        else{
            return false;
        }
    }
}



// Implement a recursive function to solve the towers of hanoi problem
int towers(int n, char start, char target, char spare){
    if (n == 0){
        return 0;
    }
    int res = towers(n-1, start, spare, target);
    return 1 + 2*res;
}



// m(5): a m(2) b m(2) c = a acbccc b acbccc c
// m(2): a m(1) b m(1) c = acbccc
// m(1): c
void mystery(int n) {
    if (n > 1) {
        cout << 'a';
        mystery(n/2);
        cout << 'b';
        mystery(n/2);
    }
    cout << 'c';
}



int main(){
    cout << "#1) Testing isEven" << endl;
    bool tmp = isEven(13);
    if (tmp == true){
        cout << "true" << endl;
    }
    else{
        cout << "false" << endl;
    }
    cout << "=====================" << endl;
    cout << endl;
    
    
    
    cout << "#2) Testing sumList" << endl;
    Node* lst1 = listBuild({1, 2, 3, 4, 5});
    Node* lst2 = listBuild({2, 2, 2, 2, 2});
    
    Node* tot = sumList(lst1, lst2);
    listDisplay(tot);
    cout << "=====================" << endl;
    cout << endl;
    
    
    
    cout << "#3) Testing finding max in a tree" << endl;
    TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
    try {
        cout << max(&f)<< endl;
    }
    catch (exception& excpt) {
        cout << excpt.what();
    }
    cout << "=====================" << endl;
    cout << endl;

    
    
    cout << "#4) Testing palindrome" << endl;
    char s[] = "racecar";
    if (palindrome(s, 7)){
        cout << "Yes!\n";
    }
    cout << "=====================" << endl;
    cout << endl;
    
    
    
    cout << "#5) Testing towers" << endl;
    int total = towers(1, 'a', 'b', 'c'); //1
    cout << "towers(1, 'a', 'b', 'c'): " << total << endl;
    
    int total2 = towers(2, 'a', 'b', 'c'); //3
    cout << "towers(2, 'a', 'b', 'c'): " << total2 << endl;
    
    int total3 = towers(3, 'a', 'b', 'c'); //7
    cout << "towers(3, 'a', 'b', 'c'): " << total3 << endl;
    
    int total4 = towers(4, 'a', 'b', 'c'); //15
    cout << "towers(4, 'a', 'b', 'c'): " << total4 << endl;
    
    int total5 = towers(5, 'a', 'b', 'c'); //31
    cout << "towers(5, 'a', 'b', 'c'): " << total5 << endl;
    
    int total6 = towers(6, 'a', 'b', 'c'); //63
    cout << "towers(6, 'a', 'b', 'c'): " << total6 << endl;
    
    int total7 = towers(7, 'a', 'b', 'c'); //127
    cout << "towers(7, 'a', 'b', 'c'): " << total7 << endl;
    
    int total8 = towers(8, 'a', 'b', 'c'); //255
    cout << "towers(8, 'a', 'b', 'c'): " << total8 << endl;
    
    int total9 = towers(9, 'a', 'b', 'c'); //511
    cout << "towers(9, 'a', 'b', 'c'): " << total9 << endl;
    
    int total10 = towers(10, 'a', 'b', 'c'); //1023
    cout << "towers(10, 'a', 'b', 'c'): " << total10 << endl;
    cout << "=====================" << endl;
    cout << endl;
    
    
    
    cout << "#6) Testing mystery" << endl;
    mystery(5);
    cout << endl;
    cout << "=====================" << endl;
    cout << endl;
}
