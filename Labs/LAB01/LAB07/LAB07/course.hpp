//  Created by Henry Rivera on 3/16/19.
//  File Name: course.hpp
//  Description: Class Course implementation header file
//  Copyright © 2019 Henry Rivera. All rights reserved

#ifndef COURSE_HPP
#define COURSE_HPP

#include <iostream>
#include <string>
#include <vector>

//reason for name: worked on from Manhattan Campus
namespace ManhattanCampus{
    
    class Student;
    
    class Course {
        friend std::ostream& operator<<(std::ostream& os, const Course& rhs);
    public:
        // Course methods needed by Registrar
        Course(const std::string& courseName);
        
        
        
        const std::string& getName() const;
        
        
        
        bool addStudent(Student* studentName);
        
        
        
        void removeStudentsFromCourse();
    private:
        std::string name;
        std::vector<Student*> students;
    };
}
#endif
