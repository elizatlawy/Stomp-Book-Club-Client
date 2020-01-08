//
// Created by zatlawy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_KEYBOARDHANDLER_H
#define BOOST_ECHO_CLIENT_KEYBOARDHANDLER_H

#include <string>
#include <vector>

using namespace std;


class keyboardHandler {
public:
    void run();

private:
    bool connected;
    bool loggedIn;
    string decodeLogin (vector<string> &userInputVector);
    string decodeJoin (vector<string> &userInputVector);
    string decodeAdd (vector<string> &userInputVector);
    string decodeBorrow (vector<string> &userInputVector);
    string decodeReturn(vector<string> &userInputVector);
    string decodeStatus (vector<string> &userInputVector);
    void sendMessage (string msg);
    vector<string> parseInput ( string lastUserInput);



};

#endif //BOOST_ECHO_CLIENT_KEYBOARDHANDLER_H
