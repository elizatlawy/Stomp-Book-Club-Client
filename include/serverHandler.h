//
// Created by zatlawy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_SERVERHANDLER_H
#define BOOST_ECHO_CLIENT_SERVERHANDLER_H

#include "connectionHandler.h";



class serverHandler {
public:
    serverHandler(ConnectionHandler &connectionHandler);
    UserData userData;

    void run();

private:
    ConnectionHandler &connectionHandler;




};


#endif //BOOST_ECHO_CLIENT_SERVERHANDLER_H
