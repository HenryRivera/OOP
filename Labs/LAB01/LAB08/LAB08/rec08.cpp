//  Created by Henry Rivera on 3/13/19.
//  File Name: rec08
//  Description: Lab on operator overloading
//  Copyright © 2019 Henry Rivera. All rights reserved

#include <iostream>
#include <string>
using namespace std;

/*
// If time allows use  separate compilation, otherwise just define the class below
#include "Rational.h"

// If time allows after implementing separate compilation, then wrap the class in a namespace.
using namespace CS2124;
 */

int gCD(int x, int y);

class Rational{
    friend ostream& operator<<(ostream& os, const Rational& rhs){
        os << rhs.numerator << '/';
        os << rhs.denominator;
        return os;
    }
    
    friend istream& operator>>(istream& is, Rational& rhs){
        char slash;
        is >> rhs.numerator >> slash >> rhs.denominator;
        rhs.reduce();
        return is;
    }
    
    friend bool operator==(const Rational& lhs, const Rational& rhs);
    
    friend bool operator<(const Rational& lhs, const Rational& rhs);
public:
    Rational(int a = 0, int b = 1) : numerator(a), denominator(b) {
        reduce();
    }
    
    
    
    //method
    Rational& operator+=(const Rational& rhs){
        if (denominator == rhs.denominator){
            numerator += rhs.numerator;
            this->reduce();
            return *this;
        }
        int aGCD = gCD(denominator, rhs.denominator);
        
        numerator = numerator * rhs.denominator + rhs.numerator * denominator;
        denominator = (denominator * rhs.denominator) / aGCD;
        this->reduce();
        return *this;
    }
    
    
    
    //member
    Rational& operator++(){
        numerator += denominator;
        this->reduce();
        return *this;
    }
    
    
    
    //member
    Rational operator++(int){
        Rational result(*this);
        numerator += denominator;
        result.reduce();
        return result;
    }
    
    
    
    void reduce(){
        // Finding gcd of both terms
        int commonDiv = gCD(numerator, denominator);
        
        // Dividing them by common factor
        numerator = numerator / commonDiv;
        denominator = denominator / commonDiv;
        
        if (denominator<0){
            numerator*=-1;
            denominator*=-1;
        }
    }
    
    
    
    explicit operator bool() const{
        return numerator != 0;
    }
private:
    int numerator;
    int denominator;
};



//non-member function
bool operator==(const Rational& lhs, const Rational& rhs){
    return (lhs.numerator == rhs.numerator)
    && (lhs.denominator / rhs.denominator);
}



//non-member function
bool operator!=(const Rational& lhs, const Rational& rhs){
    return !(lhs == rhs);
}



//non-member function
bool operator<(const Rational& lhs, const Rational& rhs){
    return (lhs.numerator / lhs.denominator)
    < (rhs.numerator / rhs.denominator);
}



//non-member function and non-friend
bool operator<=(const Rational& lhs, const Rational& rhs){
    return !(lhs == rhs) || !(lhs < rhs);
}



//non-member function and non-friend
bool operator>(const Rational& lhs, const Rational& rhs){
    return !(lhs < rhs);
}



//non-member function and non-friend
bool operator>=(const Rational& lhs, const Rational& rhs){
    return !(lhs == rhs) || !(lhs > rhs);;
}



//non-member function
Rational operator+(const Rational& lhs, const Rational& rhs){
    //Complex result;
    //result += lhs;
    //Complex result(lhs);
    Rational result = lhs;
    result += rhs;
    result.reduce();
    return result;
}


//non-member non-friend function
Rational& operator--(Rational& rhs){
    rhs += -1;
    rhs.reduce();
    return rhs;
}



//non-member non-friend function
Rational operator--(Rational& rhs, int){
    Rational rat(rhs);
    rhs += -1;
    rhs.reduce();
    return rat;
}



/*member
Rational& operator++(){
    numerator += denominator;
    this->reduce();
    return *this;
}



//member
Rational operator++(int){
    Rational result(*this);
    numerator += denominator;
    result.reduce();
    return result;
}
*/


int gCD(int x, int y){
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}



int main() {
    Rational twoThirds(2,3);
    cout << twoThirds << endl;
    
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;
    
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;
    
    // Implement as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;
    
    // How does this manage to work?
    // It does NOT require writing another == operator.
    cout << "1 == one: " << boolalpha << (1 == one) << endl;
    
    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;
    
    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;
    
    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;
    
    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;
    
    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing?
    //cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;
    
    
    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    }
    
    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    } 
}

