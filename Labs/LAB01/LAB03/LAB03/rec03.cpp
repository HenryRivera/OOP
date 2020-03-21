//  Created by Henry Rivera on 2/15/19.
//  File Name: rec03
//  Description: Tutorial style lab related to classes and bank accounts
//  Copyright © 2019 Henry Rivera. All rights reserved

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Account{
    string name;
    int accountNumber;
};


void readFileStruct(){
    // Part 1A
    ifstream file("accounts.txt");
    if (!file) {
        cerr << "Error! File could not be opened" << endl;
        exit(1);
    }
    Account someAccount;
    vector<Account> allAccounts;
    while (file >> someAccount.name >> someAccount.accountNumber){
        allAccounts.push_back(someAccount);
    }
    for (size_t i = 0; i < allAccounts.size(); ++i){
        cout << "Name: " << allAccounts[i].name << " Account Number: " << allAccounts[i].accountNumber << endl;
    }
    file.close();
    allAccounts.clear();
    
    // Part 1B
    file.open("accounts.txt");
    if (!file) {
        cerr << "Error! File could not be opened" << endl;
        exit(1);
    }
    string name;
    int accountNumber;
    while (file >> name >> accountNumber){
        Account anAccount{name, accountNumber};
        allAccounts.push_back(anAccount);
    }
    
    for (size_t i = 0; i < allAccounts.size(); ++i){
        cout << "Name: " << allAccounts[i].name << " Account Number: " << allAccounts[i].accountNumber << endl;
    }
    file.close();
}

//Part 5
class Client{
    
public:
    friend ostream& operator<< (ostream& os, const Client& aPerson) {
        os << "Name: " << aPerson.name << " SSN: " << aPerson.ssn << endl;
        return os;
    }
    Client(const string& name, const int ssn)
    :name(name),ssn(ssn) {};
    
private:
    string name;
    int ssn;
};

class BankAccount{
    friend ostream& operator<<(ostream& os, const BankAccount& BankAccount);
public:
    BankAccount(const string& name, const int accountNumber) : name(name), accountNumber(accountNumber){};
    
    /*
    const string& getName() const{
        return name;
    }
    
    int getAccountNumber() const{
        return accountNumber;
    }
    */
    
    int getAccount() const {
        return accountNumber;
    }
    
    //Part 3D
    void deposit(int amount){
        balance += amount;
        history.emplace_back("Deposit", amount);
    }
    
    void withdrawal(int amount){
        if (amount > balance){
            cerr << "Not enough funds to complete this transaction!" << endl;
        }
        else{
            balance -= amount;
            history.emplace_back("Withdrawal", amount);
        }
    }
private:
    //Part 3A - C
    class Transaction {
    public:
        friend ostream& operator<< (ostream& os, const Transaction& aTrans) {
            os << "Transaction Type: " << aTrans.type << " Amount: " << aTrans.amount << endl;
            return os;
        }
        Transaction(const string& type, int amount) :type(type), amount(amount) {};
    private:
        string type;
        int amount;
        
    };
    string name;
    int accountNumber;
    int balance;
    vector<Transaction> history;
};

//Part 2B
/*
ostream& operator<<(ostream& os, const BankAccount& someAccount){
    os << "Name: " << someAccount.getName() << " Account: " << someAccount.getAccountNumber();
    return os;
}
 */


//Part 2C
ostream& operator<<(ostream& os, const BankAccount& someAccount){
    os << "Name: " << someAccount.name << " Account: " << someAccount.accountNumber << endl;
    for (size_t i = 0; i < someAccount.history.size(); i++){
        os << someAccount.history[i] << endl;
    }
    return os;
}


void readFileClass(){
    vector<BankAccount> allAccounts;
    string name;
    string type;
    int accountNumber;
    int amount;
    
    // Part 2A
    ifstream file("accounts.txt");
    if (!file) {
        cerr << "Error! File could not be opened" << endl;
        exit(1);
    }
    
    while (file >> name >> accountNumber){
        BankAccount anAccount{name, accountNumber};
        allAccounts.push_back(anAccount);
    }
    /*
    for (size_t i = 0; i < allAccounts.size(); ++i){
        cout << "Name: " << allAccounts[i].getName() << " Account Number: " << allAccounts[i].getAccountNumber() << endl;
    }
     */
    file.close();
    allAccounts.clear();
    
    // Part 2C
    file.open("accounts.txt");
    if (!file) {
        cerr << "Error! File could not be opened" << endl;
        exit(1);
    }
    
    while (file >> name >> accountNumber){
        BankAccount anAccount{name, accountNumber};
        allAccounts.push_back(anAccount);
    }
    
    for (size_t i = 0; i < allAccounts.size(); ++i){
        cout << allAccounts[i] << endl;
    }
    
    file.close();
    allAccounts.clear();
    
    // Part 2D
    
    allAccounts.push_back(BankAccount("Vorlon", 18));
    
    //Part 2E
    allAccounts.emplace_back("Caesar", 31);
    //BankAccount anAccount(temp, num); do not need to define variable to hold account
    //allAccounts.push_back(anAccount);
    
    allAccounts.clear();
    //Part 3E
    file.open("accounts.txt");
    if (!file) {
        cerr << "Error! File could not be opened" << endl;
        exit(1);
    }
    
    while (file >> type) {
        if(type == "Account"){
            file >> name >> accountNumber;
            BankAccount someAcc(name, accountNumber);
            allAccounts.push_back(someAcc);
        }
        
        else if (type == "Deposit") {
            file >> accountNumber >> amount;
            for (size_t i = 0; i < allAccounts.size(); i++){
                if (accountNumber == allAccounts[i].getAccount()) {
                    allAccounts[i].deposit(amount);
                }
            }
        }
        
        else if (type == "Withdraw"){
            file >> accountNumber >> amount;
            for (size_t i = 0; i < allAccounts.size(); i++) {
                if (accountNumber == allAccounts[i].getAccount()) {
                    allAccounts[i].withdrawal(amount);
                }
            }
        }
    }
}


int main(){
    readFileStruct();
    readFileClass();
}
