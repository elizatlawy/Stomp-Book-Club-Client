//
// Created by zatlawy@wincs.cs.bgu.ac.il on 09/01/2020.
//

#include "Book.h"

Book::Book(const string &bookName, const string &bookOwner, bool Borrowed) : bookName(bookName), bookOwner(bookOwner),
                                                                             available(Borrowed) {}


void Book::setBorrowed(bool isBorrowed) {
    Book::available = isBorrowed;
}

const string &Book::getBookName() const {
    return bookName;
}

const string &Book::getBookOwner() const {
    return bookOwner;
}

bool Book::isAvailable() const {
    return available;
}

void Book::setAvailable(bool available) {
    Book::available = available;
}
