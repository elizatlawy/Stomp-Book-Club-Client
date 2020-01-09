//
// Created by zatlawy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_USERDATA_H
#define BOOST_ECHO_CLIENT_USERDATA_H

#include <string>
#include <iostream>
#include <string>
#include <unordered_map>

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

    string removeBook (string topic, Book& book);

    bool isAvailableBook (string topic, Book& book);

private:
    string userName;
    string userPassword;
    bool loggedIn;
    int subscriptionId;
    int receiptId;
    unordered_map<std::string,std::string> actionLog;
    unordered_map<std::string,std::vector<Book*>> inventory;
};


#endif //BOOST_ECHO_CLIENT_USERDATA_H
