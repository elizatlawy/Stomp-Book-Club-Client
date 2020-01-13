
#include <string>
#include <iostream>
#include <vector>
#include <include/Book.h>
#include "keyboardHandler.h"
#include <thread>
#include "serverHandler.h"

using namespace std;

keyboardHandler::keyboardHandler(){}

void keyboardHandler::run() {
    cout << "enter input:" << endl;
    vector<string> userInputVector;
    userData = new UserData;
    // while user not logged in, he cant to do any command besides login
    bool flag = true;
    while (flag) {
        while (!userData->isLoggedIn()) {
            string lastUserInput;
            getline(cin, lastUserInput);
            userInputVector = parseBySpace(lastUserInput);
            if (userInputVector[0] == "login") {
                if (establishConnection(userInputVector)) {
                    string loginMsg = processLogin(userInputVector);
                    sendMessage(loginMsg);
//                    unique_lock<std::mutex> lk(_mutex);
//                    cv.wait(lk, [this]{return userData->isLoginLock();});
                        // TODO: FIX IT
                    while(!userData->isLoggedIn()){}

                } else
                    cout << "Could not connect to the server" << endl;
            }
            else
                cout << "you are not logged in, please login first" << endl;
        } // end of first while
        // user is now logged in
        while (userData->isLoggedIn()) {
            string lastUserInput;
            getline(cin, lastUserInput);
            userInputVector = parseBySpace(lastUserInput);
            if (userInputVector[0] == "login") {
                string loginMsg = processLogin(userInputVector);
                sendMessage(loginMsg);
            } else if (userInputVector[0] == "join") {
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
        serverHandlerThread->join();
        cout << "you have been DISCONNECTED, bye bye..." << endl;
    }
}


bool keyboardHandler::establishConnection(vector<string> &userInputVector) {
    // create Connection Handler
    string input = userInputVector[1];
    string host = input.substr(0, input.find(':'));
    int port = stoi(input.substr(input.find(':') + 1, input.size()));
    connectionHandler = new ConnectionHandler(host, short(port));
    if (connectionHandler->connect()) {
        // create serverHandler thread
        serverHandler *serverHandler_ = new serverHandler(*connectionHandler, *userData);
        serverHandlerThread = new thread(&serverHandler::run, *serverHandler_);
        return true;
    }
    return false;
}

string keyboardHandler::processLogin(vector<string> &userInputVector) {
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
    userData->addToActionLog(receiptId, msg);
    // decode msg
    string subscriptionId = to_string(userData->incrementAndGetSubscriptionCounter());
    userData->addActiveSubscription(topic,subscriptionId);
    string output = string("SUBSCRIBE") + '\n'
                    + string("destination:") + topic + '\n'
                    + string("id:") + subscriptionId + '\n'
                    + string("receipt:") + receiptId + '\n' + '\0';
    return output;
}

string keyboardHandler::processAdd(vector<string> &userInputVector) {
// add to inventory
    string topic = userInputVector[1];
    string bookName = createBookName(userInputVector);
    string userName = userData->getUserName();
    Book *currBook = new Book(bookName, userName, true);
    userData->addBook(topic, *currBook);
    // decode msg
    string msgBody = userName + " has added the book " + bookName;
    string output = string("SEND") + '\n'
                    + string("destination:") + topic + '\n' + '\n'
                    + msgBody + '\n' + '\0';
    return output;
}

string keyboardHandler::processExit(vector<string> &userInputVector) {
    // add to actionLog
    string topic = userInputVector[1];
    string receiptId = to_string(userData->incrementAndGetReceiptCounter());
    string msg = "Exited club " + topic;
    userData->addToActionLog(receiptId, msg);
    // decode msg
    string subscriptionId = userData->getActiveSubscriptionId(topic);
    string output = string("UNSUBSCRIBE") + '\n'
                    + string("id:") + subscriptionId + '\n'
                    + string("receipt:") + receiptId + '\n' + '\0';
    return output;
}

string keyboardHandler::processBorrow(vector<string> &userInputVector) {
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
    return output;

}

string keyboardHandler::processReturn(vector<string> &userInputVector) {
    // decode msg
    string topic = userInputVector[1];
    string bookName = createBookName(userInputVector);
    string userName = userData->getUserName();
    string msgBody = "Returning " + bookName + " to " + userName;
    string output = string("SEND") + '\n'
                    + string("destination:") + topic + '\n' + '\n'
                    + msgBody + '\n' + '\0';
    return output;

}

string keyboardHandler::processStatus(vector<string> &userInputVector) {
    // decode msg
    string topic = userInputVector[1];
    string msgBody = "book status";
    string output = string("SEND") + '\n'
                    + string("destination:") + topic + '\n' + '\n'
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
    connectionHandler->sendLine(msg, '\n');
}

vector<string> keyboardHandler::parseBySpace(string lastUserInput) {
    std::istringstream iss(lastUserInput);
    vector<string> results(istream_iterator<string>{iss},
                           istream_iterator<string>());
    return results;
};

string keyboardHandler::createBookName(vector<string> &userInputVector) {
    string bookName = "";
    for (int i = 2 ; i < userInputVector.size() ; i++){
        bookName = string(bookName) + string(userInputVector[i]) + string( " ");
    }
    bookName = bookName.substr(0, bookName.length()-1);
    return bookName;
}
