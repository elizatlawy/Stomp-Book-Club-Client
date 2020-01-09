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
    keyboardHandler(ConnectionHandler &connectionHandler);

    void run();

private:
    ConnectionHandler *connectionHandler;
    UserData *userData;
    string processLogin (vector<string> &userInputVector );
    string processJoin (vector<string> &userInputVector);
    string processSubscribe (vector<string> &userInputVector);
    string processUnsubscribe (vector<string> &userInputVector);
    string processBorrow (vector<string> &userInputVector);
    string processReturn(vector<string> &userInputVector);
    string processStatus (vector<string> &userInputVector);
    void sendMessage (string msg);
    vector<string> parseInput ( string lastUserInput);



};

#endif //BOOST_ECHO_CLIENT_KEYBOARDHANDLER_H
