//  Created by Henry Rivera on 3/26/19.
//  File Name: Noble.cpp
//  Description: Noble class implementation
//  Copyright © 2019 Henry Rivera. All rights reserved

#include "Warrior.hpp"
#include "Noble.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace WarriorCraft {
    class Warrior;
    
    ostream& operator<<(ostream& os, const Noble& aNoble){
        os << aNoble.nobleName << " has an army of "
        << aNoble.nobleArmy.size() << endl;
        for (size_t i = 0; i < aNoble.nobleArmy.size(); ++i) {
            os << *aNoble.nobleArmy[i];
        }
        return os;
    }
    
    
    
    Noble::Noble(const string& aName):
    nobleName(aName), armyStrength(0), alive(true){}
    
    
    
    const string& Noble::getNobleName() const{
        return nobleName;
    }
    
    
    
    bool Noble::hire(Warrior& someWarrior){
        //need to check if Noble is alive
        if (alive == false){
            cerr << "Noble is not alive" << endl;
            return false;
        }
        
        // warrior can't be hired if already employed or dead
        else if (someWarrior.warriorEmployer() != nullptr
                 || someWarrior.getWarriorStrength() == 0){
            return false;
        }
        else{
            //need to update army strength for battles
            armyStrength += someWarrior.getWarriorStrength();
            
            nobleArmy.push_back(&someWarrior);
            //pushing back Warrior pointer into Noble's army
            
            someWarrior.setEmployer(this);
            return true;
        }
    }
    
    
    
    void Noble::release(Warrior* someWarrior){
        cout << someWarrior->getWarriorName()
        << " flees in terror, abandoning his lord, "
        << nobleName << endl;
        
        armyStrength -= someWarrior->getWarriorStrength();
        
        for (size_t i = 0; i < nobleArmy.size(); ++i) {
            if (nobleArmy[i] == someWarrior){
                size_t pos = i;
                
                //Releasing Warrior
                while (pos < nobleArmy.size() - 1){
                    Warrior* curr = nobleArmy[pos];
                    nobleArmy[pos] = nobleArmy[pos + 1];
                    nobleArmy[pos + 1] = curr;
                    pos++;
                }
                nobleArmy.pop_back();
                return;
            }
        }
    }
    
    
    
    // Have to update Noble army strength
    // and remove warrior from Army vector
    bool Noble::fire(Warrior& someWarrior){
        //need to check if Noble is alive
        if (alive == false){
            return false;
        }
        
        // need to check if warrior has already been fired
        else if (someWarrior.warriorEmployer() == nullptr){
            return false;
        }
        
        for (size_t i = 0; i < nobleArmy.size(); ++i) {
            if (nobleArmy[i] == &someWarrior){
                size_t pos = i;
                
                //Firing Warrior
                while (pos < nobleArmy.size() - 1){
                    Warrior* curr = nobleArmy[pos];
                    nobleArmy[pos] = nobleArmy[pos + 1];
                    nobleArmy[pos + 1] = curr;
                    pos++;
                }
                cout << "You don't work for me anymore "
                << someWarrior.getWarriorName() << "! -- "<< nobleName << endl;
                
                armyStrength -= someWarrior.getWarriorStrength();
                
                someWarrior.setEmployer(nullptr);
                nobleArmy.pop_back();
                return true;
            }
        }
        return false; //Warrior is not employed by this Noble
    }
    
    
    
    void Noble::battle(Noble& someNoble){
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
    
    
    
    void Noble::setStrength(double decrement){
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
    
    
    
    const double Noble::getArmyStrength() const{
        return armyStrength;
    }
}
