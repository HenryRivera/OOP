//  Created by Henry Rivera on 3/26/19.
//  File Name: Warrior.cpp
//  Description: Warrior class implementation
//  Copyright © 2019 Henry Rivera. All rights reserved

#include "Warrior.hpp"
#include "Noble.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace WarriorCraft {
    class Noble;
    
    ostream& operator<<(ostream&os,
                        const Warrior& aWarrior){
        os << "        " << aWarrior.warriorName
        << ": " << aWarrior.warriorStrength;
        return os;
    }
    
    Warrior::Warrior(const string& aName,
                     double aStrength)
    : warriorName(aName), warriorStrength(aStrength)
    , bossP(nullptr){}
    
    
    
    const double Warrior::getWarriorStrength() const{
        return warriorStrength;
    }
    
    
    
    void Warrior::setWarriorStrength(double dec){
        if (dec == 0){
            warriorStrength = dec;
        }
        else{
            //Warrior loses portion of strength
            dec = warriorStrength / dec;
            warriorStrength -= dec;
        }
    }
    
    
    
    const string& Warrior::getWarriorName() const{
        return warriorName;
    }
    
    
    
    bool Warrior::runaway(){
        if (bossP == nullptr){
            return false;
        }
        bossP->release(this);
        bossP = nullptr;
        return true;
    }
    
    
    
    //Allows us to get Warrior's employment status
    const Noble* Warrior::warriorEmployer() const{
        return bossP;
    }
    
    
    
    //Allows us to set Warrior's employment status
    void Warrior::setEmployer(Noble* someNoble){
        bossP = someNoble;
    }
}
