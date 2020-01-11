//
// Created by zatlawy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_KEYBOARDHANDLER_H
#define BOOST_ECHO_CLIENT_KEYBOARDHANDLER_H

#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "connectionHandler.h"
#include "serverHandler.h"

using namespace std;


class keyboardHandler {
public:
    keyboardHandler(mutex & _mutex);

    void run();

private:
    // TODO:: make both connectionHandler & userData
    ConnectionHandler *connectionHandler;
    thread *serverHandlerThread;
    UserData *userData;
    mutex & _mutex;
    std::condition_variable cv;
    bool establishConnection (vector<string> &userInputVector);
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
