//  Created by Henry Rivera on 2/24/19.
//  File Name: hw04
//  Description: Continuation of game of medieval times. In this version
//  nobles are introduced and they have armies of warriors
//  Copyright © 2019 Henry Rivera. All rights reserved

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class Warrior{
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
    
    const void displayWarrior() const{
        cout << "        " << warriorName
        << " : " << warriorStrength << endl;
    }
    
    //Allows us to get Warrior's employment status
    const bool isEmployed() const{
        return hired;
    }
    
    //Allows us to set Warrior's employment status
    void setEmployed(bool someStatus) {
        hired = someStatus;
    }
    
private:
    string warriorName;
    double warriorStrength;
    bool hired;
};

class Noble{
public:
    Noble(const string& aName): nobleName(aName), armyStrength(0), alive(true){}
    
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
    
    const string& getNobleName() const{
        return nobleName;
    }
    
    const double getArmyStrength() const{
        return armyStrength;
    }
    
    //Allows us to set Noble to dead or alive
    void setLifeStatus(bool someStatus) {
        alive = someStatus;
    }
    
    bool hire(Warrior& someWarrior){
        //need to check if Noble is alive
        if (alive == false){
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
    
    void display() const{
        cout << nobleName << " has an army of "
        << nobleArmy.size() << endl;
        for (size_t i = 0; i < nobleArmy.size(); ++i) {
            nobleArmy[i]->displayWarrior();
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
        
        cout << someWarrior.getWarriorName() << ", you're fired! -- "
        << nobleName << endl;
        
        armyStrength -= someWarrior.getWarriorStrength();
        
        for (size_t i = 0; i < nobleArmy.size(); ++i) {
            if (nobleArmy[i] == &someWarrior){
                size_t pos = i;
                
                //setting Warrior ptr being fired to nullptr
                nobleArmy[i] = nullptr;
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
            someNoble.setLifeStatus(false);
        }
        
        // If second Noble's army is stronger
        else if (this->armyStrength
                 < someNoble.getArmyStrength()){
            cout << this->nobleName << " defeats "
            << someNoble.getNobleName() << endl;
            
            //Determines how much stronger winning army is
            double ratioLoss =  (someNoble.armyStrength) / (this->armyStrength);
            
            this->setStrength(0);
            this->setLifeStatus(false);
            someNoble.setStrength(ratioLoss);
        }
        
        // If the army strengths of both Nobles are the same
        else{
            cout << "Mutual Annihilation: "
            << this->nobleName <<" and "
            << someNoble.getNobleName()
            << " die at each other's hands" << endl;
            this->setStrength(0);
            this->setLifeStatus(false);
            someNoble.setStrength(0);
            someNoble.setLifeStatus(false);
        }
    }
private:
    string nobleName;
    double armyStrength;
    bool alive;
    
    vector<Warrior*> nobleArmy;
};


int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
    
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
    
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    
    jim.display();
    lance.display();
    art.display();
    linus.display();
    billie.display();
    
    art.fire(cheetah);
    art.display();
    
    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);
    
    // NEW OUTPUT CODE
    cout << "==========\n"
    << "Status after all battles, etc.\n";
    jim.display();
    lance.display();
    art.display();
    linus.display();
    billie.display();
}
