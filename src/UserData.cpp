
#include <vector>
#include "Book.h"
#include "UserData.h"
# include <algorithm>


UserData::UserData()
        : loggedIn(false), subscriptionId(0), receiptId(0), disconnectReceiptId("-1"), subscriptionsLogById(),
          inventory(), wishList() {}

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

int UserData::incrementAndGetReceiptCounter() {
    receiptId++;
    return receiptId;
}

string UserData::getOutputMessage(string receipt) {
    return subscriptionsLogById.at(receipt);
}


void UserData::addBook(string topic, Book &book) {
    // topic is not found in inventory
    if (!isAvailableBook(topic, book.getBookName())) {
        if (inventory.find(topic) == inventory.end()) {
            inventory.insert(make_pair(topic, vector<Book *>()));
        }
        // topic is exist
        vector<Book *> *listOfBooks = &inventory.at(topic);
        listOfBooks->push_back(&book);
    }
}

bool UserData::isAvailableBook(string topic, const string &requestedBookName) {
    if (inventory.find(topic) != inventory.end()) { // the topic exist
        vector<Book *> listOfBooks = inventory.at(topic);
        for (Book *currBook : listOfBooks) {
            if (currBook->getBookName() == requestedBookName)
                return currBook->isAvailable();
        }
    }
    return false;
}

void UserData::changeBookAvailability(string topic, const string &requestedBookName, bool status) {
    vector<Book *> listOfBooks = inventory.at(topic);
    for (Book *currBook : listOfBooks) {
        if (currBook->getBookName() == requestedBookName)
            currBook->setAvailable(status);
    }
}

string UserData::listOfAvailableBooksByTopic(string topic) {
    string output = "";
    vector<Book *> listOfBooks = inventory.at(topic);
    for (Book *currBook : listOfBooks) {
        if (currBook->isAvailable()) {
            output = output + currBook->getBookName() + ", ";
        }
    }
    output = output.substr(0, output.length() - 2);
    return output;
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

string UserData::getDisconnectReceiptId() const {
    return disconnectReceiptId;
}

void UserData::setDisconnectReceiptId(string disconnectReceiptId) {
    UserData::disconnectReceiptId = disconnectReceiptId;
}

bool UserData::isLoginLock() const {
    return loginLock;
}

void UserData::setLoginLock(bool loginLock) {
    UserData::loginLock = loginLock;
}

UserData::~UserData() {}

string UserData::getSubscriptionLogById(string receiptId) {
    return subscriptionsLogById.at(receiptId);

}

void UserData::addSubscriptionsLogByTopic(string topic, string subscriptionId) {
    subscriptionsLogByTopic.insert(make_pair(topic, subscriptionId));
}

void UserData::removeSubscriptionsLogByTopic(string topic) {
    subscriptionsLogByTopic.erase(topic);
}

void UserData::addSubscriptionLogById(string receiptId, string topic) {
    subscriptionsLogById.insert(make_pair(receiptId, topic));
}

void UserData::removeSubscriptionLogById(string receiptId) {
    subscriptionsLogById.erase(receiptId);
}

void UserData::addCommandLog(string receiptId, string command) {
    commandLog.insert(make_pair(receiptId, command));

}

string UserData::getCommand(string receiptId) {
    return commandLog.at(receiptId);

}

string UserData::getSubscriptionsLogByTopic(string topic) {
    return subscriptionsLogByTopic.at(topic);
}

bool UserData::isLogOutLock() const {
    return logOutLock;
}

void UserData::setLogOutLock(bool logOutLock) {
    UserData::logOutLock = logOutLock;
}

string UserData::getBookOwner(string topic, string bookName) {
    if (inventory.find(topic) != inventory.end()) { // the topic exist
        vector<Book *> listOfBooks = inventory.at(topic);
        for (Book *currBook : listOfBooks) {
            if (currBook->getBookName() == bookName)
                return currBook->getBookOwner();
        }
    }
}


