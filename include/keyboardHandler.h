
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
    keyboardHandler(); // constructor
    keyboardHandler(const keyboardHandler& other); // copy constructor
    keyboardHandler& operator=(const keyboardHandler& other); // copy assignment
    virtual ~keyboardHandler(); // destructor

    void run();

private:
    ConnectionHandler *connectionHandler;
    UserData *userData;
    thread *serverHandlerThread;
    serverHandler *serverHandler_;

    bool establishConnection (vector<string> &userInputVector);
    void processLogin (vector<string> &userInputVector );
    void processJoin (vector<string> &userInputVector);
    void processAdd (vector<string> &userInputVector);
    void processExit (vector<string> &userInputVector);
    void processBorrow (vector<string> &userInputVector);
    void processReturn(vector<string> &userInputVector);
    void processStatus (vector<string> &userInputVector);
    void processLogOut();
    void sendMessage (string msg);
    vector<string> parseBySpace (string lastUserInput);
    string createBookName (vector<string> &userInputVector);




};

#endif //BOOST_ECHO_CLIENT_KEYBOARDHANDLER_H
