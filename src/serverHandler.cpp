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
    while (connectionHandler->isConnected()) {
        string message;
        connectionHandler->getLine(message);
        vector<std::string> serverOutputMessage = parseOutput(message);
        if (serverOutputMessage[0] == "CONNECTED") {
            userData->logIn();
            cout << "Login successful" << endl;
        } else if (serverOutputMessage[0] == "RECEIPT") {
            string receiptId = serverOutputMessage[1].substr(serverOutputMessage[1].find(':') + 1);
            // prints to the screen
            // if it is the answer of the disconnect message logout
            if (receiptId == userData->getDisconnectReceiptId())
                userData->logout();
            if(userData->getCommandType(receiptId) == "SUBSCRIBE"){
                // todo add the subscription to map
            }
            cout << userData->getOutputMessage(receiptId) << endl;

        } else if (serverOutputMessage[0] == "ERROR") {
            string receiptId = serverOutputMessage[1].substr(serverOutputMessage[1].find(':') + 1);
            userData->setLastReceiptId(receiptId);
            string errorMessage = serverOutputMessage[2].substr(serverOutputMessage[1].find(':') + 1);
            cout << errorMessage << endl;
        } else if (serverOutputMessage[0] == "MESSAGE") {
            string subscription = serverOutputMessage[1].substr(serverOutputMessage[1].find(':') + 1);
            string topic = serverOutputMessage[3].substr(serverOutputMessage[3].find(':') + 1);
            string msgBody = serverOutputMessage[4].substr(serverOutputMessage[4].find(':') + 1);
            messageExecutor(subscription, topic, msgBody);
        }
    }


}

void serverHandler::messageExecutor(string subscription, string topic, string msgBody) {
    // TODO: check if +1 is needed to the position
    string bookName;
    // message type is wish to borrow
    if (msgBody.find("wish to borrow") != string::npos) {
        bookName = msgBody.substr(msgBody.find_last_of(' ') + 1);
        if (userData->isAvailableBook(topic, bookName)) { // if the user have the requested Book
            string msg = string("SEND") + '\n'
                         + string("destination:") + topic + '\n'
                         + userData->getUserName() + (" ") + string("has ") + bookName + '\n' + '\0';
            sendMessage(msg);
        }
    } // end of wish
    // message type is {User} has {bookName}
    if (msgBody.find(" has ") != string::npos) {
        bookName = msgBody.substr(msgBody.find_last_of(' ') + 1);
        // check if I wish to have this book
        vector<string> wishList = userData->getWishList();
        auto result = std::find(std::begin(wishList), std::end(wishList), bookName);
        if (result != std::end(wishList)) {// the book is found in the wishList
            string senderName = msgBody.substr(0, msgBody.find(' '));
            string msg = string("SEND") + '\n'
                         + string("destination:") + topic + '\n'
                         + string("Taking") + bookName + string("from") + senderName + '\n' + '\0';
            Book *borrowedBook = new Book(bookName, senderName, true);
            userData->addBook(topic, *borrowedBook);
            userData->removeFromWishList(bookName);

            sendMessage(msg);
        }
    } // end of has
    if (msgBody.find("Returning") != string::npos) {
        string toReturnName = msgBody.substr(msgBody.find_last_of(' ') + 1);
        // if the some want to return the book to me
        if (toReturnName == userData->getUserName()) {
            bookName = msgBody.substr(msgBody.find(' ') + 1);
            // but the book back to my inventory.
            userData->changeBookAvailability(topic, bookName, true);
            // TODO: check if need to return the book all the way to the starter
        } // end of Returning
        if (msgBody.find("book status") != string::npos) {
            string bookList = userData->listOfAvailableBooksByTopic(topic);
            // if the list is not empty
            if (bookList != "") {
                string msg = string("SEND") + '\n'
                             + string("destination:") + topic + '\n'
                             + userData->getUserName() + (":") + bookList + '\n' + '\0';
            }
        } // end of book status


    } // end of messageExecutor
}


    void serverHandler::sendMessage(string msg) {
        connectionHandler->sendLine(msg);
    }

vector<string> serverHandler::parseOutput(string lastUserInput) {
    std::stringstream ss(lastUserInput);
    std::string line;
    vector<string> results;
        while(std::getline(ss,line,'\n')){
            results.push_back(line);
        }
    return results;
}












