//  Created by Henry Rivera on 3/1/19.
//  File Name: rec05
//  Description: Implemention of TAs with lab sections
//  Copyright © 2019 Henry Rivera. All rights reserved

#include <iostream>
#include <vector>
#include <string>
#include <vector>

using namespace std;

class StudentRecord{
    friend ostream& operator<< (ostream& os,
                                const StudentRecord& aStudentRecord){
        os << "Name: " << aStudentRecord.studentName
        << ", Grades: ";
        for (size_t i = 0; i < aStudentRecord.gradeBook.size(); ++i){
            os << aStudentRecord.gradeBook[i] << " ";
        }
        os << endl;
        return os;
    }
    
public:
    StudentRecord(const string& someStudent):
    studentName(someStudent), gradeBook(14, -1){}
    
    const string& getName() const{
        return studentName;
    }
    
    void setGrade(int grade, int ind){
        for (size_t i = 0; i < gradeBook.size(); ++i){
            if (i == ind - 1){
                gradeBook[i] = grade;
            }
        }
    }
    
private:
    string studentName;
    vector<int> gradeBook;
};

class Section{
    // Section: A2, Time slot: [Day: Tuesday, Start time: 4pm], Students: None
    friend ostream& operator<< (ostream& os,
                                const Section& aSection){
        os << "Section: " << aSection.sectionName
        << ", Time Slot: " << aSection.aTimeSlot
        << "Students: " << endl;
        if (aSection.roster.size() == 0){
            os << "None";
        }
        for (size_t i = 0; i < aSection.roster.size(); ++i){
            os << *aSection.roster[i];
        }
        return os;
    }
public:
    Section(const string& aName, const string& aDay, int aTime)
    : sectionName(aName), aTimeSlot(aDay, aTime){}
    
    void addStudent(const string& studentName){
        StudentRecord* p = new StudentRecord(studentName);
        roster.push_back(p);
    }
    
    void updateGradeBook(const string& someStudent,
                         int grade, int ind){
        for (size_t i = 0; i < roster.size(); ++i){
            if (roster[i]->getName() == someStudent){
                roster[i]->setGrade(grade, ind);
            }
        }
    }
    
    //Copy constructor
    Section(const Section& rhs): sectionName(rhs.sectionName),
    aTimeSlot(rhs.aTimeSlot) {
        for (size_t i = 0; i < rhs.roster.size(); i++){
            roster.push_back(new StudentRecord(*rhs.roster[i]));
        }
    }
    
    //Destructor
    ~Section(){ //no return type
        cout << "Section " << sectionName
        << " is being deleted" << endl;
        for (size_t i = 0; i < roster.size(); ++i){
            cout << "Deleting "
            << roster[i]->getName() << endl;
            delete roster[i];
        }
        roster.clear();
    }
private:

    //start TimeSlot class
    class TimeSlot{
        
        friend ostream& operator<< (ostream& os,
                                    const TimeSlot& aTimeSlot){
            os << "[Day: " << aTimeSlot.sectionDay
            << ", Start time: ";
            if (aTimeSlot.sectionTime <= 12){
                os << aTimeSlot.sectionTime << "am] ";
            }
            else{
                os << aTimeSlot.sectionTime - 12 << "pm] ";
            }
            return os;
        }
        
    public:
        TimeSlot(const string& aDay, int aTime) :
        sectionDay(aDay), sectionTime(aTime){}
        
        
    private:
        string sectionDay;
        int sectionTime;
    }; //end TimeSlot Class
    
    string sectionName;
    TimeSlot aTimeSlot;
    vector<StudentRecord*> roster;
};

class LabWorker{
    friend ostream& operator<< (ostream& os,
                                const LabWorker& aLabWorker){
        if (aLabWorker.workerSection == nullptr){
            os << aLabWorker.labWorkerName
            << " does not have a section";
        }
        else{
            os << aLabWorker.labWorkerName << " has "
            << *aLabWorker.workerSection;
        }
        return os;
    }
public:
    LabWorker(const string& aName) : labWorkerName(aName){}
    
    void addSection(Section& sectionName){
        workerSection = &sectionName;
    }
    
    void addGrade(const string& someStudent,
                  int someGrade, int ind){
        workerSection->updateGradeBook(someStudent, someGrade, ind);
    }
private:
    string labWorkerName;
    Section* workerSection = nullptr;
};



// Test code
void doNothing(Section sec) {
    cout << sec << endl;;
}

int main() {
    
    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;
    
    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;
    
    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe("Moe");
    cout << moe << endl;
    
    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection(secA2);
    cout << moe << endl;
    
    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection(secB3);
    cout << jane << endl;
    
    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);
    moe.addGrade("Paul", 19, 1);
    moe.addGrade("George", 16, 1);
    moe.addGrade("Ringo", 7, 1);
    cout << moe << endl;
    
    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    cout << moe << endl;
    
    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
    << "those students (or rather their records?)\n";
    
    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
    << "then make sure the following call works properly, i.e. no memory leaks\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";
    
} // main
