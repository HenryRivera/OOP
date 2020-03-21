//  Created by Henry Rivera on 2/14/19.
//  File Name: hw03
//  Description: Program reads in a list of warriors with given strengths
//  and who they will battle. Then produces results of the battles and
//  the strengths of each warrior post battle
//  Copyright © 2019 Henry Rivera. All rights reserved

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& someWarrior){
        os << "Warrior: " << someWarrior.warriorName
        << ", " << someWarrior.aWeapon;
        return os;
    }
public:
    Warrior(const string& warriorName, const string& weaponName, int weaponStrength)
    : warriorName(warriorName), aWeapon(weaponName, weaponStrength){}
    
    const string& getName() const{
        return warriorName;
    }

    
    const int getStrength() const{
        return aWeapon.getWeaponStrength();
    }
    
    void weakenWeapon(int decrease){
        aWeapon.setStrength(decrease);
    }
    
    
private:
    class Weapon{
        friend ostream& operator<< (ostream& os, const Weapon& aWeapon){
            os << "Weapon: " << aWeapon.weaponName << ", " << aWeapon.weaponStrength;
            return os;
        }
    public:
        Weapon(const string& weaponName, int weaponStrength)
        : weaponName(weaponName), weaponStrength(weaponStrength){}
        
        const int getWeaponStrength() const{
            return weaponStrength;
        }
        
        void setStrength(int decrease){
            weaponStrength -= decrease;
        }
    private:
        string weaponName;
        int weaponStrength;
    };
    string warriorName;
    Weapon aWeapon; //Need to create an instance of type Weapon
    // in order to inilialize in Warrior initialization list
};

// Searches the given vector for the warriors and makes them fight
void battle(const string& first, const string& second, vector<Warrior>& allWarriors);
// Takes in a vector and displays it
void displayVector(const vector<Warrior>& allWarriors);

int main(){
    ifstream file("warriors.txt");
    if (!file){
        cerr << "File could not be opened" << endl;
        exit(1);
    }
    vector<Warrior> allWarriors; //Stores all warriors
    string type, warriorName, weaponName;
    int weaponStrength;
    
    while(file >> type){
        if (type == "Warrior"){
            file >> warriorName >> weaponName >> weaponStrength;
            Warrior someWarrior{warriorName, weaponName, weaponStrength};
            allWarriors.push_back(someWarrior);
        }
        
        else if (type == "Battle"){
            string firstWarrior;
            string secondWarrior;
            
            file >> firstWarrior >> secondWarrior;
            battle(firstWarrior, secondWarrior, allWarriors);
        }
        
        else if (type == "Status"){
            displayVector(allWarriors);
        }
    }
    file.close();
}


void battle(const string& first, const string& second,
            vector<Warrior>& allWarriors){
    size_t warrior1;
    size_t warrior2;
    
    //Searches through vector of Warriors to
    //find warriors passed into function
    for (size_t i = 0; i < allWarriors.size(); ++i){
        if (allWarriors[i].getName() == first){
            warrior1 = i;
        }
        if (allWarriors[i].getName() == second){
            warrior2 = i;
        }
    }
    
    cout << first << " battles " << second << endl;
    // If both warriors are dead
    if (allWarriors[warrior1].getStrength() == 0
        && allWarriors[warrior2].getStrength() == 0){
        cout << "Oh, NO! They're both dead! Yuck!"<< endl;
    }
    
    // If second warrior is dead
    else if (allWarriors[warrior1].getStrength() > 0
             && allWarriors[warrior2].getStrength() == 0){
        cout << "He's dead, " << first << endl;
    }
    
    // If first warrior is dead
    else if (allWarriors[warrior1].getStrength() == 0
             && allWarriors[warrior2].getStrength() > 0){
        cout << "He's dead, " << second << endl;
    }
    
    // If first warrior is stronger than the second
    else if (allWarriors[warrior1].getStrength()
             > allWarriors[warrior2].getStrength()){
        cout << first << " defeats " << second << endl;
        int warrior2strength = allWarriors[warrior2].getStrength();
        allWarriors[warrior1].weakenWeapon(warrior2strength);
        allWarriors[warrior2].weakenWeapon(warrior2strength);
    }
    
    // If second warrior is stronger than the first
    else if (allWarriors[warrior1].getStrength()
             < allWarriors[warrior2].getStrength()){
        cout << second << " defeats " << first << endl;
        allWarriors[warrior2].weakenWeapon(allWarriors[warrior1].getStrength());
        allWarriors[warrior1].weakenWeapon(allWarriors[warrior2].getStrength());
    }
    
    // If both warriors are of the same strength
    else{
        cout << "Mutual Annihilation: " << first <<" and "
        << second << " die at each other's hands" << endl;
        allWarriors[warrior1].weakenWeapon(allWarriors[warrior1].getStrength());
        allWarriors[warrior2].weakenWeapon(allWarriors[warrior2].getStrength());
    }
}

void displayVector(const vector<Warrior>& allWarriors){
    cout << "There are: " << allWarriors.size() << " warriors" << endl;
    for (size_t i = 0; i < allWarriors.size(); ++i){
        cout << allWarriors[i] <<endl;
    }
}
