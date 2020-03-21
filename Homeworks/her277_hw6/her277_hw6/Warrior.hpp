//  Created by Henry Rivera on 3/26/19.
//  File Name: Warrior.hpp
//  Description: Warrior header file
//  Copyright © 2019 Henry Rivera. All rights reserved

#ifndef WARRIOR_HPP
#define WARRIOR_HPP

#include <iostream>
#include <string>


namespace WarriorCraft {
    class Noble;
    
    
    
    class Warrior{
        friend std::ostream& operator<<(std::ostream&os,
                                   const Warrior& aWarrior);
        
    public:
        Warrior(const std::string& aName, double aStrength);
        
        
        const double getWarriorStrength() const;
        
        
        void setWarriorStrength(double dec);
        
        
        const std::string& getWarriorName() const;
        
        
        bool runaway();
        
        
        //Allows us to get Warrior's employment status
        const Noble* warriorEmployer() const;
        
        
        //Allows us to set Warrior's employment status
        void setEmployer(Noble* someNoble);
        
    private:
        std::string warriorName;
        double warriorStrength;
        Noble* bossP;
    };
}

#endif
