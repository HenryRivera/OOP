//  Created by Henry Rivera on 3/15/19.
//  File Name: rec07
//  Description: Registrar implementation
//  Copyright © 2019 Henry Rivera. All rights reserved

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student* someStudent);
    void removeStudentsFromCourse();
    
private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course* someCourse);
    
    // Student method needed by Course
    void removedFromCourse(Course* someCourse);
    
private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    bool addCourse(const string& courseName);
    bool addStudent(const string& studentName);
    bool enrollStudentInCourse(const string& someStudent,
                               const string& someCourse);
    bool cancelCourse(const string& someCourse);
    void purge();
    
private:
    size_t findStudent(const string& someStudent) const;
    size_t findCourse(const string& someCourse) const;
    
    vector<Course*> courses;
    vector<Student*> students;
};

int main() {
    
    Registrar registrar;
    
    cout << "No courses or students added yet\n";
    cout << registrar << endl;
    
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;
    
    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;
    
    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;
    
    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;
    
    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
    << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;
    
    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
    
    /*
     // [OPTIONAL - do later if time]
     cout << "ChangeStudentName FritzTheCat MightyMouse\n";
     registrar.changeStudentName("FritzTheCat", "MightyMouse");
     cout << registrar << endl;
     
     cout << "DropStudentFromCourse MightyMouse CS101.001\n";
     registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
     cout << registrar << endl;
     
     cout << "RemoveStudent FritzTheCat\n";
     registrar.removeStudent("FritzTheCat");
     cout << registrar << endl;
     */
    
    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}



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
(const string& someStudent, const string& someCourse){
    size_t studentPos = findStudent(someStudent);
    size_t coursePos = findCourse(someStudent);
    if (studentPos == students.size()
        || coursePos == courses.size()){
        return false;
    }
    students[studentPos]->addCourse(courses[coursePos]);
    courses[coursePos]->addStudent(students[studentPos]);
    return true;
}



bool Registrar::cancelCourse(const string& someCourse){
    size_t coursePos = findCourse(someCourse);
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
