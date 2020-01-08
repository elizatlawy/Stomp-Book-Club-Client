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

keyboardHandler::keyboardHandler(ConnectionHandler &connectionHandler) : connectionHandler(connectionHandler) {}

void keyboardHandler::run() {
    cout << "enter input:" << endl;
    string lastUserInput;
    vector<string> userInputVector;
    UserData userData;
    while (!userData.isLoggedIn()) {
        getline(cin, lastUserInput);
        userInputVector = parseInput(lastUserInput);
        if (userInputVector[0] == "login") {
            string loginMsg = decodeLogin(userInputVector, userData);
            sendMessage(loginMsg);
        }
        while (userData.isLoggedIn()) {
            getline(cin, lastUserInput);
            userInputVector = parseInput(lastUserInput);
            if (userInputVector[0] == "join") {
                string joinMsg = decodeLogin(userInputVector);
                sendMessage(joinMsg);
            } else if (userInputVector[0] == "add") {
                string addMsg = decodeLogin(userInputVector);
                sendMessage(addMsg);
            } else if (userInputVector[0] == "borrow") {
                string borrowMsg = decodeLogin(userInputVector);
                sendMessage(borrowMsg);
            } else if (userInputVector[0] == "return") {
                string returnMsg = decodeLogin(userInputVector);
                sendMessage(returnMsg);
            } else if (userInputVector[0] == "status") {
                string statusMsg = decodeLogin(userInputVector);
                sendMessage(statusMsg);
            }
        } // end of while

    }
}

string keyboardHandler::decodeLogin(vector<string> &userInputVector, UserData userData ) {
    userData.setUserName(userInputVector[2]);
    userData.setUserPassword(userInputVector[3]);
    string output = string("CONNECT") + ('\n')  + string("accept-version:1.2");
    cout << output << endl;
    return output;

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

vector<string> keyboardHandler::parseInput(string lastUserInput) {
    std::istringstream iss(lastUserInput);
    vector<string> results(istream_iterator<string>{iss},
                           istream_iterator<string>());
    return results;
};
}
