//  Created by Henry Rivera on 3/16/19.
//  File Name: registrar.hpp
//  Description: Registrar Class implementation header file
//  Copyright © 2019 Henry Rivera. All rights reserved

#ifndef REGISTRAR_HPP
#define REGISTRAR_HPP

#include <iostream>
#include <string>
#include <vector>

namespace ManhattanCampus{
    class Student;
    class Course;
    
    class Registrar {
        friend std::ostream& operator<<
        (std::ostream& os, const Registrar& rhs);
    public:
        Registrar();
        
        
        
        bool addCourse(const std::string& courseName);
        
        
        
        bool addStudent(const std::string& studentName);
        
        
        
        bool enrollStudentInCourse
        (const std::string& someStudent, const std::string& someCourse);
        
        
        
        bool cancelCourse(const std::string& someCourse);
        
        
        
        void purge();
    private:
        size_t findStudent(const std::string& someStudent) const;
        size_t findCourse(const std::string& someCourse) const;
        
        std::vector<Course*> courses;
        std::vector<Student*> students;
    };
}
#endif
