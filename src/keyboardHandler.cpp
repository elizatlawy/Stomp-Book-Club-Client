//
// Created by zatlawy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include "keyboardHandler.h"
using namespace std;

void keyboardHandler::run() {
    connected = true;
    cout << "enter input:" << endl;
    string lastUserInput;
    while (connected){
        getline(cin, lastUserInput);
        std::istringstream iss(lastUserInput);
        std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                         std::istream_iterator<std::string>());
        vector<std::string> userInputVector = results;
        if(userInputVector[0] == "login"){


        }

    }






}



