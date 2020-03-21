//  Created by Henry Rivera on 3/16/19.
//  File Name: registrar.cpp
//  Description: Registrar Class implementation cpp file
//  Copyright © 2019 Henry Rivera. All rights reserved

#include "registrar.hpp"
#include "course.hpp"
#include "student.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//reason for name: worked on from Manhattan Campus
namespace ManhattanCampus {
    class Student;
    class Course;
    
    ostream& operator<<(ostream& os, const Registrar& rhs){
        os << "Registrar's Report" << endl;
        os << "Courses:" << endl;
        for (size_t i = 0; i < rhs.courses.size(); ++i){
            os << *rhs.courses[i] << endl;
        }
        os << "Students:" << endl;
        for (size_t i = 0; i < rhs.students.size(); ++i){
            os << *rhs.students[i] << endl;
        }
        return os;
    }
    
    
    
    Registrar::Registrar(){}
    
    
    
    bool Registrar::addCourse(const string& courseName){
        if (findCourse(courseName) == courses.size()){
            Course* someCourse = new Course(courseName);
            courses.push_back(someCourse);
            return true;
        }
        return false;
    }
    
    
    
    bool Registrar::addStudent(const string& studentName){
        if (findStudent(studentName) == students.size()){
            Student* someStudent = new Student(studentName);
            students.push_back(someStudent);
            return true;
        }
        return false;
    }
    
    
    
    bool Registrar::enrollStudentInCourse
    (const string& studentName, const string& courseName){
        size_t studentPos = findStudent(studentName);
        size_t coursePos = findCourse(courseName);
        if (studentPos == students.size()
            || coursePos == courses.size()){
            return false;
        }
        students[studentPos]->addCourse(courses[coursePos]);
        courses[coursePos]->addStudent(students[studentPos]);
        return true;
    }
    
    
    
    bool Registrar::cancelCourse(const string& courseName){
        size_t coursePos = findCourse(courseName);
        if (coursePos == courses.size()){
            return false;
        }
        for (size_t i = 0; i < students.size(); ++i){
            students[i]->removedFromCourse(courses[coursePos]);
        }
        //    courses[coursePos], courses[courses.size()]
        //    = courses[courses.size()], courses[coursePos];
        delete courses[coursePos];
        courses[coursePos] = courses.back();
        courses.pop_back();
        return true;
    }
    
    
    
    void Registrar::purge(){
        for (size_t i = 0; i < students.size(); i++) {
            delete students[i];
        }
        students.clear();
        
        for (size_t i = 0; i < courses.size(); i++) {
            delete courses[i];
        }
        courses.clear();
    }
    
    
    
    size_t Registrar::findStudent(const string& someName) const{
        for (size_t i = 0; i < students.size(); ++i){
            if (students[i]->getName() == someName){
                return i;
            }
        }
        return students.size();
    }
    
    
    
    size_t Registrar::findCourse(const string& someCourse) const{
        for (size_t i = 0; i < courses.size(); ++i){
            if (courses[i]->getName() == someCourse){
                return i;
            }
        }
        return courses.size();
    }
}
