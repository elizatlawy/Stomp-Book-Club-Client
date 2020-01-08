//
// Created by zatlawy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_USERDATA_H
#define BOOST_ECHO_CLIENT_USERDATA_H
#include <string>
#include <iostream>
#include <string>
using namespace std;



class UserData {
private:
    bool loggedIn = false;
    void logIn();
    void logout();
    bool isLoggedIn();

public:
    const string &getUserName() const;

    const string &getUserPassword() const;

    void setUserName(const string &userName);

    void setUserPassword(const string &userPassword);

private:
    string userName;
    string userPassword;

};

const string &UserData::getUserName() const {
    return userName;
}

const string &UserData::getUserPassword() const {
    return userPassword;
}

void UserData::setUserName(const string &userName) {
    UserData::userName = userName;
}

void UserData::setUserPassword(const string &userPassword) {
    UserData::userPassword = userPassword;
}


#endif //BOOST_ECHO_CLIENT_USERDATA_H
