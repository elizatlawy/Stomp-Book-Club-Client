//
// Created by zatlawy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#include <vector>
#include "Book.h"
#include "UserData.h"
#include <algorithm>

UserData::UserData()
        : loggedIn(false), subscriptionId(0), receiptId(0), actionLog(), inventory(unordered_map<std::string, std::vector<Book*>>()) {}

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

void UserData::addBook(string topic, Book& book) {
    // topic is not found in inventory
    if (inventory.find(topic) == inventory.end()) {
        inventory.insert(make_pair(topic, vector<Book*>()));
    }
    // topic is exist
    vector<Book*> listOfBooks = inventory.at(topic);
    listOfBooks.push_back(&book);
}

bool UserData::isAvailableBook(string topic, const string& requestedBookName) {
    vector<Book*> listOfBooks = inventory.at(topic);
    for (Book* currBook : listOfBooks){
        if(currBook->getBookName() == requestedBookName)
            return currBook->isAvailable();
    }
    return false;
}
void UserData::changeBookAvailability(string topic, const string& requestedBookName, bool status) {
    vector<Book *> listOfBooks = inventory.at(topic);
    for (Book *currBook : listOfBooks) {
        if (currBook->getBookName() == requestedBookName)
            currBook->setAvailable(status);
    }
}

const vector<string> &UserData::getWishList() const {
    return wishList;
}

void UserData::addToWishList(string bookName) {
    wishList.push_back(bookName);
}

void UserData::removeFromWishList(string bookName) {
    wishList.erase(std::remove(wishList.begin(), wishList.end(), bookName), wishList.end());
}

