//
// Created by zatlawy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_SERVERHANDLER_H
#define BOOST_ECHO_CLIENT_SERVERHANDLER_H

#include "connectionHandler.h"



class serverHandler {
public:
    serverHandler(ConnectionHandler &connectionHandler, UserData &userData); // constructor

    virtual ~serverHandler(); // destructor

    void run();

private:
    ConnectionHandler *connectionHandler;
    UserData *userData;
    void messageExecutor(string topic, string msgBody);
    void sendMessage (string msg);
    vector<string> parseByLine(string message);
    vector<string> parseBySpace(string message);
    void wishBookExecutor(string topic, string msgBody);
    void hasBookExecutor(string topic, string msgBody);
    void takeBookExecutor(string topic, string msgBody);
    void returnBookExecutor(string topic, string msgBody);
    void bookStatusExecutor(string topic);

};


#endif //BOOST_ECHO_CLIENT_SERVERHANDLER_H
