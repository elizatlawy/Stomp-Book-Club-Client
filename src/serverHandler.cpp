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
    while (connectionHandler.isConnected()){
        string message;
        connectionHandler.getLine(message);
        std::istringstream iss(message);
        std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                         std::istream_iterator<std::string>());
        vector<std::string> serverOutputMessage = results;
        if(serverOutputMessage[0] == "CONNECTED"){
            userData = connectionHandler.getUserData();
            userData.logIn();
            cout << "Login successful" << endl;
        }
        else if(serverOutputMessage[0] == "RECEIPT"){
            string receiptId = serverOutputMessage[1].substr(serverOutputMessage[1].find(':'));
            cout << userData.getOutputMessage(receiptId) << endl;

        }
        else if(serverOutputMessage[0] == "ERROR"){
            string receiptId = serverOutputMessage[1].substr(serverOutputMessage[1].find(':'));
            userData.setLastReceiptId(receiptId);
            string errorMessage = serverOutputMessage[2].substr(serverOutputMessage[1].find(':'));
            cout << errorMessage << endl;
        }
        else if(serverOutputMessage[0] == "MESSAGE") {
            string subscription = serverOutputMessage[1].substr(serverOutputMessage[1].find(':'));
            string topic = serverOutputMessage[3].substr(serverOutputMessage[3].find(':'));
            string msgBody = serverOutputMessage[4].substr(serverOutputMessage[4].find(':'));
            messageExecutor(subscription,topic,msgBody);
        }




}


}

void serverHandler::messageExecutor(string subscription, string topic, string msgBody) {


}
// end of run










    }
}
