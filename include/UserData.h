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
    UserData(); // constructor

    virtual ~UserData();

    const string &getUserName() const;

    const string &getUserPassword() const;

    void setUserName(const string &name);
    void setUserPassword(const string &password);
    bool isLoggedIn();
    void logIn();
    void logout();
    int incrementAndGetSubscriptionCounter();
    int incrementAndGetReceiptCounter();
    void addToActionLog(string receiptId, string msg);
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

    bool isLoginLock() const;

    void setLoginLock(bool loginLock);


private:
    string userName;
    string userPassword;
    bool loggedIn;
    int subscriptionId;
    int receiptId;
    bool loginLock = false;
    string disconnectReceiptId;
    unordered_map<string,string> actionLog;
    unordered_map<std::string,std::vector<Book*>> inventory;
    vector<string> wishList; // vector of wished book names
};




#endif //BOOST_ECHO_CLIENT_USERDATA_H
