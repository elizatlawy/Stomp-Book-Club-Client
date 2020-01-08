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
    loggedIn = false;
    cout << "enter input:" << endl;
    string lastUserInput;
    while (!loggedIn){
        if (userInputVector[0] == "login") {
            string loginMsg = decodeLogin(userInputVector);
            sendMessage(loginMsg);

    }


    while (connected) {
        getline(cin, lastUserInput);
        std::istringstream iss(lastUserInput);
        std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                         std::istream_iterator<std::string>());
        vector<std::string> userInputVector = results;


        }
        else if (userInputVector[0] == "join") {
            string joinMsg = decodeLogin(userInputVector);
            sendMessage(joinMsg);
        }
        else if (userInputVector[0] == "add") {
            string addMsg = decodeLogin(userInputVector);
            sendMessage(addMsg);
        }
        else if (userInputVector[0] == "borrow") {
            string borrowMsg = decodeLogin(userInputVector);
            sendMessage(borrowMsg);
        }
        else if (userInputVector[0] == "return") {
            string returnMsg = decodeLogin(userInputVector);
            sendMessage(returnMsg);
        }
        else if (userInputVector[0] == "status") {
            string statusMsg = decodeLogin(userInputVector);
            sendMessage(statusMsg);
        }
    } // end of while

}

string keyboardHandler::decodeLogin(vector<string> &userInputVector ) {
    string userName = userInputVector
    string output = "CONNECT" + '\n' + "accept-version:"

}

string keyboardHandler::decodeJoin(vector<string> &userInputVector) {

}

string keyboardHandler::decodeAdd(vector<string> &userInputVector) {

}

string keyboardHandler::decodeBorrow(vector<string> &userInputVector) {

}


string keyboardHandler::decodeReturn(vector<string> &userInputVector) {

}

string keyboardHandler::decodeStatus(vector<string> &userInputVector) {

}

void keyboardHandler::sendMessage(string) {}








