//
// Created by zatlawy@wincs.cs.bgu.ac.il on 08/01/2020.
//

#include <vector>
#include "userData.h"
#include <algorithm>

userData::userData()
        : loggedIn(false), subscriptionId(0), receiptId(0), actionLog(), inventory(unordered_map<std::string, std::vector<string>>()) {}

void userData::logIn() {
    loggedIn = true;
}

void userData::logout() {
    loggedIn = false;
}
bool userData::isLoggedIn() {
    return loggedIn;
}

const string &userData::getUserName() const {
    return userName;
}

const string &userData::getUserPassword() const {
    return userPassword;
}

void userData::setUserName(const string &name) {
    userData::userName = name;
}

void userData::setUserPassword(const string &password) {
    userData::userPassword = password;
}

int userData::incrementAndGetSubscriptionCounter() {
    subscriptionId++;
    return subscriptionId;
}
void userData::addToActionLog(string receiptId, string msg) {
    actionLog.insert(make_pair(receiptId,msg));
}

string userData::getOutputMessage(string receiptId) {
    return actionLog.at(receiptId);
}

void userData::addBook(string topic, string book) {
    // topic is not found in inventory
    if (inventory.find(topic) == inventory.end()) {
        inventory.insert(make_pair(topic, vector<string>()));
    }
    // topic is exist
    vector<string> listOfBooks = inventory.at(topic);
    listOfBooks.push_back(book);
}

string userData::removeBook(string topic, string book) {
    vector<string> listOfBooks = inventory.at(topic);
    listOfBooks.erase(remove( listOfBooks.begin(), listOfBooks.end(), book ), listOfBooks.end() );

}

bool userData::isAvailableBook(string topic, string book) {
    vector<string> listOfBooks = inventory.at(topic);
    return find(listOfBooks.begin(), listOfBooks.end(), book) != listOfBooks.end();
}



