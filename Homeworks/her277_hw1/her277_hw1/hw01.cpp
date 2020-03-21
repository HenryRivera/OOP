//  Created by Henry Rivera on 2/7/19.
//  Program File Name: hw01
//  Copyright © 2019 Henry Rivera. All rights reserved.
//  This program reads in an encrypted Caesar Cipher file and creates an output
//  with the lines in reverse order



#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

char decrypt_letter(char& letter, int decrement); /*function prototype*/
void decrypt_string(string& input, int decrement); /*function prototype*/

int main() {
    ifstream file("encrypted.txt");
    if (!file) {
        cerr << "Error! File could not be opened" << endl;
        exit(1);
    }
    string line;
    vector<string> decrypted; /*will hold decrypted lines from file*/
    
    getline(file, line);
    int digit = stoi(line), count;
    while (getline(file, line)) {
        decrypt_string(line, digit);
        decrypted.push_back(line);
    }
    
    count = decrypted.size() - 1;
    for (size_t i = 0; i < decrypted.size(); ++i) {
        cout << decrypted[count] << endl;
        count -= 1;
    }
    file.close();
}

/*Following function decrypts Caesar cypher
 characters and returns the decrypted value.
 Returns if character is upper case*/

char decrypt_letter(char& letter, int decrement) {
    char first_letter = 'a', last_letter = 'Z';
    if (int(letter) - decrement < first_letter && int(letter) > last_letter) {
        int leftover = int(letter) - first_letter;
        letter = 123 - (decrement - leftover); /*123 represents {*/
        return char(letter);
    }
    else if (int(letter) - decrement >= first_letter && int(letter) > last_letter) {
        letter -= decrement;
        return char(letter);
    }
    return letter;
}


/*Function below uses the above function to
 decrypt all characters in a string*/
void decrypt_string(string& input, int decrement) {
    for (int i = 0; i < input.length(); i++) {
        decrypt_letter(input[i], decrement) << ' ';
    }
}
