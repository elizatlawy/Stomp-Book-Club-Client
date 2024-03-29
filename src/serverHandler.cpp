
#include <string>
#include <iostream>
#include <vector>
#include <Book.h>
#include <sstream>
#include "serverHandler.h"


using namespace std;

serverHandler::serverHandler(ConnectionHandler &connectionHandler, UserData &userData) : connectionHandler(
        &connectionHandler), userData(&userData) {}

// copy constructor
serverHandler::serverHandler(const serverHandler &other) : connectionHandler(), userData() {
    connectionHandler = other.connectionHandler;
    userData = other.userData;
}

// copy assignment
serverHandler &serverHandler::operator=(const serverHandler &other) {
    // check for self assignment
    if (this == &other)
        return *this;
    // first destroy old resources
    delete connectionHandler;
    delete userData;
    // copy resources of other
    connectionHandler = other.connectionHandler;
    userData = other.userData;
    return *this;
}

// destructor
serverHandler::~serverHandler() {}


void serverHandler::run() {
    while (connectionHandler->isConnected()) {
        string message;
        if (!connectionHandler->getLine(message)) {
            std::cout << "Failed to get answer form server, connection lost" << std::endl;
            connectionHandler->close();
            userData->logout();
            userData->setLogOutLock(false);
            break;
        }
        if (message.length() > 0) {
            vector<std::string> serverOutputMessage = parseByLine(message);
            if (serverOutputMessage[0] == "CONNECTED") {
                handleConnectedFrame();
            } else if (serverOutputMessage[0] == "RECEIPT") {
                string receiptId = serverOutputMessage[1].substr(serverOutputMessage[1].find(':') + 1);
                handleReceiptFrame(receiptId);
            } else if (serverOutputMessage[0] == "ERROR") {
                string errorMessage = serverOutputMessage[2].substr(serverOutputMessage[1].find(':') - 1);
                handleErrorFrame(errorMessage);
            } else if (serverOutputMessage[0] == "MESSAGE") {
                string msgBody = serverOutputMessage[5];
                string topic = serverOutputMessage[3].substr(serverOutputMessage[3].find(':') + 1);
                cout << string(topic + ":" + msgBody) << endl;
                handleMessageFrame(topic, msgBody);
            }
        }
    }
}

void serverHandler::handleMessageFrame(string topic, string msgBody) {

    if (msgBody.find("wish to borrow") != string::npos) {
        wishBookExecutor(topic, msgBody);
    } else if (msgBody.find("Taking") != string::npos) {
        takeBookExecutor(topic, msgBody);
    } else if (msgBody.find("Returning") != string::npos) {
        returnBookExecutor(topic, msgBody);
    } else if (msgBody.find("book status") != string::npos) {
        bookStatusExecutor(topic);
    } else if (msgBody.find("has added") == string::npos) {
        // handle message type is {User} has {bookName}
        hasBookExecutor(topic, msgBody);
    }
} // end of handleMessageFrame

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

void serverHandler::handleConnectedFrame() {
    userData->logIn();
    userData->setLoginLock(false);
    cout << "Login successful" << endl;
}

void serverHandler::handleReceiptFrame(string receiptId) {
    if (receiptId == userData->getDisconnectReceiptId()) {
        connectionHandler->close();
        userData->logout();
        userData->setLogOutLock(false);
        //delete connectionHandler;
    } else if (userData->getCommand(receiptId) == "SUBSCRIBE") {
        cout << string("Joined club ") + userData->getSubscriptionLogById(receiptId) << endl;
    } else { // the command "UNSUBSCRIBE"
        string topic = userData->getSubscriptionLogById(receiptId);
        cout << string("Exited club ") + topic << endl;
        userData->removeSubscriptionsLogByTopic(topic);
        userData->removeSubscriptionLogById(receiptId);
    }
}

void serverHandler::handleErrorFrame(string errorMessage) {
    connectionHandler->close();
    //delete connectionHandler;
    userData->logout();
    cout << errorMessage << endl;
    userData->setLogOutLock(false);
    userData->setLoginLock(false);
}

void serverHandler::sendMessage(string msg) {
    if (!connectionHandler->sendLine(msg)) {
        connectionHandler->close();
        userData->logout();
        userData->setLogOutLock(false);
        std::cout << "Failed to send message, connection lost" << std::endl;
    }
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






















