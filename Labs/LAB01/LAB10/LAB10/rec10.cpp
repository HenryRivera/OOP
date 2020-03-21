//  Created by Henry Rivera on 4/12/19.
//  File Name: rec10
//  Description: More practice with inheritance
//  Copyright © 2019 Henry Rivera. All rights reserved

#include <iostream>
#include <vector>
using namespace std;

class Instrument{
public:
    virtual void makeSound() = 0;
    
    virtual void playInstr() = 0;
};



class Brass : public Instrument{
public:
    Brass(unsigned someSize) : size(someSize) {}
    
    void makeSound(){
        cout << "To make a sound... blow on a mouthpiece of size "
        << size << endl;
    }
private:
    unsigned size;
};



class Trombone : public Brass{
public:
    Trombone(unsigned someSize) : Brass(someSize){}
    
    void playInstr(){
        cout << "Blat";
    }
};



class Trumpet : public Brass{
public:
    Trumpet(unsigned someSize) : Brass(someSize){}
    
    void playInstr(){
        cout << "Toot";
    }
};



class String : public Instrument{
public:
    String(unsigned somePitch) : pitch(somePitch) {}
    
     void makeSound(){
        cout << "To make sound... bow a string with pitch "
        << pitch << endl;
    }
private:
    unsigned pitch;
};



class Cello : public String{
public:
    Cello(unsigned somePitch) : String(somePitch) {}
    
    void playInstr(){
        cout << "Squawk";
    }
};



class Violin : public String{
public:
    Violin(unsigned somePitch) : String(somePitch) {}
    
    void playInstr(){
        cout << "Screech";
    }
};



class Percussion : public Instrument{
public:
    void makeSound(){
        cout << "To make a sound... hit me!" << endl;
    }
};



class Drum : public Percussion{
public:
    void playInstr(){
        cout << "Boom";
    }
};



class Cymbal : public Percussion{
public:
    void playInstr(){
        cout << "Crash";
    }
};



class Musician {
public:
    Musician() : instr(nullptr) {}
    
    void acceptInstr(Instrument* instPtr){
        instr = instPtr;
    }
    
    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }
    
    void testPlay() const {
        if (instr) instr->makeSound();
        else cerr << "have no instr\n";
    }
    
    void play() const {
        if (instr) instr->playInstr();
    }
private:
    Instrument* instr;
};



class MILL{
public:
    void receiveInstr(Instrument& instr){
        instr.makeSound();
        for (size_t i = 0; i < someInstr.size(); ++i){
            if (someInstr[i] == nullptr){
                someInstr[i] = &instr;
                return;
            }
        }
        someInstr.push_back(&instr);
        // return true;
    }
    
    
    void dailyTestPlay() const {
        for (size_t i = 0; i < someInstr.size(); ++i){
            if (someInstr[i] != nullptr){
                someInstr[i]->makeSound();
            }
        }
    }
    
    
    Instrument* loanOut(){
        for (size_t i = 0; i < someInstr.size(); ++i){
            if (someInstr[i] != nullptr){
                Instrument* result(someInstr[i]);
                someInstr[i] = nullptr;
                return result;
            }
        }
        return nullptr;
    }
private:
    vector<Instrument*> someInstr;
};



class Orch{
public:
    void addPlayer(Musician& musc){
        band.push_back(&musc);
    }
    
    void play(){
        for (size_t i = 0; i < band.size(); ++i){
            band[i]->play();
        }
        cout << endl;
    }
private:
    vector<Musician*> band;
};


// PART TWO
int main() {
    // The initialization phase
    
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);
    
    MILL mill;
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
    
    Musician bob;
    Musician sue;
    Musician mary;
    Musician ralph;
    Musician jody;
    Musician morgan;
    
    Orch orch;
    
    // THE SCENARIO
    
    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);
    
    //The orchestra performs
    cout << "orch performs\n";
    orch.play();
    
    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);
    
    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());
    
    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);
    
    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());
    
    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);
    
    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());
    
    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
    
    //Ralph joins the orchestra.
    orch.addPlayer(ralph);
    
    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
    
    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());
    
    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());
    
    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
    
    //Morgan joins the orchestra.
    orch.addPlayer(morgan);
    
    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
    
} // main



/*
// PART ONE
int main() {
    
    cout << "Define some instruments ------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;
    
    // use the debugger to look at the mill
    cout << "Define the MILL --------------------------------------------\n";
    MILL mill;
    
    cout << "Put the instruments into the MILL --------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
    
    cout << "Daily test -------------------------------------------------\n";
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
    
    cout << "Define some Musicians---------------------------------------\n";
    Musician harpo;
    Musician groucho;
    
    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();
    cout << endl;
    groucho.acceptInstr(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    
    cout << endl << endl;
    
    groucho.testPlay();
    cout << endl;
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    cout << endl;
    groucho.testPlay();
    cout << endl;
    harpo.testPlay();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    
    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
    
    // fifth
    mill.receiveInstr(*groucho.giveBackInstr());
    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());
    
    
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
    
    cout << endl;
}
*/
