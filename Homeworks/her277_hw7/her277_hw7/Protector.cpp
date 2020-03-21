//  Created by Henry Rivera on 4/13/19.
//  File Name: Protector.cpp
//  Description: Protector classes implementation
//  Copyright © 2019 Henry Rivera. All rights reserved

#include "Protector.hpp"
#include "Noble.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace WarriorCraft {
    class Noble;
    class Lord;
    
    
    Protector::Protector(const string& someName, double someStrength)
    : protectorName(someName), protectorStrength(someStrength), bossP(nullptr){}
    
    const Lord* Protector::protectorEmployer() const{
        return bossP;
    }
    
    
    
    void Protector::setEmployer(Lord* someNoble){
        bossP = someNoble;
    }
    
    
    
    const double Protector::getProtectorStrength() const{
        return protectorStrength;
    }
    
    
    
    const string& Protector::getProtectorName() const{
        return protectorName;
    }
    
    
    
    const string& Protector::getBossName() const{
        return bossP->getNobleName();
    }
    
    
    
    void Protector::setProtectorStrength(double dec){
        if (dec == 0){
            protectorStrength = dec;
        }
        else{
            //Warrior loses portion of strength
            dec = protectorStrength / dec;
            protectorStrength -= dec;
        }
    }
    
    
    
    bool Protector::runaway(){
        if (bossP == nullptr){
            return false;
        }
        bossP->release(this);
        bossP = nullptr;
        return true;
    }
    
    
    
    Wizard::Wizard(const string& someName, double someStrength)
    : Protector(someName, someStrength){}
    
    // POOF
    void Wizard::battleCry(){
        cout << "POOF" << endl;
    }
    
    
    
    Warrior::Warrior(const string& someName, double someStrength)
    : Protector(someName, someStrength){}
    
    
    Archer::Archer(const string& someName, double someStrength)
    : Warrior(someName, someStrength){}
    
    void Archer::battleCry(){
        // TWANG! <archer's name> says:
        // Take that in the name of my lord, __________
        cout << "TWANG! " << Protector::getProtectorName()
        << " says: Take that in the name of my lord, "
        << Protector::getBossName() << endl;
    }
    
    
    
    Swordsman::Swordsman(const string& someName, double someStrength)
    : Warrior(someName, someStrength){}
    
    void Swordsman::battleCry(){
        // CLANG! <swordsman's name>says:
        // Take that in the name of my lord, __________
        cout << "CLANG! " << Protector::getProtectorName()
        << " says: Take that in the name of my lord, "
        << Protector::getBossName() << endl;
    }
}
