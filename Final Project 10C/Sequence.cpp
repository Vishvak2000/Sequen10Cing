//
//  Sequence.cpp
//  Final Project 10C
//
//  Created by Vishvak on 13/06/2020.
//  Copyright © 2020 Vishvak. All rights reserved.
//

#include "Sequence.hpp"
#include <string>
#include <iostream>




//Sequence Iterator::



//Sequence_Iterator::Sequence_Iterator(Sequence* x): pos(x->start) {
//    if (x->start == nullptr) {
//        std::cout << "empty list!" << std::endl;
//    }
//}
//
//Sequence_Iterator::Sequence_Iterator(Nucleotide* x): pos(x) {}
//
//Sequence_Iterator Sequence_Iterator::operator ++(){
//    Nucleotide* p = pos->next;
//    pos = p;
//    return *this;
//}
//
//Sequence_Iterator Sequence_Iterator::operator --(){
//    Nucleotide* p = pos->prev;
//    pos = p;
//    return *this;
//}



//---------------------

//Nucleotide (Node ctor)
Nucleotide::Nucleotide(char c): base(c), next(nullptr), prev(nullptr) {}


//Sequence (List ctor)
Sequence::Sequence(std::string txt): start(nullptr), end(nullptr) {
    for (size_t i = 0 ; i < txt.length() ; i++) {
        add(txt[i]);
    }
}

void Sequence::add(char c) {
    Nucleotide* p = new Nucleotide(c);
    if (start == nullptr) {
        start = p;
        end = p;
    } else {
        end->next = p;
        p->prev = end;
        end = p;
    }
}

Sequence::~Sequence(){
    Nucleotide* p;
    p = start;
    while (p != nullptr) {
        Nucleotide* temp = p->next;
        delete p;
        p = temp;
    }
}


void Sequence::print(std::ostream& o) {
    Nucleotide* i;
    i = start;
    while (i != nullptr) {
        o << i->base << " ";
        i = i->next;
    }
    o << std::endl;
}

int Sequence::length(){
    Nucleotide* i;
    i = start;
    int l = 0;
    while (i != nullptr) {
        l++;
        i = i->next;
    }
    return l;
}

void Sequence::transcription(std::ostream& o) {
    Nucleotide* i;
    i = start;
    while (i != nullptr) {
        if (i->base == 'T') {
            o << 'U' << " ";
            i = i->next;
        } else {
        o << i->base << " ";
        i = i->next;
        }
    }
    o << std::endl;
}


