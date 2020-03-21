//  Created by Henry Rivera on 4/6/19.
//  File Name: hw07
//  Description: Nobles and Warriors game
//  Copyright © 2019 Henry Rivera. All rights reserved

#include "Noble.hpp"
#include "Protector.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
using namespace WarriorCraft;

int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    
    sam.hires(samantha);
    
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    
    joe.battle(randy);
    joe.battle(sam);
    
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    
    janet.hires(hardy);
    janet.hires(stout);
    
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    
    janet.battle(barclay);
    janet.hires(samantha);
    
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    
    janet.battle(barclay);
    sam.battle(barclay);
    joe.battle(barclay);
}
