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
