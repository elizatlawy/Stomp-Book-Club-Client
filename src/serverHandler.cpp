//
// Created by zatlawy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#include <include/serverHandler.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <include/Book.h>
#include "serverHandler.h"
using namespace std;

serverHandler::serverHandler(ConnectionHandler &connectionHandler) : connectionHandler(&connectionHandler),
                                                                     userData(&connectionHandler.getUserData()) {

}

void serverHandler::run() {
    while (connectionHandler->isConnected()){
        string message;
        connectionHandler->getLine(message);
        std::istringstream iss(message);
        std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                         std::istream_iterator<std::string>());
        vector<std::string> serverOutputMessage = results;
        if(serverOutputMessage[0] == "CONNECTED"){
            userData->logIn();
            cout << "Login successful" << endl;
        }
        else if(serverOutputMessage[0] == "RECEIPT"){
            string receiptId = serverOutputMessage[1].substr(serverOutputMessage[1].find(':') + 1);
            // prints to the screen
            cout << userData->getOutputMessage(receiptId) << endl;

        }
        else if(serverOutputMessage[0] == "ERROR"){
            string receiptId = serverOutputMessage[1].substr(serverOutputMessage[1].find(':') + 1);
            userData->setLastReceiptId(receiptId);
            string errorMessage = serverOutputMessage[2].substr(serverOutputMessage[1].find(':') + 1);
            cout << errorMessage << endl;
        }
        else if(serverOutputMessage[0] == "MESSAGE") {
            string subscription = serverOutputMessage[1].substr(serverOutputMessage[1].find(':') + 1);
            string topic = serverOutputMessage[3].substr(serverOutputMessage[3].find(':') + 1);
            string msgBody = serverOutputMessage[4].substr(serverOutputMessage[4].find(':') + 1);
            messageExecutor(subscription,topic,msgBody);
        }
}


}

void serverHandler::messageExecutor(string subscription, string topic, string msgBody) {
    // TODO: check if +1 is needed to the position
    string bookName = msgBody.substr(msgBody.find_last_of(' ') + 1);
    // message type is wish to borrow
    if (msgBody.find("wish to borrow") != string::npos) {
        if (userData->isAvailableBook(topic,bookName)) { // if the user have the requested Book
            string output = string("SEND") + '\n'
                            + string("destination:") + topic + '\n'
                            + userData->getUserName()+ (" ") + string("has ") + bookName + '\n' + '\0';
        }
    } // end of wish
    // message type is {User} has {bookName}
    if (msgBody.find(" has ") != string::npos) {

        // check if I wish to have this book
        vector<string> wishList = userData->getWishList();
        auto result =  std::find(std::begin(wishList), std::end(wishList), bookName);
        if(result != std::end(wishList)){  // the book is found in the wishList


    } // end of
}

void serverHandler::sendMessage(string msg) {
    connectionHandler->sendLine(msg);
}


// end of run



->





    }
}
