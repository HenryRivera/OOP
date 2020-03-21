//  Created by Henry Rivera on 3/16/19.
//  File Name: course.cpp
//  Description: Class Course implementation cpp file
//  Copyright © 2019 Henry Rivera. All rights reserved

#include "course.hpp"
#include "student.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//reason for name: worked on from Manhattan Campus
namespace ManhattanCampus{
    
    class Student;
    
    ostream& operator<<(ostream& os, const Course& rhs){
        os << rhs.name << ": ";
        if (rhs.students.size() == 0){
            os << "No Students";
        }
        else{
            for (size_t i=0; i < rhs.students.size(); ++i){
                os << rhs.students[i]->getName() << " ";
            }
        }
        return os;
    }
    
    
    
    Course::Course(const string& courseName): name(courseName){}
    
    
    const string& Course::getName() const{
        return name;
    }
    
    
    
    bool Course::addStudent(Student* someStudent){
        for (size_t i = 0; i < students.size(); ++i){
            if (students[i] == someStudent){
                return false;
            }
        }
        students.push_back(someStudent);
        return true;
    }
    
    
    
    void Course::removeStudentsFromCourse(){
        for (size_t i = 0; i < students.size(); ++i){
            students[i]->removedFromCourse(this);
        }
        students.clear();
    }
    
}
