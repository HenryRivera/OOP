//  Created by Henry Rivera on 2/6/19.
//  File Name: hw02
//  Description: Program reads in a list of warriors with given strengths
//  and who they will battle. Then produces results of the battles and
//  the strengths of each warrior post battle
//  Copyright © 2019 Henry Rivera. All rights reserved

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


// Creates a structure of type warrior with the warrior's name and strength
struct Warrior {
    string name;
    int strength;
};

// Takes in two warriors and produces the result of the given fight
void battle(const string& first, const string& second, vector<Warrior>& allWarriors);

// Prints the number of warriors and their strengths post battle
void status(vector<Warrior>& allWarriors);

int main() {
    ifstream file("warriors.txt");
    if (!file) {
        cerr << "Error! File could not be opened" << endl;
        exit(1);
    }
    vector<Warrior> list_of_warriors; /*will hold warriors from file*/
    string line;
    Warrior someWarrior;
    
    while (file >> line) {
        if (line == "Warrior"){
            file >> someWarrior.name >> someWarrior.strength;
            list_of_warriors.push_back(someWarrior);
        }
        if (line == "Battle"){
            string first_warrior;
            string second_warrior;
            
            file >> first_warrior >> second_warrior;
            
            battle(first_warrior, second_warrior, list_of_warriors);
        }
        if (line == "Status"){
            status(list_of_warriors);
        }
    }
    file.close();
}


void battle(const string& first, const string& second, vector<Warrior>& allWarriors){
    size_t warrior1;
    size_t warrior2;
    
    //Searches through vector of Warriors to find warriors passed into function
    for (size_t i = 0; i < allWarriors.size(); ++i){
        if (allWarriors[i].name == first){
            warrior1 = i;
        }
        if (allWarriors[i].name == second){
            warrior2 = i;
        }
    }

    cout << first << " battles " << second << endl;
    
    // If both warriors are dead
    if (allWarriors[warrior1].strength == 0 && allWarriors[warrior2].strength == 0){
        cout << "Oh, NO! They're both dead! Yuck!"<< endl;
    }
    
    // If second warrior is dead
    else if (allWarriors[warrior1].strength > 0 && allWarriors[warrior2].strength == 0){
        cout << "He's dead, " << first << endl;
    }
    
    // If first warrior is dead
    else if (allWarriors[warrior1].strength == 0 && allWarriors[warrior2].strength > 0){
        cout << "He's dead, " << second << endl;
    }
    
    // If first warrior is stronger than the second
    else if (allWarriors[warrior1].strength > allWarriors[warrior2].strength){
        cout << first << " defeats " << second << endl;
        allWarriors[warrior1].strength -= allWarriors[warrior2].strength;
        allWarriors[warrior2].strength = 0;
    }
    
    // If second warrior is stronger than the first
    else if (allWarriors[warrior1].strength < allWarriors[warrior2].strength){
        cout << second << " defeats " << first << endl;
        allWarriors[warrior2].strength -= allWarriors[warrior1].strength;
        allWarriors[warrior1].strength = 0;
    }
    
    // If both warriors are of the same strength
    else{
        cout << "Mutual Annihilation: " << first <<" and "
        << second << " die at each other's hands" << endl;
        allWarriors[warrior1].strength = 0;
        allWarriors[warrior2].strength = 0;
    }
}

void status(vector<Warrior>& allWarriors){
    cout << "There are: " << allWarriors.size() << " warriors" << endl;
    for (size_t i = 0; i < allWarriors.size(); ++i){
        cout << "Warrior: " << allWarriors[i].name
        << ", strength: " << allWarriors[i].strength<< endl;
    }
}

