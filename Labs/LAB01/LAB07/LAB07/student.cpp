//  Created by Henry Rivera on 3/16/19.
//  File Name: student.cpp
//  Description: Student Class implementation cpp file
//  Copyright © 2019 Henry Rivera. All rights reserved

#include "student.hpp"
#include "registrar.hpp"
#include "course.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace ManhattanCampus{
    ostream& operator<<(ostream& os, const Student& rhs){
        os << rhs.name << ": ";
        if (rhs.courses.size() == 0){
            os << "No Courses";
        }
        else{
            for (size_t i = 0; i < rhs.courses.size(); ++i){
                os << rhs.courses[i]->getName() << " ";
            }
        }
        return os;
    }
    
    
    
    Student::Student(const string& name): name(name){}
    
    
    
    const string& Student::getName() const{
        return name;
    }
    
    
    
    bool Student::addCourse(Course* someCourse){
        for (size_t i = 0; i < courses.size(); ++i){
            if (courses[i] == someCourse){
                return false;
            }
        }
        courses.push_back(someCourse);
        return true;
    }
    
    
    
    void Student::removedFromCourse(Course* someCourse){
        for (size_t i = 0; i < courses.size(); ++i){
            if (courses[i] == someCourse){
                // delete courses[i];
                courses[i] = courses.back();
                courses.pop_back();
                return;
                /*
                 courses[i], courses[courses.size() - 1]
                 = courses[courses.size()-1], courses[i];
                 delete courses[courses.size()];
                 courses.pop_back();
                 */
            }
        }
    }
}
