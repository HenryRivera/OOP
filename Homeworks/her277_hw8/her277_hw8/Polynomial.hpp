//  Created by Henry Rivera on 4/28/19.
//  File Name: Polynomial.hpp
//  Description: Polynomial header implementation
//  Copyright © 2019 Henry Rivera. All rights reserved

#ifndef Polynomial_hpp
#define Polynomial_hpp

#include <iostream>
#include <string>
#include <vector>

namespace Poly {
    struct Node;
    
    
    
    // listClear: frees up all the nodes in a list
    void listClear(Node*& headPtr);
    
    
    
    Node* listFindTail(Node* hp);
    
    
    
    void listInsertTail(Node*& hp, int data);
    
    
    
    Node* listDup(Node* p);
    
    
    
    void display(std::ostream& os, const Node* hp, int deg);
    
    
    
    class Polynomial {
        friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);
        
        
        
        friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
        
        
        
        friend bool operator!=(const Polynomial& lhs, const Polynomial& rhs);
        
        
        
        friend Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);
    public:
        Polynomial(const std::vector <int>& vals);
        
        
        
        Polynomial(const Polynomial& rhs);
        
        
        
        Polynomial();
        
        
        
        Polynomial& operator+=(const Polynomial& rhs);
        
        
        
        Polynomial& operator=(const Polynomial& rhs);
        
        
        
        int raise(int num, int power) const;
        
        
        
        int evaluate(int x) const;
        
        
        
        ~Polynomial();
    private:
        int degree;
        Node* coeffs;
        
    };
}

#endif /* Polynomial_hpp */
