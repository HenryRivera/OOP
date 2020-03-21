//  Created by Henry Rivera on 2/7/19.
//  Copyright © 2019 Henry Rivera. All rights reserved.
//  Program File Name: Rec01
//  This program implements Conway's Game of Life

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*Takes in a "parent" generation and produces a "child" based on the rules*/
void game_of_life(vector<string>& new_world) {
    vector<string> child = new_world;
    int count;
    for (size_t row= 1; row < child.size() - 1; row++) {
        for (size_t col= 1; col < child[row].size() - 1; col++) {
            count = 0;
            char cell;
            cell = child[row][col];
            if (child[row - 1][col - 1] == '*') { /*top left neighbor*/
                count++;
            }
            if (child[row - 1][col] == '*') { /*top neighbor*/
                count++;
            }
            if (child[row - 1][col + 1] == '*') { /*top right neighbor*/
                count++;
            }
            if (child[row][col - 1] == '*') { /*left neighbor*/
                count++;
            }
            if (child[row][col + 1] == '*') { /*right neighbor*/
                count++;
            }
            if (child[row + 1][col - 1] == '*') { /*bottom left neighbor*/
                count++;
            }
            if (child[row + 1][col] == '*') { /*bottom neighbor*/
                count++;
            }
            if (child[row + 1][col + 1] == '*') { /*bottom right neighbor*/
                count++;
            }
            /*Determine if cell lives or dies in next generation*/
            if (cell == '*') {
                if (count == 2 || count == 3) {
                    new_world[row][col] = '*';
                }
                else {
                    new_world[row][col] = '-';
                }
            }
            else {
                if (count == 3) {
                    new_world[row][col] = '*';
                }
                else {
                    new_world[row][col] = '-';
                }
            }
        }
    }
}

int main() {
    ifstream game("life.txt");
    if (!game) {
        cerr << "Error: File could not be opened" << endl;
        exit(1);
    }
    string line, border="aaaaaaaaaaaaaaaaaaaaaa";
    vector<string> parent;
    parent.push_back(border);
    cout << "Initial World" << endl;
    while (getline(game,line) ){
        cout << line << endl;
        line = "a" + line + "a";
        parent.push_back(line);
    }
    parent.push_back(border);
    cout << "====================" << endl;
    game.close();
    
    for (size_t generation = 1; generation < 11; generation++){
        cout << "Generation: " << generation << endl;
        game_of_life(parent);
        for (size_t row = 1; row < parent.size() - 1; ++row) {
            for (size_t col = 1; col < parent[0].size() - 1; ++col) {
                cout << parent[row][col];
            }
            cout << endl;
        }
        cout << "====================" << endl;
    }
}
