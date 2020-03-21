//  Created by Henry Rivera on 2/8/19.
//  Copyright © 2019 Henry Rivera. All rights reserved.
//  File name: Rec01
//  Program Description: Program opens and reads a file of chemical formulas and groups hydrocarbons of same molecular formula and sorts them

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;


struct Hydrocarbon{
    vector<string> formula_names;
    int carbon_amount;
    int hydrogen_amount;
};

// Takes an input from user and checks to see if input is a correct file name
void open_stream(ifstream& input);

// Takes input from stream and creates a vector of type Hydrocarbon
void read_file(ifstream& file, vector<Hydrocarbon>& allHydrocarbons);

//Searches vector and checks to see if hydrocarbon formula is already inside
size_t find_molecule(const vector<Hydrocarbon>& allHydrocarbons, Hydrocarbon someHydrocarbon);

//Sorts vector based on carbons. If carbons equal then sorts by hydrogens
void sort_vector(vector<Hydrocarbon>& allHydrocarbons);

//Prints sorted vector
void print_vector(const vector<Hydrocarbon>& allHydrocarbons);

int main() {
    ifstream file_name;
    vector<Hydrocarbon> allHydrocarbons;
    open_stream(file_name);
    read_file(file_name, allHydrocarbons);
    sort_vector(allHydrocarbons);
    print_vector(allHydrocarbons);
    file_name.close();
}

void open_stream(ifstream& input){
    string file_name;
    cout << "Please enter the file name" << endl;
    cin >> file_name;
    input.open(file_name);
    while (!input){
        input.clear();
        cout << "File could not be opened. Please enter another file name" << endl;
        cin >> file_name;
        input.open(file_name);
    }
}

void read_file(ifstream& file, vector<Hydrocarbon>& allHydrocarbons){
    char carbon_or_hydrogen;
    string name;
    
    
    Hydrocarbon someHydrocarbon;
    while (file >> name >> carbon_or_hydrogen
           >> someHydrocarbon.carbon_amount >> carbon_or_hydrogen >> someHydrocarbon.hydrogen_amount){
        size_t index = find_molecule(allHydrocarbons, someHydrocarbon);
        if (index == allHydrocarbons.size()){
            someHydrocarbon.formula_names.clear();
            (someHydrocarbon.formula_names).push_back(name);
            allHydrocarbons.push_back(someHydrocarbon);
        }
        else{
            allHydrocarbons[index].formula_names.push_back(name);
        }
    }
}

size_t find_molecule(const vector<Hydrocarbon>& allHydrocarbons, Hydrocarbon someHydrocarbon){
    for (size_t i = 0; i < allHydrocarbons.size(); ++i){
        if (allHydrocarbons[i].carbon_amount == someHydrocarbon.carbon_amount && allHydrocarbons[i].hydrogen_amount == someHydrocarbon.hydrogen_amount){
            return(i);
        }
    }
    return(allHydrocarbons.size());
}

void sort_vector(vector<Hydrocarbon>& allHydrocarbons){
    for (size_t i = 0; i < allHydrocarbons.size(); ++i){
        for (size_t j = 0; j < allHydrocarbons.size() - 1; ++j){
            if (allHydrocarbons[j].carbon_amount > allHydrocarbons[j + 1].carbon_amount
            || (allHydrocarbons[j].carbon_amount == allHydrocarbons[j + 1].carbon_amount && allHydrocarbons[j].hydrogen_amount > allHydrocarbons[j + 1].hydrogen_amount)){
                Hydrocarbon molecule_name;
                molecule_name = allHydrocarbons[j];
                allHydrocarbons[j] = allHydrocarbons[j + 1];
                allHydrocarbons[j + 1] = molecule_name;
            }
        }
    }
}

void print_vector(const vector<Hydrocarbon>& allHydrocarbons) {
    for (size_t i = 0; i < allHydrocarbons.size(); i++) {
        cout << "C" << allHydrocarbons[i].carbon_amount << "H" << allHydrocarbons[i].hydrogen_amount << " ";
        for (size_t name = 0; name < (allHydrocarbons[i].formula_names).size(); name++) {
            cout << (allHydrocarbons[i].formula_names)[name] << " ";
        }
        cout << endl;
    }
}
