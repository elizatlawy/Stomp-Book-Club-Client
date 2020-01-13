
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <include/Book.h>
#include "serverHandler.h"


using namespace std;

serverHandler::serverHandler(ConnectionHandler &connectionHandler, UserData &userData) : connectionHandler(
        &connectionHandler), userData(&userData) {}

void serverHandler::run() {
    while (connectionHandler->isConnected()) {
        // TODO: MAKE ALL IF AS FUNCTIONS
        string message;
        string topic;
        connectionHandler->getLine(message, '\0');
        vector<std::string> serverOutputMessage = parseByLine(message);
        if (serverOutputMessage[0] == "CONNECTED") {
            userData->logIn();
            userData->setLoginLock(false);
            cout << "Login successful" << endl;
        } else if (serverOutputMessage[0] == "RECEIPT") {
            string receiptId = serverOutputMessage[1].substr(serverOutputMessage[1].find(':') + 1);
            // prints to the screen
            // if it is the answer of the disconnect message logout
            if (receiptId == userData->getDisconnectReceiptId()) {
                userData->setLoginLock(false);
                userData->logout();
                userData->setLogOutLock(false);
                // TODO: check if needed
                connectionHandler->close();
            } else if (userData->getCommand(receiptId) == "SUBSCRIBE") {
                cout << string("Joined club ") + userData->getSubscriptionLogById(receiptId) << endl;
            } else { // the command "UNSUBSCRIBE"
                topic = userData->getSubscriptionLogById(receiptId);
                cout << string("Exited club ") + topic << endl;
                userData->removeSubscriptionsLogByTopic(topic);
                userData->removeSubscriptionLogById(receiptId);
            }
        } else if (serverOutputMessage[0] == "ERROR") {
            userData->setLoginLock(false);
            userData->logout();
            //string receiptId = serverOutputMessage[1].substr(serverOutputMessage[1].find(':') + 1);
            string errorMessage = serverOutputMessage[2].substr(serverOutputMessage[1].find(':') - 1);
            cout << errorMessage << endl;
        } else if (serverOutputMessage[0] == "MESSAGE") {
            string msgBody = serverOutputMessage[5];
            cout << string("Client Received MESSAGE from Server: " + msgBody) << endl;
            topic = serverOutputMessage[3].substr(serverOutputMessage[3].find(':') + 1);

            messageExecutor(topic, msgBody);
        }
    }

}

void serverHandler::messageExecutor(string topic, string msgBody) {
    // message type is wish to borrow
    if (msgBody.find("wish to borrow") != string::npos) {
        cout << "Client STARTED process: " + msgBody << endl;
        wishBookExecutor(topic, msgBody);
        cout << "Client FINISHED process: " + msgBody << endl;

    }
        // message type is {User} has {bookName} or  {User} has added the book
    else if (msgBody.find(" has ") != string::npos) {
        cout << "Client STARTED process:" + msgBody << endl;
        hasBookExecutor(topic, msgBody);
        cout << "Client FINISHED process:" + msgBody << endl;
    } else if (msgBody.find(" Taking ") != string::npos) {
        cout << "Client STARTED process:" + msgBody << endl;
        takeBookExecutor(topic, msgBody);
        cout << "Client FINISHED process:" + msgBody << endl;
    } else if (msgBody.find("Returning") != string::npos) {
        cout << "Client STARTED process:" + msgBody << endl;
        returnBookExecutor(topic, msgBody);
        cout << "Client FINISHED process: " + msgBody << endl;
    } else if (msgBody.find("book status") != string::npos) {
        cout << "Client STARTED process: " + msgBody << endl;
        bookStatusExecutor(topic);
        cout << "Client FINISHED process: " + msgBody << endl;
    }
        // TODO: delete this before submission
        // else this is the  book status of other users message
    else
        cout << msgBody << endl;
} // end of messageExecutor


void serverHandler::wishBookExecutor(string topic, string msgBody) {
    string bookName = msgBody.substr(msgBody.find_last_of(' ') + 1);
    if (userData->isAvailableBook(topic, bookName)) { // if the user have the requested Book
        string msg = string("SEND") + '\n'
                     + string("destination:") + topic + '\n' + '\n'
                     + userData->getUserName() + (" ") + string("has ") + bookName + '\n' + '\0';
        sendMessage(msg);
    }
}

void serverHandler::hasBookExecutor(string topic, string msgBody) {
    string bookName = msgBody.substr(msgBody.find_last_of(' ') + 1);
    // check if I wish to have this book
    vector<string> wishList = userData->getWishList();
    auto result = std::find(std::begin(wishList), std::end(wishList), bookName);
    if (result != std::end(wishList)) {// the book is found in the wishList
        string senderName = msgBody.substr(0, msgBody.find(' '));
        string msg = string("SEND") + '\n'
                     + string("destination:") + topic + '\n' + '\n'
                     + string("Taking ") + bookName + string(" from ") + senderName + '\n' + '\0';
        Book *borrowedBook = new Book(bookName, senderName, true);
        userData->addBook(topic, *borrowedBook);
        userData->removeFromWishList(bookName);
        sendMessage(msg);
    }
}

// TODO: handle the case of long book name with spaces
void serverHandler::takeBookExecutor(string topic, string msgBody) {
    string toTakeFromName = msgBody.substr(msgBody.find_last_of(' ') + 1);
    if (toTakeFromName == userData->getUserName()) {
        int end = msgBody.find("from");
        string bookName = msgBody.substr(7, end - 8);
        userData->changeBookAvailability(topic, bookName, false);
    }
}

void serverHandler::returnBookExecutor(string topic, string msgBody) {
    string toReturnName = msgBody.substr(msgBody.find_last_of(' ') + 1);
    // if the some want to return the book to me
    if (toReturnName == userData->getUserName()) {
        int end = msgBody.find("to");
        int start = msgBody.find("Returning");
        string bookName = msgBody.substr(10, end - start - 11);
        // but the book back to my inventory.
        userData->changeBookAvailability(topic, bookName, true);
    }
}

void serverHandler::bookStatusExecutor(string topic) {
    string bookList = userData->listOfAvailableBooksByTopic(topic);
    // send the message
    string msg = string("SEND") + '\n'
                 + string("destination:") + topic + '\n' + '\n'
                 + userData->getUserName() + (":") + bookList + '\n' + '\0';
    sendMessage(msg);
}


void serverHandler::sendMessage(string msg) {
    connectionHandler->sendLine(msg, '\n');
}

vector<string> serverHandler::parseByLine(string message) {
    std::stringstream ss(message);
    std::string line;
    vector<string> results;
    while (std::getline(ss, line, '\n')) {
        results.push_back(line);
    }
    return results;
}


vector<string> serverHandler::parseBySpace(string message) {
    std::istringstream iss(message);
    vector<string> results(istream_iterator<string>{iss},
                           istream_iterator<string>());
    return results;
}














