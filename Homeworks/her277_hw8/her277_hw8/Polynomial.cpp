//  Created by Henry Rivera on 4/28/19.
//  File Name: Polynomial.cpp
//  Description: Polynomial.cpp implementation
//  Copyright © 2019 Henry Rivera. All rights reserved

#include "Polynomial.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;



namespace Poly {
    struct Node {
        Node(int data = 0, Node* next = nullptr): data(data), next(next){}
        int data;
        Node* next;
    };
    
    
    // listClear: frees up all the nodes in a list
    void listClear(Node*& headPtr){
        while (headPtr){
            Node* next = headPtr->next;
            delete headPtr;
            headPtr = next;
        }
    }
    
    
    
    Node* listFindTail(Node* hp){
        if (hp == nullptr) return nullptr;
        Node* p = hp;
        while (p->next != nullptr){
            p = p->next;
        }
        return p;
    }
    
    
    
    void listInsertTail(Node*& hp, int data){
        if (hp == nullptr){
            hp = new Node(data);
        }
        else {
            Node* tail = listFindTail(hp);
            tail->next = new Node(data);
        }
    }
    
    
    
    Node* listDup(Node* p){
        if (p->next == nullptr){
            return nullptr;
        }
        return new Node(p->data, listDup(p->next));
    }
    
    
    
    void display(ostream& os, const Node* hp, int deg){
        if (hp == nullptr) {
            return;
        }
        deg++;
        display(os, hp->next, deg);
        
        if (deg == 0 && hp->data != 0){
            os << hp->data;
        }
        else if (deg == 1) {
            if (hp->data <0 ) {
                os << hp->data << "x + ";
            }
            else {
                os << "x + ";
            }
            
        }
        else if (hp->data == 1) {
            os << hp->data << "x^" << deg <<" + ";
        }
        else if (hp->data != 0){
            os << hp->data << "x^" << deg <<" + ";
            
        }
        deg--;
    }
    
    
    
    ostream& operator<<(ostream& os, const Polynomial& rhs){
        if (rhs.coeffs == nullptr){
            os << "0";
            return os;
        }
        int tmp = -1;
        display(os, rhs.coeffs, tmp);
        return os;
    }
    
    
    
    bool operator==(const Polynomial& lhs, const Polynomial& rhs){
        if (lhs.degree == rhs.degree){
            Node* p = lhs.coeffs;
            Node* rhsP = rhs.coeffs;
            
            for (int i = 0; i <= lhs.degree; i++){
                if (p->data != rhsP->data){
                    return false;
                }
                p = p->next;
                rhsP = rhsP->next;
            }
        }
        else{
            return false;
        }
        return true;
    }
    
    
    
    bool operator!=(const Polynomial& lhs, const Polynomial& rhs){
        return !(lhs == rhs);
    }
    
    
    
    Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs){
        Polynomial res = lhs;
        return res += rhs;
    }
    
    
    
    Polynomial::Polynomial(const vector <int>& vals)
    : coeffs(nullptr), degree(vals.size() - 1){
        
        for (size_t ind = vals.size(); ind > 0; --ind){
            listInsertTail(coeffs, vals[ind - 1]);
        }
    }
    
    
    
    Polynomial::Polynomial(const Polynomial& rhs){
        degree = rhs.degree;
        coeffs = listDup(rhs.coeffs);
    }
    
    
    
    Polynomial::Polynomial() : coeffs(nullptr), degree(0){}
    
    
    
    Polynomial& Polynomial::operator+=(const Polynomial& rhs){
        Node* p = coeffs;
        Node* rhsP = rhs.coeffs;
        
        for (int i = 0; i <= rhs.degree; i++){
            if (i <= degree){
                p->data += rhsP->data;
            }
            if (p->next == nullptr && rhsP->next != nullptr){
                p->next = new Node(rhsP ->next->data);
            }
            p = p->next;
            rhsP = rhsP->next;
        }
        if (degree < rhs.degree){
            degree = rhs.degree;
        }
        return *this;
    }
    
    
    
    Polynomial& Polynomial::operator=(const Polynomial& rhs){
        if (this != &rhs){
            degree = rhs.degree;
            coeffs = new Node(rhs.coeffs->data);
            
            Node* p = coeffs;
            Node* rhsP = rhs.coeffs->next;
            
            for (int i = 1; i <= degree; i ++){
                p->next = new Node(rhsP->data);
                p = p->next;
                rhsP = rhsP->next;
            }
        }
        return *this;
    }
    
    
    
    int Polynomial::raise(int num, int power) const{
        int result = 1;
        for(int i = 0; i < power; ++i)
        {
            result *= num;
        }
        return result;
    }
    
    
    
    int Polynomial::evaluate(int x) const{
        int total = 0;
        Node* p = coeffs;
        
        for (int i = 0; i <= degree; i++){
            total += raise(x, i) * (p->data);
            p = p->next;
        }
        
        return total;
    }
    
    
    
    Polynomial::~Polynomial(){
        listClear(coeffs);
    }
}
