//  Created by Henry Rivera on 3/16/19.
//  File Name: cyclicTest.cpp
//  Description: Test file to see if separate compilation files worked
//  Copyright © 2019 Henry Rivera. All rights reserved

#include "course.hpp"
#include "student.hpp"
#include "registrar.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace ManhattanCampus;

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
     ----------------------
     */
    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
    
}
