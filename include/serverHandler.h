//
// Created by zatlawy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_SERVERHANDLER_H
#define BOOST_ECHO_CLIENT_SERVERHANDLER_H

#include "connectionHandler.h"



class serverHandler {
public:
    serverHandler(ConnectionHandler &connectionHandler, UserData &userData); // constructor
    serverHandler(const serverHandler& other); // copy constructor
    serverHandler& operator=(const serverHandler& other); // copy assignment
    virtual ~serverHandler(); // destructor

    void run();

private:
    ConnectionHandler *connectionHandler;
    UserData *userData;
    void handleMessageFrame(string topic, string msgBody);
    void wishBookExecutor(string topic, string msgBody);
    void hasBookExecutor(string topic, string msgBody);
    void takeBookExecutor(string topic, string msgBody);
    void returnBookExecutor(string topic, string msgBody);
    void bookStatusExecutor(string topic);
    void handleConnectedFrame();
    void handleReceiptFrame(string receiptId);
    void handleErrorFrame(string errorMessage);
    vector<string> parseByLine(string message);
    void sendMessage (string msg);

};


#endif //BOOST_ECHO_CLIENT_SERVERHANDLER_H
