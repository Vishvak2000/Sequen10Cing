//
//  Sequence.hpp
//  Final Project 10C
//
//  Created by Vishvak on 13/06/2020.
//  Copyright © 2020 Vishvak. All rights reserved.
//

#ifndef Sequence_hpp
#define Sequence_hpp

#include <stdio.h>
#include <string>
#include <iostream>

class Nucleotide {
public:
    char base;
    Nucleotide* next;
    Nucleotide* prev;
    

    Nucleotide (char c);
    Nucleotide (const Nucleotide &old_obj);
    
    friend class Sequence;
};


class Sequence {
    
public:
    
    //** STANDARD LIST FUNCTIONS**//
    Nucleotide* start;
    Nucleotide* end;

    Sequence(std::string txt);
    void del();
  // ~Sequence(); //RAII?
    void add(char c);
    void print(std::ostream& o);
    int length();
    
    //**CENTRAL DOGMA FUNCTIONS **//
    void transcription(std::ostream& o);
    void translation(std::ostream& o);
    
    
    //**FIND**//
    std::vector<int> find(Sequence x, int snp);
    //**MUTATION**//
    void addition(int x, char c);
    void addition(int x, Sequence s);
    
    void deletion(int x);
};





/* class Sequence_Iterator {
private:
    Nucleotide* pos;
public:
    Sequence_Iterator( Sequence* x);
    Sequence_Iterator( Nucleotide* x);
    //Nucleotide* get_pos() {return pos;}
    Sequence_Iterator operator ++();
    Sequence_Iterator operator --();
    friend class Sequence;

     //for destructor

};
*/
#endif /* Sequence_hpp */
