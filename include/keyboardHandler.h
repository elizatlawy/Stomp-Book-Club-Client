//
// Created by zatlawy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_KEYBOARDHANDLER_H
#define BOOST_ECHO_CLIENT_KEYBOARDHANDLER_H

#include <string>
#include <vector>
#include "connectionHandler.h"

using namespace std;


class keyboardHandler {
public:
    keyboardHandler();

    void run();

private:
    ConnectionHandler *connectionHandler;
    UserData *userData;
    string processLogin (vector<string> &userInputVector );
    string processJoin (vector<string> &userInputVector);
    string processAdd (vector<string> &userInputVector);
    string processExit (vector<string> &userInputVector);
    string processBorrow (vector<string> &userInputVector);
    string processReturn(vector<string> &userInputVector);
    string processStatus (vector<string> &userInputVector);
    string processLogOut();
    void sendMessage (string msg);
    vector<string> parseBySpace (string lastUserInput);




};

#endif //BOOST_ECHO_CLIENT_KEYBOARDHANDLER_H
