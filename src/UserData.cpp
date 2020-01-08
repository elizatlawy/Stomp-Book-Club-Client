//
// Created by zatlawy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#include "UserData.h"





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