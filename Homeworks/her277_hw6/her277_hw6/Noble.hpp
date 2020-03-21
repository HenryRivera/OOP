//  Created by Henry Rivera on 3/26/19.
//  File Name: Noble.hpp
//  Description: Noble class header file
//  Copyright © 2019 Henry Rivera. All rights reserved

#ifndef NOBLE_HPP
#define NOBLE_HPP

#include <iostream>
#include <string>
#include <vector>


namespace WarriorCraft {
    class Warrior;
    
    class Noble{
        friend std::ostream& operator<<(std::ostream& os,
                                   const Noble& aNoble);
    public:
        Noble(const std::string& aName);
        
        
        
        const std::string& getNobleName() const;
        
        
        bool hire(Warrior& someWarrior);
        
        
        void release(Warrior* someWarrior);
        
        
        // Have to update Noble army strength
        // and remove warrior from Army vector
        bool fire(Warrior& someWarrior);
        
        
        void battle(Noble& someNoble);
        
    private:
        std::string nobleName;
        double armyStrength;
        bool alive;
        std::vector<Warrior*> nobleArmy;
        
        
        
        void setStrength(double decrement);
        
        const double getArmyStrength() const;
    };
    
}

#endif
