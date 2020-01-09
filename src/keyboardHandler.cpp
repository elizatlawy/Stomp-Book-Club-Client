//
// Created by zatlawy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <include/Book.h>
#include "keyboardHandler.h"

using namespace std;

keyboardHandler::keyboardHandler(ConnectionHandler &connectionHandler) : connectionHandler(&connectionHandler), userData(&connectionHandler.getUserData()) {}

void keyboardHandler::run() {
    cout << "enter input:" << endl;
    string lastUserInput;
    vector<string> userInputVector;
    // while user not logged in, he cant to do any command besides login
    while (!userData->isLoggedIn()) {
        getline(cin, lastUserInput);
        userInputVector = parseInput(lastUserInput);
        if (userInputVector[0] == "login") {
            string loginMsg = processLogin(userInputVector);
            sendMessage(loginMsg);
        }
        // user is now logged in
        while (userData->isLoggedIn()) {
            getline(cin, lastUserInput);
            userInputVector = parseInput(lastUserInput);
            if (userInputVector[0] == "join") {
                string joinMsg = processJoin(userInputVector);
                sendMessage(joinMsg);
            } else if (userInputVector[0] == "add") {
                string addMsg = processSubscribe(userInputVector);
                sendMessage(addMsg);
            } else if (userInputVector[0] == "exit") {
                string addMsg = processUnsubscribe(userInputVector);
                sendMessage(addMsg);
            } else if (userInputVector[0] == "borrow") {
                string borrowMsg = processBorrow(userInputVector);
                sendMessage(borrowMsg);
            } else if (userInputVector[0] == "return") {
                string returnMsg = processReturn(userInputVector);
                sendMessage(returnMsg);
            } else if (userInputVector[0] == "status") {
                string statusMsg = processStatus(userInputVector);
                sendMessage(statusMsg);
            }
        } // end of while
    }
}

string keyboardHandler::processLogin(vector<string> &userInputVector) {
    // set userName and password
    userData->setUserName(userInputVector[2]);
    userData->setUserPassword(userInputVector[3]);
    // decode msg
    string output = string("CONNECT") + '\n'
            + string("accept-version:1.2") + '\n'
            + string("host:stomp.cs.bg.ac.il") + '\n'
            + string ("login:") + userData->getUserName() +'\n'
            + string ("passcode:") + userData->getUserPassword() + '\n' + '\0' ;
    return output;
}

string keyboardHandler::processJoin(vector<string> &userInputVector){
    // add to actionLog
    string topic = userInputVector[1];
    string receiptId = to_string(userData->incrementAndGetReceiptCounter());
    string msg = "Joined club " + topic;
    userData->addToActionLog(receiptId, msg);
    // decode msg
    string subscriptionId = to_string(userData->incrementAndGetSubscriptionCounter());
    string output = string("SUBSCRIBE") + '\n'
                    + string("destination:") + topic + '\n'
                    + string("id:") + subscriptionId + '\n'
                    + string("receipt:") + receiptId + '\n' + '\0' ;
    return output;
}

string keyboardHandler::processSubscribe(vector<string> &userInputVector) {
// add to inventory
    string topic = userInputVector[1];
    string bookName = userInputVector[2];
    string userName = userData->getUserName();
    Book* currBook = new Book(bookName,userName,false);
    userData->addBook(topic, *currBook);
    // decode msg
    string msgBody = userName + " has added the book Foundation";
    string output = string("SEND") + '\n'
                    + string("destination:") + topic + '\n'
                    + msgBody + '\n' + '\0';
    return output;
}

string keyboardHandler::processUnsubscribe(vector<string> &userInputVector) {
    // add to actionLog
    string topic = userInputVector[1];
    string receiptId = to_string(userData->incrementAndGetReceiptCounter());
    string msg = "Exited club club " + topic;
    userData->addToActionLog(receiptId, msg);
    // decode msg
    string subscriptionId = to_string(userData->incrementAndGetSubscriptionCounter());
    string output = string("UNSUBSCRIBE") + '\n'
                    + string("id:") + subscriptionId + '\n'
                    + string("receipt:") + receiptId + '\n' + '\0' ;
    return output;
}

string keyboardHandler::processBorrow(vector<string> &userInputVector) {

}


string keyboardHandler::processReturn(vector<string> &userInputVector) {

}

string keyboardHandler::processStatus(vector<string> &userInputVector) {

}

void keyboardHandler::sendMessage(string msg) {
    connectionHandler->sendLine(msg);
}

vector<string> keyboardHandler::parseInput(string lastUserInput) {
    std::istringstream iss(lastUserInput);
    vector<string> results(istream_iterator<string>{iss},
                           istream_iterator<string>());
    return results;
};

