
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

    bool isLogOutLock() const;

    void setLogOutLock(bool logOutLock);

    string getSubscriptionLogById(string receiptId);
    void addSubscriptionLogById(string receiptId, string topic);
    void removeSubscriptionLogById(string receiptId);

    void addSubscriptionsLogByTopic(string topic, string subscriptionId);
    void removeSubscriptionsLogByTopic(string topic);
    string getSubscriptionsLogByTopic(string topic);

    void addCommandLog(string receiptId, string command);
    string getCommand(string receiptId );

    string getBookOwner (string topic, string bookName);


private:
    string userName;
    string userPassword;
    bool loggedIn;
    int subscriptionId;
    int receiptId;
    bool loginLock = true;
    bool logOutLock = false;
    string disconnectReceiptId;
    unordered_map<std::string,std::vector<Book*>> inventory;
    vector<string> wishList; // vector of wished book names
    unordered_map<string,string> subscriptionsLogByTopic; // key: topic name value: subscriptionId
    unordered_map<string,string> subscriptionsLogById; // key: receiptId value: topic name
    unordered_map<string,string> commandLog; // key: receiptId value: command name



};




#endif //BOOST_ECHO_CLIENT_USERDATA_H
