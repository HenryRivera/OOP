//  Created by Henry Rivera on 3/16/19.
//  File Name: student.hpp
//  Description: Student Class implementation header file
//  Copyright © 2019 Henry Rivera. All rights reserved

#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <iostream>
#include <string>
#include <vector>

namespace ManhattanCampus{
    
    class Course;
    
    class Student {
        friend std::ostream& operator<<
        (std::ostream& os, const Student& rhs);
    public:
        // Student methods needed by Registrar
        Student(const std::string& name);
        const std::string& getName() const;
        bool addCourse(Course* someCourse);
        
        // Student method needed by Course
        void removedFromCourse(Course* someCourse);
        
    private:
        std::string name;
        std::vector<Course*> courses;
    };
}

#endif
