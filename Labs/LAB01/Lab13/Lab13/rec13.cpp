//  Created by Henry Rivera on 5/3/19.
//  File Name: rec13.cpp
//  Description: task based lab
//  Copyright © 2019 Henry Rivera. All rights reserved

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

// 9. Calling the function to print the list
void printList(const list<int>& aLst){
    for (list<int>::const_iterator it = aLst.begin(); it != aLst.end(); ++it){
        cout << *it << ' ';
        if (it == aLst.end()){
            break;
        }
    }
}



// 10. Calling the function that prints the list, using ranged-for
void printRangedFor(const list<int>& aLst){
    for (int x: aLst){
        cout << x << ' ';
    }
}



// 11. Calling the function that, using auto, prints alternate
// items in the list
void printAutoAlt(const list<int>& aLst){
    for (auto it = aLst.begin(); it != aLst.end(); ++++it) {
        cout << *it << ' ';
//        if (it == aLst.end()){
//            break;
//        }
    }
}



// 12.  Write a function find that takes a list and value to search for.
//      What should we return if not found
list<int>::const_iterator lstFind(const list<int>& aLst, int val){
    for (list<int>::const_iterator it = aLst.begin(); it != aLst.end(); ++it){
        if (*it == val){
            return it;
        }
    }
    return aLst.end();
}



// 13.  Write a function find that takes a list and value to search for.
//      What should we return if not found
auto lstAutoFind(const list<int>& aLst, int val){
    for (auto it = aLst.begin(); it != aLst.end(); ++it){
        if (*it == val){
            return it;
        }
    }
    return aLst.end();
}



// 15. Generic algorithms: find_if
bool isEven(int n){
    return n%2 ==0;
}



// 16. Functor
class IsEven{
public:
    bool operator()(int n){
        return n%2 ==0;
    }
};



// 19. Implement find as a function for lists
vector<int>::iterator ourFind(vector<int>::iterator start, vector<int>::iterator stop, int val){
    while (start!=stop) {
        if (*start==val){
            cout << "Found value!" << endl;
            return start;
        }
        ++start;
    }
    cout << "Value NOT found!" << endl;
    return stop;
}



// 20. Implement find as a templated function
template<class resIterator, class T>
resIterator ourFind(resIterator start, resIterator stop, const T& val){
    cout << "Inside templated ourFind" << endl;
    while (start!=stop) {
        if (*start==val){
            return start;
        }
        ++start;
    }
    return stop;
}


int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> someVec = {14, 2, 20, 13, 42, 11};
    for (int x: someVec){
        cout << x << ' ';
    }
    cout << "\n=======\n";
    
    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> someList(someVec.begin(), someVec.end());
    for (int x: someList){
        cout << x << ' ';
    }
    cout << "\n=======\n";
    
    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(someVec.begin(), someVec.end());
    
    for (int x: someVec){
        cout << x << ' ';
    }
    cout << endl;
    for (int x: someList){
        cout << x << ' ';
    }
    cout << "\n=======\n";
    
    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for (size_t i = 0; i < someVec.size(); i+=2){
        cout << someVec[i] << ' ';
    }
    cout << "\n=======\n";
    
    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
    /*
    for (size_t i = 0; i < someList.size(); i+=2){
     cout << someList[i] << ' ';
    }
     */
    cout << "\n=======\n";
    //
    // Iterators
    //
    
    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for (vector<int>::iterator it = someVec.begin(); it != someVec.end(); it += 2){
        cout << *it << ' ';
    }
    cout << "\n=======\n";
    
    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    for (list<int>::iterator it = someList.begin(); it != someList.end(); ++it){
        cout << *it << ' ';
        ++it;
        if (it == someList.end()){
            break;
        }
    }
    cout << "\n=======\n";
    
    // 8. Sorting a list
    cout << "Task 8:\n";
    someList.sort();
    for (int x: someList){
        cout << x << ' ';
    }
    cout << "\n=======\n";
    
    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    printList(someList);
    cout << "\n=======\n";
    
    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    printRangedFor(someList);
    cout << "\n=======\n";
    
    //
    // Auto
    //
    
    // 11. Calling the function that, using auto, prints alternate
    // items in the list
    cout << "Task 11:\n";
    printAutoAlt(someList);
    cout << "\n=======\n";
    
    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    
    list<int>::const_iterator ind = lstFind(someList, 14);
    cout << *ind << endl;
    
    list<int>::const_iterator ind2 = lstFind(someList, 150);
    cout << *ind2;
    cout << "\n=======\n";
    
    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    
    list<int>::const_iterator ind3 = lstAutoFind(someList, 14);
    cout << *ind3 << endl;
    
    list<int>::const_iterator ind4 = lstAutoFind(someList, 150);
    cout << *ind4;
    cout << "\n=======\n";
    
    //
    // Generic Algorithms
    //
    
    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    
    list<int>::iterator find1 = find(someList.begin(), someList.end(), 14);
    if (find1 != someList.end()){
        cout << *find1;
    }
    cout << endl;
    list<int>::iterator find2 = find(someList.begin(), someList.end(), 150);
    if (find2 != someList.end()){
        cout << *find2;
    }
    
    cout << "\n=======\n";
    
    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    
    list<int>::iterator even = find_if(someList.begin(), someList.end(), isEven);
    if (even != someList.end()){
        cout << *even;
    }
    cout << "\n=======\n";
    
    // 16. Functor
    cout << "Task 16:\n";
    list<int>::iterator even2 = find_if(someList.begin(), someList.end(), IsEven());
    if (even2 != someList.end()){
        cout << *even2;
    }
    cout << "\n=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    list<int>::iterator even3 = find_if(someList.begin(), someList.end(),
                                        [](int aNum) {return aNum % 2 == 0; });
    cout << *even3;
    cout << "\n=======\n";
    
    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    
    int arr[8];
    copy(someList.begin(), someList.end(), arr);
    
    for (int x: arr){
        cout << x << ' ';
    }
    cout << endl;
    
    int* arrFind1 = find(arr, arr+8, 14);
    cout << *arrFind1;
    cout << endl;
    int* arrFind2 = find(arr, arr+8, 150);
    cout << "\n=======\n";
    
    //
    // Templated Functions
    //
    
    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    
    vector<int>::iterator res = ourFind(someVec.begin(), someVec.end(), 14);
    cout << *res;
    cout << endl;
    vector<int>::iterator res2 = ourFind(someVec.begin(), someVec.end(), 150);
    cout << *res2;
    
    cout << "\n=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    
    vector<int>::iterator res3 = ourFind(someVec.begin(), someVec.end(), 14);
    cout << *res3;
    cout << endl;
    vector<int>::iterator res4 = ourFind(someVec.begin(), someVec.end(), 150);
    cout << *res4;
    
    cout << "\n=======\n";
    
    //
    // Associative collections
    //
    
    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    
    vector<string> collection;
    string word;
    ifstream book("pooh.txt");
    if (!book) {
        cerr << "Error: File could not be opened" << endl;
        exit(1);
    }
    while (book >> word){
        vector<string>::iterator check = find(collection.begin(), collection.end(), word);
        if (check == collection.end()){
            collection.push_back(word);
        }
    }
    
    cout << "Our vector has: " << collection.size() << " words" << endl;
//    for (size_t i = 0; i < collection.size(); ++i){
//        cout << collection[i] << ' ';
//    }
    book.close();
    book.clear();
    cout << "\n=======\n";
    
    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    book.open("pooh.txt");
    set<string> menagerie;
    string word1;
    while (book >> word1){
        menagerie.insert(word1);
    }
    
    cout << "Our set has: " << menagerie.size() << " words" << endl;
    //    for (size_t i = 0; i < collection.size(); ++i){
    //        cout << collection[i] << ' ';
    //    }
    
    book.close();
    book.clear();
    cout << "\n=======\n";
    
    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    
    book.open("pooh.txt");
    map<string, vector<int>> wordMap;
    int pos = 0;
    string word2;
    while (book >> word2) {
        wordMap[word2].push_back(pos);
        pos++;
    }
//    for (const auto& elem: wordMap){
//        cout << elem.first << " ";
//        for (int index : elem.second){
//            cout << index << ", ";
//        }
//        cout << endl;
//    }
    cout << "Our wordMap has: " << wordMap.size() << " words" << endl;
    
    book.close();
    book.clear();
    cout << "\n=======\n";
}
