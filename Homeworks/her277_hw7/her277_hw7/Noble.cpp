//  Created by Henry Rivera on 4/13/19.
//  File Name: Noble.cpp
//  Description: Noble class implementation
//  Copyright © 2019 Henry Rivera. All rights reserved

#include "Protector.hpp"
#include "Noble.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace WarriorCraft {
    class Protector;
    
    Noble::Noble(const string& aName, double aStrength)
    : nobleName(aName), alive(true){}
    
    
    
    void Noble::battle(Noble& someNoble){
        cout << this->nobleName << " battles "
        << someNoble.nobleName << endl;
        
        
        // If the armies of both Nobles are dead
        if (this->alive == false
            && someNoble.alive == false){
            cout << "Oh, NO! They're both dead! Yuck!"<< endl;
        }
        
        
        // If the army of the first Noble is dead
        else if (this->alive == false){
            cout << "He's dead, " << someNoble.nobleName << endl;
        }
        
        
        // If the army of the second Noble is dead
        else if (someNoble.alive == false){
            cout << "He's dead, " << this->nobleName << endl;
        }
        
        
        // If the first Noble's army is stronger
        else if (this->getNobleStrength()
                 > someNoble.getNobleStrength()){
            
            this->rallyCries();
            someNoble.rallyCries();
            
            cout << this->nobleName << " defeats "
            << someNoble.nobleName << endl;
            
            //Determines how much stronger winning army is
            double ratioLoss = (this->getNobleStrength())
            / (someNoble.getNobleStrength());
            
            this->setStrength(ratioLoss);
            someNoble.setStrength(0);
            someNoble.alive = false;
        }
        
        
        // If second Noble's army is stronger
        else if (this->getNobleStrength()
                 < someNoble.getNobleStrength()){
            
            this->rallyCries();
            someNoble.rallyCries();
            
            cout << someNoble.nobleName << " defeats "
            << this->nobleName << endl;
            
            //Determines how much stronger winning army is
            double ratioLoss =  (someNoble.getNobleStrength())
            / (this->getNobleStrength());
            
            this->setStrength(0);
            this->alive = false;
            someNoble.setStrength(ratioLoss);
        }
        
        
        // If the army strengths of both Nobles are the same
        else{
            cout << "Mutual Annihilation: "
            << this->nobleName <<" and "
            << someNoble.nobleName
            << " die at each other's hands" << endl;
            this->setStrength(0);
            this->alive = false;
            someNoble.setStrength(0);
            someNoble.alive = false;
        }
    }
    
    
    
    const string& Noble::getNobleName() const{
        return nobleName;
    }
    
    
    
    const bool Noble::getLife() const{
        return alive;
    }
    
    
    
    Lord::Lord(const string& aName)
    : Noble(aName) {}
    
    
    
    bool Lord::hires(Protector& aProtector){
        //need to check if Lord is alive
        if (Noble::getLife() == false){
            return false;
        }
        
        // Protector can't be hired if already employed or dead
        else if (aProtector.protectorEmployer() != nullptr
                 || aProtector.getProtectorStrength() == 0){
            return false;
        }
        else{
            //need to update army strength for battles
            armyStrength += aProtector.getProtectorStrength();
            
            nobleArmy.push_back(&aProtector);
            //pushing back Protector pointer into Lord's army
            
            aProtector.setEmployer(this);
            return true;
        }
    }
    
    
    
    void Lord::release(Protector* aProtector){
        cout << aProtector->getProtectorName()
        << " flees in terror, abandoning his lord, "
        << this->getNobleName() << endl;
        
        armyStrength -= aProtector->getProtectorStrength();
        
        for (size_t i = 0; i < nobleArmy.size(); ++i) {
            if (nobleArmy[i] == aProtector){
                size_t pos = i;
                
                //Releasing protector
                while (pos < nobleArmy.size() - 1){
                    Protector* curr = nobleArmy[pos];
                    nobleArmy[pos] = nobleArmy[pos + 1];
                    nobleArmy[pos + 1] = curr;
                    pos++;
                }
                nobleArmy.pop_back();
                return;
            }
        }
    }
    
    
    
    // Have to update Lord army strength
    // and remove protector from army
    bool Lord::fires(Protector& someProtector){
        //need to check if Lord is alive
        if (Noble::getLife() == false){
            return false;
        }
        
        // need to check if protector has already been fired
        else if (someProtector.protectorEmployer() == nullptr){
            return false;
        }
        
        for (size_t i = 0; i < nobleArmy.size(); ++i) {
            if (nobleArmy[i] == &someProtector){
                size_t pos = i;
                
                //Firing Protector
                while (pos < nobleArmy.size() - 1){
                    Protector* curr = nobleArmy[pos];
                    nobleArmy[pos] = nobleArmy[pos + 1];
                    nobleArmy[pos + 1] = curr;
                    pos++;
                }
                cout << "You don't work for me anymore "
                << someProtector.getProtectorName()
                << "! -- "<< this->getNobleName() << endl;
                
                armyStrength -= someProtector.getProtectorStrength();
                
                someProtector.setEmployer(nullptr);
                nobleArmy.pop_back();
                return true;
            }
        }
        return false; //Protector is not employed by this Noble
    }
    
    
    
    void Lord::battle(Noble& someNoble){
        Noble::battle(someNoble);
    }
    
    
    
    void Lord::rallyCries(){
        for (size_t i = 0; i < nobleArmy.size(); ++i){
            nobleArmy[i]->battleCry();
        }
    }
    
    
    void Lord::setStrength(double decrement){
        double newStrength = 0;;
        for (size_t i = 0; i < nobleArmy.size(); ++i) {
            nobleArmy[i]->setProtectorStrength(decrement);
        }
        
        //Updates the Lord's army strength
        for (size_t i = 0; i < nobleArmy.size(); ++i) {
            newStrength += nobleArmy[i]->getProtectorStrength();
        }
        armyStrength = newStrength;
    }
    
    
    
    const double Lord::getNobleStrength() const{
        return armyStrength;
    }
    
    
    
    PersonWithStrengthToFight::PersonWithStrengthToFight
    (const string& aName, double aStrength)
    : Noble(aName), nobleStrength(aStrength) {}
    
    
    
    void PersonWithStrengthToFight::battle(Noble& someNoble){
        Noble::battle(someNoble);
    }
    
    
    
    void PersonWithStrengthToFight::rallyCries(){
        cout << "UGH!!!" << endl;
    }
    
    
    
    void PersonWithStrengthToFight::setStrength(double decrement){
        if (decrement == 0){
            nobleStrength = decrement;
            // Noble::setStrength(decrement);
        }
        else{
            //Warrior loses portion of strength
            decrement = nobleStrength / decrement;
            nobleStrength -= decrement;
            // Noble::setStrength(decrement);
        }
    }
    
    
    
    const double PersonWithStrengthToFight::getNobleStrength() const{
        return nobleStrength;
    }
}
