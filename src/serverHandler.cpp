//
// Created by zatlawy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#include <include/serverHandler.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include "serverHandler.h"
using namespace std;

serverHandler::serverHandler(ConnectionHandler &connectionHandler) : connectionHandler(connectionHandler) {

}

void serverHandler::run() {
    while (connected){
        string message;
        connectionHandler.getLine(message);
        std::istringstream iss(message);
        std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                         std::istream_iterator<std::string>());
        vector<std::string> serverOutputMessage = results;
        if(serverOutputMessage[0] == "CONNECTED"){



        }






    }
}
