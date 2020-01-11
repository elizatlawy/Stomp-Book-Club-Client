
#include <string>
#include <iostream>
#include <vector>
#include <include/Book.h>
#include "keyboardHandler.h"
#include <thread>
#include "serverHandler.h"

using namespace std;

keyboardHandler::keyboardHandler() : userData() {}

void keyboardHandler::operator()() {
    cout << "enter input:" << endl;
    string lastUserInput;
    vector<string> userInputVector;
    // while user not logged in, he cant to do any command besides login
    bool flag = true;
    while (flag) {
        while (!userData->isLoggedIn()) {
            getline(cin, lastUserInput);
            userInputVector = parseInput(lastUserInput);
            if (userInputVector[0] == "login") {
                string loginMsg = processLogin(userInputVector);
                if (loginMsg != "failToConnect")
                    sendMessage(loginMsg);
                else
                   cout << "Could not connect to the server" << endl;
            }
            // user is now logged in
            while (userData->isLoggedIn()) {
                getline(cin, lastUserInput);
                userInputVector = parseInput(lastUserInput);
                if (userInputVector[0] == "join") {
                    string joinMsg = processJoin(userInputVector);
                    sendMessage(joinMsg);
                } else if (userInputVector[0] == "add") {
                    string addMsg = processAdd(userInputVector);
                    sendMessage(addMsg);
                } else if (userInputVector[0] == "exit") {
                    string addMsg = processExit(userInputVector);
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
                } else if (userInputVector[0] == "logout") {
                    string logoutMsg = processLogOut();
                    sendMessage(logoutMsg);
                }
            }
        }
    }
}

string keyboardHandler::processLogin(vector<string> &userInputVector) {
    // create Connection Handler
    string input = userInputVector[1];
    string host = input.substr(0, input.find(':'));
    int port = stoi(input.substr(input.find(':') + 1, input.size()));
    connectionHandler = new ConnectionHandler(host, short(port));
    if (!connectionHandler->connect()) {
        return "failToConnect";
    }
    // create serverHandler thread
    serverHandler *server_Handler = new serverHandler(*connectionHandler, *userData);
    thread t2(std::ref(server_Handler));
    // set userName and password
    userData->setUserName(userInputVector[2]);
    userData->setUserPassword(userInputVector[3]);
    // decode msg
    string output = string("CONNECT") + '\n'
                    + string("accept-version:1.2") + '\n'
                    + string("host:stomp.cs.bg.ac.il") + '\n'
                    + string("login:") + userData->getUserName() + '\n'
                    + string("passcode:") + userData->getUserPassword() + '\n' + '\0';
    return output;
}




string keyboardHandler::processJoin(vector<string> &userInputVector) {
    // add to actionLog
    string topic = userInputVector[1];
    string receiptId = to_string(userData->incrementAndGetReceiptCounter());
    string msg = "Joined club " + topic;
    userData->addToActionLog(receiptId,msg);
    // decode msg
    string subscriptionId = to_string(userData->incrementAndGetSubscriptionCounter());
    string output = string("SUBSCRIBE") + '\n'
                    + string("destination:") + topic + '\n'
                    + string("id:") + subscriptionId + '\n'
                    + string("receipt:") + receiptId + '\n' + '\0';
    return output;
}

string keyboardHandler::processAdd(vector<string> &userInputVector) {
// add to inventory
    string topic = userInputVector[1];
    string bookName = userInputVector[2];
    string userName = userData->getUserName();
    Book *currBook = new Book(bookName, userName, true);
    userData->addBook(topic, *currBook);
    // decode msg
    string msgBody = userName + " has added the book Foundation";
    string output = string("SEND") + '\n'
                    + string("destination:") + topic + '\n'
                    + msgBody + '\n' + '\0';
    return output;
}

string keyboardHandler::processExit(vector<string> &userInputVector) {
    // add to actionLog
    string topic = userInputVector[1];
    string receiptId = to_string(userData->incrementAndGetReceiptCounter());
    string msg = "Exited club " + topic;
    userData->addToActionLog(receiptId,msg);
    // decode msg
    string subscriptionId = to_string(userData->incrementAndGetSubscriptionCounter());
    string output = string("UNSUBSCRIBE") + '\n'
                    + string("id:") + subscriptionId + '\n'
                    + string("receipt:") + receiptId + '\n' + '\0';
    return output;
}

string keyboardHandler::processBorrow(vector<string> &userInputVector) {
    // add to user wish list
    string bookName = userInputVector[2];
    userData->addToWishList(bookName);
    // decode msg
    string topic = userInputVector[1];
    string userName = userData->getUserName();
    string msgBody = userName + " wish to borrow " + bookName;
    string output = string("SEND") + '\n'
                    + string("destination:") + topic + '\n'
                    + msgBody + '\n' + '\0';
    return output;

}

string keyboardHandler::processReturn(vector<string> &userInputVector) {
    // decode msg
    string topic = userInputVector[1];
    string bookName = userInputVector[2];
    string userName = userData->getUserName();
    string msgBody = "Returning " + bookName + " to " + userName;
    string output = string("SEND") + '\n'
                    + string("destination:") + topic + '\n'
                    + msgBody + '\n' + '\0';
    return output;

}

string keyboardHandler::processStatus(vector<string> &userInputVector) {
    // decode msg
    string topic = userInputVector[1];
    string msgBody = "book status";
    string output = string("SEND") + '\n'
                    + string("destination:") + topic + '\n'
                    + msgBody + '\n' + '\0';
    return output;
}

string keyboardHandler::processLogOut() {
    // decode msg
    string receiptId = to_string(userData->incrementAndGetReceiptCounter());
    userData->setDisconnectReceiptId(receiptId);
    string output = string("DISCONNECT") + '\n'
                    + string("receipt:") + receiptId + '\n' + '\0';
    return output;
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
