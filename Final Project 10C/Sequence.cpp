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
#include <vector>
#include <map>





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

Nucleotide::Nucleotide(const Nucleotide &old_obj) {
    next = old_obj.next;
    prev = old_obj.prev;
    base = old_obj.base;
}


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

void Sequence::del() {
    while (start != nullptr) {
        Nucleotide* temp = start->next;
        delete start;
        start = temp;
    }
}

//Sequence::~Sequence(){
//    while (start != nullptr) {
//        Nucleotide* temp = start->next;
//        delete start;
//        start = temp;
//    }
//}




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

bool Compare(Nucleotide* i, Nucleotide* x, int l) {
    int difference = 0;
    for (int index = 0; index < l ; index++) {
        if (i == nullptr || x == nullptr) {
            return false;
        }
        
        if (i->base != x->base) {
            difference++;
        }
        if (difference > 1) {
            return false;
        }
        i = i->next;
        x = x->next;
    }
    return true;
}

bool end_of_sequence(Nucleotide* i, int len) {
    for (int curr = 0; curr < len; curr++) {
        if (i->next == nullptr) {
            return true;
        }
        i = i->next;
    }
    return false;
}

std::vector<int> Sequence::find(Sequence x) {
    Nucleotide* i = this->start;
    int seq_length = x.length();
    int index = 1;
    std::vector<int> matches;
    if (i == nullptr) {
        return matches;
    }
    
    do {
        if (Compare(i, x.start, x.length())) {
            matches.push_back(index);
        }
        i = i->next;
        index++;
    } while (!end_of_sequence(i, seq_length));
    return matches;
}
    
    
void Sequence::addition(int x, char c) {
    Nucleotide* p = start;
    if (x > this->length()) {
        std::cout << "Failed!" << std::endl;
        return;
    }
    for (int index = 1; index < x ; index++) {
        p = p->next;
    }
    Nucleotide* q = new Nucleotide(c);
    Nucleotide* temp = p->prev;
    q->next = p;
    q->prev = temp;
    temp->next = q;
    return;
}

void Sequence::addition(int x, Sequence s) {
    Nucleotide* p = start;
    if (x > this->length()) {
        std::cout << "Failed!" << std::endl;
        return;
    }
    for (int index = 1; index < x ; index++) {
        p = p->next;
    }
    Nucleotide* temp = p->prev;
    s.end->next = p;
    s.start->prev = temp;
    temp->next = s.start;
    
}

void Sequence::deletion(int x) {
        Nucleotide* p = start;
       if (x > this->length()) {
           std::cout << "Failed!" << std::endl;
           return;
       }
       for (int index = 1; index < x ; index++) {
           p = p->next;
       }

       Nucleotide* b4 = p->prev;
        Nucleotide* a = p->next;
        a->prev = b4;
        b4->next = a;
        delete p;
       return;
}

////translation matrix

void Sequence::translation(std::ostream& o) {
    
    std::map<std::string,std::string> chart = {
        {"ATA","I"},{ "ATC","I"},{ "ATT","I"},{ "ATG","M"},
        {"ACA","T"},{ "ACC","T"},{ "ACG","T"},{ "ACT","T"},
        {"AAC","N"},{ "AAT","N"},{ "AAA","K"},{ "AAG","K"},
        {"AGC","S"},{ "AGT","S"},{ "AGA","R"},{ "AGG","R"},
        {"CTA","L"},{ "CTC","L"},{ "CTG","L"},{ "CTT","L"},
        {"CCA","P"},{ "CCC","P"},{ "CCG","P"},{ "CCT","P"},
        {"CAC","H"},{ "CAT","H"},{ "CAA","Q"},{ "CAG","Q"},
        {"CGA","R"},{ "CGC","R"},{ "CGG","R"},{ "CGT","R"},
        {"GTA","V"},{ "GTC","V"},{ "GTG","V"},{ "GTT","V"},
        {"GCA","A"},{ "GCC","A"},{ "GCG","A"},{ "GCT","A"},
        {"GAC","D"},{ "GAT","D"},{ "GAA","E"},{ "GAG","E"},
        {"GGA","G"},{ "GGC","G"},{ "GGG","G"},{ "GGT","G"},
        {"TCA","S"},{ "TCC","S"},{ "TCG","S"},{ "TCT","S"},
        {"TTC","F"},{ "TTT","F"},{"TTA","L"},{ "TTG","L"},
        {"TAC","Y"},{ "TAT","Y"},{ "TAA","_"},{ "TAG","_"},
        {"TGC","C"},{ "TGT","C"},{ "TGA","_"},{ "TGG","W"}};
        
    Sequence start_codon("ATG");
    std::vector<int> index = this->find(start_codon);
    std::string codon = "";
    Nucleotide* p = this->start;
    
    while (codon != "TGA" || codon != "TAG" || codon != "TAA") {
        codon.push_back(p->base);
        //std::cout << codon << "|";
        if (codon.length() == 3) {
            o << chart[codon] << "-" ;
            codon = "";
        }
        if (p->next != nullptr) {
            p = p->next;
        } else {
            return;
        }
    }
    
}
