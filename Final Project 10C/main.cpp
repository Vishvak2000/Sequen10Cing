//
//  main.cpp
//  Final Project 10C
//
//  Created by Vishvak on 13/06/2020.
//  Copyright © 2020 Vishvak. All rights reserved.
//

#include <iostream>
#include <string>
#include "Sequence.hpp"


int main() {
    // insert code here...
    std::string seq = "GACT";
    Sequence Monkey (seq);
    Monkey.print(std::cout);
    std::cout << std::endl;
    Monkey.transcription(std::cout);
    std::cout << Monkey.length();
    
}
