
#include <string>
#include <iostream>
#include <vector>
#include <Book.h>
#include "keyboardHandler.h"
#include <thread>
#include <sstream>
#include "serverHandler.h"

using namespace std;

keyboardHandler::keyboardHandler(): connectionHandler(), userData(), serverHandlerThread(), serverHandler_() {
    connectionHandler = new ConnectionHandler();
    userData = new UserData;
    serverHandler_  = new serverHandler(*connectionHandler, *userData);
    serverHandlerThread = new thread(&serverHandler::run, *serverHandler_);
}

// copy constructor
keyboardHandler::keyboardHandler(const keyboardHandler &other): connectionHandler(), userData(), serverHandlerThread(), serverHandler_() {
    connectionHandler = other.connectionHandler;
    userData = other.userData;
}
// copy assignment
keyboardHandler &keyboardHandler::operator=(const keyboardHandler &other) {
    // check for self assignment
    if (this == &other)
        return  *this;
    // first destroy old resources
    delete connectionHandler;
    delete  userData;
    // copy resources of other
    connectionHandler = other.connectionHandler;
    userData = other.userData;
    return *this;
}



// destructor
keyboardHandler::~keyboardHandler() {

    serverHandlerThread->join();
    delete serverHandlerThread;
    delete serverHandler_;
    delete connectionHandler;
    delete userData;
}

void keyboardHandler::run() {
    cout << "enter input:" << endl;
    vector<string> userInputVector;
    // while user not logged in, he cant to do any command besides login
    bool bye = false;
    while (!bye) {
        while (!userData->isLoggedIn() && !bye) {
            userData->setLoginLock(true);
            string lastUserInput;
            getline(cin, lastUserInput);
            userInputVector = parseBySpace(lastUserInput);
            if (userInputVector[0] == "login") {
                if (establishConnection(userInputVector)) {
                    processLogin(userInputVector);
                    while (userData->isLoginLock()) {}
                } else
                    cout << "Could not connect to server" << endl;
            } else if (userInputVector[0] == "bye") {
                bye = true;
            } else
                cout << "you are not logged in, please login first" << endl;
        } // end of first while
        // user is now logged in
        while (userData->isLoggedIn()) {
            string lastUserInput;
            getline(cin, lastUserInput);
            userInputVector = parseBySpace(lastUserInput);
            if (userInputVector[0] == "login") {
                processLogin(userInputVector);
                userData->setLogOutLock(true);
            } else if (userInputVector[0] == "join") {
                processJoin(userInputVector);
            } else if (userInputVector[0] == "add") {
                processAdd(userInputVector);
            } else if (userInputVector[0] == "exit") {
                processExit(userInputVector);
            } else if (userInputVector[0] == "borrow") {
                processBorrow(userInputVector);
            } else if (userInputVector[0] == "return") {
                processReturn(userInputVector);
            } else if (userInputVector[0] == "status") {
                processStatus(userInputVector);
            } else if (userInputVector[0] == "logout") {
                processLogOut();
                userData->setLogOutLock(true);
            } else if (userInputVector[0] == "bye") {
                if (userData->isLoggedIn())
                    cout << "in order to exit the program, please logout first" << endl;
                else
                    bye = true;
            }
            while (userData->isLogOutLock()) {}
        }
        cout << "you have been DISCONNECTED, bye bye..." << endl;
    }
}

bool keyboardHandler::establishConnection(vector<string> &userInputVector) {
    // create Connection Handler
    string input = userInputVector[1];
    string host = input.substr(0, input.find(':'));
    int port = stoi(input.substr(input.find(':') + 1, input.size()));
    if (connectionHandler->connect(host, short(port))) {
        // create serverHandler thread
        serverHandlerThread->join();
        delete serverHandlerThread;
        serverHandlerThread = new thread(&serverHandler::run, *serverHandler_);
        return true;
    }
    return false;
}

void keyboardHandler::processLogin(vector<string> &userInputVector) {
    // set userName and password
    userData->setUserName(userInputVector[2]);
    userData->setUserPassword(userInputVector[3]);
    // decode msg
    string output = string("CONNECT") + '\n'
                    + string("accept-version:1.2") + '\n'
                    + string("host:stomp.cs.bg.ac.il") + '\n'
                    + string("login:") + userData->getUserName() + '\n'
                    + string("passcode:") + userData->getUserPassword() + '\n' + '\0';
    sendMessage(output);
}

void keyboardHandler::processJoin(vector<string> &userInputVector) {
    // add to subscriptionsLogById
    string topic = userInputVector[1];
    if (!userData->isSubscribed(topic)) {
        string receiptId = to_string(userData->incrementAndGetReceiptCounter());
        string subscriptionId = to_string(userData->incrementAndGetSubscriptionCounter());
        userData->addSubscriptionLogById(receiptId, topic);
        userData->addCommandLog(receiptId, "SUBSCRIBE");
        userData->addSubscriptionsLogByTopic(topic, subscriptionId);
        userData->addTopic(topic);
        // decode msg
        string output = string("SUBSCRIBE") + '\n'
                        + string("destination:") + topic + '\n'
                        + string("id:") + subscriptionId + '\n'
                        + string("receipt:") + receiptId + '\n' + '\0';
        sendMessage(output);
    } else
        cout << "you are already subscribed to this topic" << endl;
}

void keyboardHandler::processAdd(vector<string> &userInputVector) {
// add to inventory
    string topic = userInputVector[1];
    string bookName = createBookName(userInputVector);
    if (!userData->isAvailableBook(topic, bookName)) {
        string userName = userData->getUserName();
        Book *currBook = new Book(bookName, userName, true);
        userData->addBook(topic, *currBook);
        // decode msg
        string msgBody = userName + " has added the book " + bookName;
        string output = string("SEND") + '\n'
                        + string("destination:") + topic + '\n' + '\n'
                        + msgBody + '\n' + '\0';
        sendMessage(output);
    }
}

void keyboardHandler::processExit(vector<string> &userInputVector) {
    // add to subscriptionsLogById
    string topic = userInputVector[1];
    string receiptId = to_string(userData->incrementAndGetReceiptCounter());
    string subscriptionId = userData->getSubscriptionsLogByTopic(topic);

    userData->addSubscriptionLogById(receiptId, topic);
    userData->addCommandLog(receiptId, "UNSUBSCRIBE");
    // decode msg
    string output = string("UNSUBSCRIBE") + '\n'
                    + string("id:") + subscriptionId + '\n'
                    + string("receipt:") + receiptId + '\n' + '\0';
    sendMessage(output);
}

void keyboardHandler::processBorrow(vector<string> &userInputVector) {
    // add to user wish list
    string bookName = createBookName(userInputVector);
    userData->addToWishList(bookName);
    // decode msg
    string topic = userInputVector[1];
    string userName = userData->getUserName();
    string msgBody = userName + " wish to borrow " + bookName;
    string output = string("SEND") + '\n'
                    + string("destination:") + topic + '\n' + '\n'
                    + msgBody + '\n' + '\0';
    sendMessage(output);
}

void keyboardHandler::processReturn(vector<string> &userInputVector) {
    // decode msg
    string topic = userInputVector[1];
    string bookName = createBookName(userInputVector);
    if (userData->isAvailableBook(topic, bookName)) {
        string ownerName = userData->getBookOwner(topic, bookName);
        string msgBody = "Returning " + bookName + " to " + ownerName;
        string output = string("SEND") + '\n'
                        + string("destination:") + topic + '\n' + '\n'
                        + msgBody + '\n' + '\0';
        sendMessage(output);
        userData->changeBookAvailability(topic, bookName, false);
    }
}

void keyboardHandler::processStatus(vector<string> &userInputVector) {
    // decode msg
    string topic = userInputVector[1];
    string msgBody = "book status";
    string output = string("SEND") + '\n'
                    + string("destination:") + topic + '\n' + '\n'
                    + msgBody + '\n' + '\0';
    sendMessage(output);
}

void keyboardHandler::processLogOut() {
    // decode msg
    string receiptId = to_string(userData->incrementAndGetReceiptCounter());
    userData->setDisconnectReceiptId(receiptId);
    string output = string("DISCONNECT") + '\n'
                    + string("receipt:") + receiptId + '\n' + '\0';
    sendMessage(output);
}

void keyboardHandler::sendMessage(string msg) {
    if (!connectionHandler->sendLine(msg)) {
        connectionHandler->close();
        userData->logout();
        userData->setLogOutLock(false);
        std::cout << "Failed to send message, connection lost" << std::endl;
    }
}

vector<string> keyboardHandler::parseBySpace(string lastUserInput) {
    std::istringstream iss(lastUserInput);
    vector<string> results(istream_iterator<string>{iss},
                           istream_iterator<string>());
    return results;
};

string keyboardHandler::createBookName(vector<string> &userInputVector) {
    string bookName;
    for (int i = 2; (unsigned)i < userInputVector.size(); i++) {
        bookName = string(bookName) + string(userInputVector[i]) + string(" ");
    }
    bookName = bookName.substr(0, bookName.length() - 1);
    return bookName;
}




