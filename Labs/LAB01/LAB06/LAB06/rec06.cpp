//  Created by Henry Rivera on 3/8/19.
//  File Name: rec06
//  Description:
//  Copyright © 2019 Henry Rivera. All rights reserved

#include <string>
#include <iostream>
using namespace std;

class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }
public:
    Position(const string& aTitle, double aSalary)
    : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
private:
    string title;
    double salary;
}; // class Position

class Entry {
    friend ostream& operator<<(ostream& os, const Entry& rhs) {
        os << rhs.name << ' ' << rhs.room
        << ' ' << rhs.phone << ", " << *rhs.pos;
        return os;
    }
public:
    Entry(const string& name, unsigned room, unsigned phone, Position& position)
    : name(name), room(room), phone(phone), pos(&position) {
    }
    const string& getName() const { return name; }
    unsigned getPhone() const { return phone; }
private:
    string name;
    unsigned room;
    unsigned phone;
    Position* pos;
}; // class Entry

class Directory {
    // Overload output operator
    friend ostream& operator<<(ostream& os, const Directory& rhs) {
        for (size_t i = 0; i < rhs.size; ++i){
            os << *rhs.entries[i] << endl;
        }
        return os;
    }
public:
    Directory():entries(new Entry*[1]), size(0), capacity(1){}
    
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (capacity == 0){
            entries = new Entry*[1];
            capacity = 1;
        }
        else if (size == capacity){
            Entry** oldArray = entries;
            entries = new Entry*[capacity*2];
            for (size_t i = 0; i < size; ++i){
                entries[i] = oldArray[i];
            }
            delete [] oldArray;
            capacity *= 2;
            
        }
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add
    
    //Copy constructor
    Directory(const Directory& rhs):
    entries(new Entry*[rhs.capacity]),size(rhs.size), capacity(rhs.capacity){
        for (size_t i = 0; i < rhs.size; i++){
            entries[i] = new Entry(*rhs.entries[i]);
        }
    }
    
    //Destructor
    ~Directory(){ //no return type
        for (size_t i = 0; i < size; ++i){
            delete entries[i];
        }
        delete [] entries;
    }
    
    //Assignment operator. Must be implemented as a member function (method)
    Directory& operator=(const Directory& rhs){
        //0. check for self assignment
        if (this != &rhs){
            //1. Free up. Cannot resize old array
            for (size_t i = 0; i < size; ++i){
                delete entries[i];
            }
            delete [] entries;
            
            //2. Allocate
            entries = new Entry*[rhs.capacity];
            
            //3. Copy over all the data
            size = rhs.size;
            capacity = rhs.capacity;
            for (size_t i = 0; i < size; ++i){
                entries[i] = new Entry(*rhs.entries[i]);
                // entries[i] = rhs.entries[i];
            }
        }
        //4. return yourself
        return *this;
    }
    
    unsigned operator[](const string& name) const{
        for (size_t i = 0; i < size; ++i){
            if (entries[i]->getName() == name){
                return entries[i]->getPhone();
            }
        }
        return 0;
    }

private:
    Entry** entries;
    size_t size;
    size_t capacity = 0;
}; // class Directory

void doNothing(Directory dir) {
    cout << dir << endl;
}

int main() {
    
    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);
    
    // Create a Directory
    Directory d;    //name, room, phone, position
    d.add("Marilyn", 123, 4567, boss);
    cout << d << endl;
    
    Directory d2 = d;	// What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << d << endl;
    
    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";
    
    Directory d3;
    d3 = d2;
    
    // Should display 1592
    cout << d2["Carmack"] << endl;
    
} // main
