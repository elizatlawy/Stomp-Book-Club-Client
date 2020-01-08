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
public:
    const string &getUserName() const;

    const string &getUserPassword() const;

    void setUserName(const string &name);

    void setUserPassword(const string &password);

    bool isLoggedIn();

private:
    string userName;
    string userPassword;
    bool loggedIn = false;
    void logIn();
    void logout();


};




#endif //BOOST_ECHO_CLIENT_USERDATA_H