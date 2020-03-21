//  Created by Henry Rivera on 4/13/19
//  File Name: Protector.hpp
//  Description: Protector header file
//  Copyright © 2019 Henry Rivera. All rights reserved

#ifndef PROTECTOR_HPP
#define PROTECTOR_HPP

#include <iostream>
#include <string>


namespace WarriorCraft {
    class Noble;
    class Lord;
    
    
    class Protector{
    public:
        Protector(const std::string& someName, double someStrength);
        
        const Lord* protectorEmployer() const;
        
        
        
        void setEmployer(Lord* someNoble);
        
        
        
        const double getProtectorStrength() const;
        
        
        
        const std::string& getProtectorName() const;
        
        
        
        const std::string& getBossName() const;
        
        
        
        void setProtectorStrength(double dec);
        
        
        
        virtual void battleCry() = 0;
        
        
        
        bool runaway();
    private:
        std::string protectorName;
        double protectorStrength;
        Lord* bossP;
    };
    
    
    
    class Wizard : public Protector{
    public:
        Wizard(const std::string& someName, double someStrength);
        
        void battleCry();
    };
    
    
    
    class Warrior: public Protector{
    public:
        Warrior(const std::string& someName, double someStrength);
        
        virtual void battleCry() = 0;
    };
    
    
    
    class Archer : public Warrior{
    public:
        Archer(const std::string& someName, double someStrength);
        
        void battleCry();
    };
    
    
    
    class Swordsman : public Warrior{
    public:
        Swordsman(const std::string& someName, double someStrength);
        
        void battleCry();
    };
}

#endif
