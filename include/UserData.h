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

    void addToActionLog(string receiptId, string msg);

    string getOutputMessage(string receiptId);

    void addBook (string topic, Book& book);

    bool isAvailableBook (string topic, string requestedBookName);
    void changeBookAvailability(string topic, string requestedBookName, bool status);

    const vector<string> &getWishList() const;
    void addToWishList(string bookName);
    void removeFromWishList(string bookName);

private:
    string userName;
    string userPassword;
    bool loggedIn;
    int subscriptionId;
    int receiptId;
    unordered_map<std::string,std::string> actionLog;
    unordered_map<std::string,std::vector<Book*>> inventory;
    vector<string> wishList; // vector of wished book names

};




#endif //BOOST_ECHO_CLIENT_USERDATA_H