//
// Created by zatlawy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#include "UserData.h"

UserData::UserData() : loggedIn(false), subscriptionId(0), receiptId(0), actionLog() {}

void UserData::logIn() {
    loggedIn = true;
}

void UserData::logout() {
    loggedIn = false;
}
bool UserData::isLoggedIn() {
    return loggedIn;
}

const string &UserData::getUserName() const {
    return userName;
}

const string &UserData::getUserPassword() const {
    return userPassword;
}

void UserData::setUserName(const string &name) {
    UserData::userName = name;
}

void UserData::setUserPassword(const string &password) {
    UserData::userPassword = password;
}

int UserData::incrementAndGetSubscriptionCounter() {
    subscriptionId++;
    return subscriptionId;
}

void UserData::addToActionLog(string receiptId, string msg) {
    actionLog.insert(make_pair(receiptId,msg));
}
string UserData::getOutputMessage(string receiptId) {
    return actionLog.at(receiptId);
}


