//
//  main.cpp
//  Final Project 10C
//
//  Created by Vishvak on 13/06/2020.
//  Copyright © 2020 Vishvak. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include "Sequence.hpp"


int main() {
    // insert code here...
    std::string seq = "ATGCGG";
    Sequence Monkey (seq);
////    Monkey.print(std::cout);
//    std::cout << std::endl;
////    Monkey.transcription(std::cout);
////    std::cout << Monkey.length();
//    std::string sequ = "ATC";
//
//    Sequence Chimp (sequ);
//   std::vector<int> matches = Monkey.find(Chimp);//
//   // Chimp.transcription(std::cout);
//    for (int i = 0; i < matches.size() ; i++) {
//        std::cout << matches[i] << " " << std::endl;
//    }
    
    Monkey.print(std::cout);
    Monkey.translation(std::cout);
  Monkey.del();
 // Chimp.del();
}
