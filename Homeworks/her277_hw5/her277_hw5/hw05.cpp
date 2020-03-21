//  Created by Henry Rivera on 3/3/19.
//  File Name: hwo5
//  Description: Implementation of Noble game using heap
//  Copyright © 2019 Henry Rivera. All rights reserved

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Warrior{
    friend ostream& operator<< (ostream&os, const Warrior& aWarrior){
        os << "        " << aWarrior.warriorName
        << " : " << aWarrior.warriorStrength;
        return os;
    }
    
public:
    Warrior(const string& aName, double aStrength)
    : warriorName(aName), warriorStrength(aStrength), hired(false) {}
    
    const double getWarriorStrength() const{
        return warriorStrength;
    }
    
    void setWarriorStrength(double dec){
        if (dec == 0){
            warriorStrength = dec;
        }
        else{
            //Warrior loses portion of strength
            dec = warriorStrength / dec;
            warriorStrength -= dec;
        }
    }
    
    const string& getWarriorName() const{
        return warriorName;
    }
    
    //Allows us to get Warrior's employment status
    const bool isEmployed() const{
        return hired;
    }
    
    //Allows us to set Warrior's employment status
    void setEmployed(const bool someStatus){
        hired = someStatus;
    }
    
private:
    string warriorName;
    double warriorStrength;
    bool hired;
};

class Noble{
    friend ostream& operator<< (ostream& os, const Noble& aNoble){
        os << aNoble.nobleName << " has an army of "
        << aNoble.nobleArmy.size() << endl;
        for (size_t i = 0; i < aNoble.nobleArmy.size(); ++i) {
            os << *aNoble.nobleArmy[i] << endl;
        }
        return os;
    }
    
public:
    Noble(const string& aName): nobleName(aName), armyStrength(0), alive(true){}
    
    const string& getNobleName() const{
        return nobleName;
    }
    
    bool hire(Warrior& someWarrior){
        //need to check if Noble is alive
        if (alive == false){
            cerr << "Warrior is not alive" << endl;
            return false;
        }
        
        // warrior can't be hired if already employed or dead
        if (someWarrior.isEmployed() == true
            || someWarrior.getWarriorStrength() == 0){
            return false;
        }
        else{
            //need to update army strength for battles
            armyStrength += someWarrior.getWarriorStrength();
            
            Warrior* ptr = &someWarrior;
            nobleArmy.push_back(ptr);
            //pushing back Warrior pointer into Noble's army
            
            someWarrior.setEmployed(true);
            return true;
        }
    }
    
    // Have to update Noble army strength
    // and remove warrior from Army vector
    bool fire(Warrior& someWarrior){
        //need to check if Noble is alive
        if (alive == false){
            return false;
        }
        
        // need to check if warrior has already been fired
        if (someWarrior.isEmployed() == false){
            return false;
        }
        
        cout << "You don't work for me anymore "
        << someWarrior.getWarriorName() << "! -- "<< nobleName << endl;
        
        armyStrength -= someWarrior.getWarriorStrength();
        
        for (size_t i = 0; i < nobleArmy.size(); ++i) {
            if (nobleArmy[i] == &someWarrior){
                size_t pos = i;
                
                //Firing Warrior
                while (pos < nobleArmy.size() - 1){
                    Warrior* curr = nobleArmy[i];
                    nobleArmy[i] = nobleArmy[i + 1];
                    nobleArmy[i + 1] = curr;
                    curr ++;
                }
                nobleArmy.pop_back();
                someWarrior.setEmployed(false);
                return true;
                
            }
        }
        return false; //Warrior is not employed by this Noble
    }
    
    void battle(Noble& someNoble){
        cout << this->nobleName << " battles "
        << someNoble.getNobleName() << endl;
        
        // If the armies of both Nobles are dead
        if (this->alive == false
            && someNoble.alive == false){
            cout << "Oh, NO! They're both dead! Yuck!"<< endl;
        }
        
        // If the army of the first Noble is dead
        else if (this->armyStrength > 0
                 && someNoble.getArmyStrength() == 0){
            cout << "He's dead, " << this->nobleName << endl;
        }
        
        // If the army of the second Noble is dead
        else if (this->armyStrength == 0
                 && someNoble.getArmyStrength() > 0){
            cout << "He's dead, " << someNoble.getNobleName() << endl;
        }
        
        // If the first Noble's army is stronger
        else if (this->armyStrength
                 > someNoble.getArmyStrength()){
            cout << this->nobleName << " defeats "
            << someNoble.getNobleName() << endl;
            
            //Determines how much stronger winning army is
            double ratioLoss = (this->armyStrength) / (someNoble.armyStrength);
            
            this->setStrength(ratioLoss);
            someNoble.setStrength(0);
            someNoble.alive = false;
        }
        
        // If second Noble's army is stronger
        else if (this->armyStrength
                 < someNoble.getArmyStrength()){
            cout << this->nobleName << " defeats "
            << someNoble.getNobleName() << endl;
            
            //Determines how much stronger winning army is
            double ratioLoss =  (someNoble.armyStrength) / (this->armyStrength);
            
            this->setStrength(0);
            this->alive = false;
            someNoble.setStrength(ratioLoss);
        }
        
        // If the army strengths of both Nobles are the same
        else{
            cout << "Mutual Annihilation: "
            << this->nobleName <<" and "
            << someNoble.getNobleName()
            << " die at each other's hands" << endl;
            this->setStrength(0);
            this->alive = false;
            someNoble.setStrength(0);
            someNoble.alive = false;
        }
    }
    
    //Destructor
    ~Noble(){ //no return type
        for (size_t i = 0; i < nobleArmy.size(); ++i){
            delete nobleArmy[i];
        }
        nobleArmy.clear();
    }
private:
    string nobleName;
    double armyStrength;
    bool alive;
    
    vector<Warrior*> nobleArmy;
    
    void setStrength(double decrement){
        int newArmyStrength = 0;;
        for (size_t i = 0; i < nobleArmy.size(); ++i) {
            nobleArmy[i]->setWarriorStrength(decrement);
        }
        
        //Updates the Noble's army strength
        for (size_t i = 0; i < nobleArmy.size(); ++i) {
            newArmyStrength += nobleArmy[i]->getWarriorStrength();
        }
        armyStrength = newArmyStrength;
    }
    
    const double getArmyStrength() const{
        return armyStrength;
    }
};

//Takes file and calls one of following functions depending on task
void readFile(ifstream& someFile);


//Displays results post firings, hirings, and battles
void displayStatus(const vector<Noble*>& allNobles,
                   const vector<Warrior*>& someWarriors);

//Calls Noble's hire method
void hireWarrior(ifstream& someFile,const vector<Noble*>& allNobles,
                 vector<Warrior*>& someWarriors);

//Calls Noble's fire method
void fireWarrior(ifstream& someFile,const vector<Noble*>& allNobles,
                 vector<Warrior*>& someWarriors);

//Calls battle between two nobles
void nobleBattle(ifstream& someFile,const vector<Noble*>& allNobles);

int main(){
    ifstream file("nobleWarriors.txt");
    if (!file){
        cerr << "File could not be opened" << endl;
        exit(1);
    }
    readFile(file);
    file.close();
}

void displayStatus(const vector<Noble*>& allNobles, const vector<Warrior*>& someWarriors){
    cout << "Status" << endl;
    cout << "======" << endl;
    cout << "Nobles:" << endl;
    if (allNobles.size() == 0){
        cout << "NONE" << endl;
    }
    else{
        for (size_t i = 0; i < allNobles.size(); ++i){
            cout << *allNobles[i];
        }
    }
    cout << "Unemployed Warriors:" << endl;
    int unemployed = 0;
    for (size_t i = 0; i < someWarriors.size(); i++) {
        if (someWarriors[i]->isEmployed() == false) {
            cout << *someWarriors[i] << endl;
            unemployed++;
        }
    }
    if (unemployed == 0) {
        cout << "NONE" << endl;
    }
}

void hireWarrior(ifstream& someFile,const vector<Noble*>& allNobles,
                 vector<Warrior*>& someWarriors){
    string employer;
    string employee;
    
    someFile >> employer >> employee;
    for (size_t i = 0; i < allNobles.size(); ++i){
        if (allNobles[i]->getNobleName() == employer){
            for (size_t j = 0; j < someWarriors.size(); ++j){
                if (someWarriors[j]->getWarriorName() == employee){
                    allNobles[i]->hire(*someWarriors[j]);
                }
            }
        }
    }
}

void fireWarrior(ifstream& someFile,const vector<Noble*>& allNobles,
                 vector<Warrior*>& someWarriors){
    string employer;
    string employee;
    
    someFile >> employer >> employee;
    for (size_t i = 0; i < allNobles.size(); ++i){
        if (allNobles[i]->getNobleName() == employer){
            for (size_t j = 0; j < someWarriors.size(); ++j){
                if (someWarriors[j]->getWarriorName() == employee){
                    allNobles[i]->fire(*someWarriors[j]);
                }
            }
        }
    }
}

void nobleBattle(ifstream& someFile,const vector<Noble*>& allNobles){
    string nobleOne;
    string nobleTwo;
    someFile >> nobleOne >> nobleTwo;
    
    Noble* firstNoble = nullptr;
    Noble* secondNoble = nullptr;
    
    for (size_t i = 0; i < allNobles.size(); ++i){
        if (allNobles[i]->getNobleName() == nobleOne){
            firstNoble = allNobles[i];
        }
        else if (allNobles[i]->getNobleName() == nobleTwo){
            secondNoble = allNobles[i];
        }
    }
    //If both nobles were found
    if (firstNoble && secondNoble){
        firstNoble->battle(*secondNoble);
    }
}

void readFile(ifstream& someFile){
    vector<Noble*> allNobles;
    vector<Warrior*> allWarriors;
    string type, nobleName, warriorName;
    double warriorStrength;
    
    while(someFile >> type){
        if (type == "Noble"){
            someFile >> nobleName;
            Noble* someNoble = new Noble(nobleName);
            allNobles.push_back(someNoble);
        }
        
        else if (type == "Warrior"){
            someFile >> warriorName >> warriorStrength;
            Warrior* someWarrior = new Warrior(warriorName, warriorStrength);
            allWarriors.push_back(someWarrior);
        }
        
        else if (type == "Hire"){
            hireWarrior(someFile, allNobles, allWarriors);
        }
        
        else if (type == "Fire"){
            fireWarrior(someFile, allNobles, allWarriors);
        }
        
        else if (type == "Battle"){
            nobleBattle(someFile, allNobles);
        }
        
        else if (type == "Status"){
            displayStatus(allNobles, allWarriors);
        }
        
        else if (type == "Clear"){
            for (size_t i = 0; i < allNobles.size(); ++i){
                delete allNobles[i];
            }
            allNobles.clear();
            //Clearing all Nobles deletes their armies so
            //just need to clear Warrior pointer vector
            allWarriors.clear();
        }
    }
}
