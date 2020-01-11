//
// Created by zatlawy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_USERDATA_H
#define BOOST_ECHO_CLIENT_USERDATA_H

#include <string>
#include <iostream>
#include <string>
#include <unordered_map>
#include "Book.h"

using namespace std;

class UserData {
public:
    UserData();

    const string &getUserName() const;

    const string &getUserPassword() const;

    void setUserName(const string &name);

    void setUserPassword(const string &password);

    bool isLoggedIn();

    void logIn();

    void logout();

    const string &getReceiptId() const;

    void setLastReceiptId(const string &receiptId);

    int incrementAndGetSubscriptionCounter();

    int incrementAndGetReceiptCounter();

    void addToActionLog(string receiptId,string msg);

    string getOutputMessage(string receiptId);

    void addBook (string topic, Book& book);

    bool isAvailableBook (string topic, const string& requestedBookName);
    void changeBookAvailability(string topic, const string& requestedBookName, bool status);

    const vector<string> &getWishList() const;
    void addToWishList(string bookName);
    void removeFromWishList(string bookName);

    string getDisconnectReceiptId() const;

    void setDisconnectReceiptId(string disconnectReceiptId);
    string listOfAvailableBooksByTopic(string topic);


    vector<string> parseInput ( string lastUserInput);

private:
    string userName;
    string userPassword;
    bool loggedIn;
    int subscriptionId;
    int receiptId;
    string disconnectReceiptId;
    unordered_map<string,string> actionLog; // key: receiptID value:  message to print
    unordered_map<string,vector<Book*>> inventory;
    vector<string> wishList; // vector of wished book names
};




#endif //BOOST_ECHO_CLIENT_USERDATA_H
