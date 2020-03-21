//  Created by Henry Rivera on 4/13/19.
//  File Name: Noble.hpp
//  Description: Noble class header file
//  Copyright © 2019 Henry Rivera. All rights reserved

#ifndef NOBLE_HPP
#define NOBLE_HPP

#include <iostream>
#include <string>
#include <vector>


namespace WarriorCraft {
    class Protector;
    
    
    
    class Noble{
    public:
        Noble(const std::string& aName, double aStrength = 0);
        
        
        
        virtual void battle(Noble& someNoble);
        
        
        
        virtual void rallyCries() = 0;
        
        
        
        virtual void setStrength(double decrement) = 0;
        
        
        
        virtual const double getNobleStrength() const = 0;
        
        
        
        const std::string& getNobleName() const;
        
        
        
        const bool getLife() const;
    private:
        std::string nobleName;
        bool alive;
    };
    
    
    
    class Lord : public Noble{
    public:
        Lord(const std::string& aName);
        
        
        
        bool hires(Protector& aProtector);
        
        
        
        void release(Protector* aProtector);
        
        
        
        bool fires(Protector& aProtector);
        
        
        
        void battle(Noble& someNoble);
        
        
        
        void rallyCries();
        
        
        
        void setStrength(double decrement);
        
        
        
        const double getNobleStrength() const;
    private:
        std::vector<Protector*> nobleArmy;
        double armyStrength;
    };
    
    
    
    class PersonWithStrengthToFight : public Noble{
    public:
        PersonWithStrengthToFight(const std::string& aName, double aStrength);
        
        
        
        void battle(Noble& someNoble);
        
        
        
        void rallyCries();
        
        
        
        void setStrength(double decrement);
        
        
        
        const double getNobleStrength() const;
    private:
        double nobleStrength;
    };
    
}

#endif
