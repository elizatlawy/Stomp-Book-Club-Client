
#include "Book.h"

Book::Book(const string &bookName, const string &bookOwner, bool isAvailable) : bookName(bookName), bookOwner(bookOwner),available(isAvailable) {}

Book::~Book() {}

const string &Book::getBookName() const {
    return bookName;
}

const string &Book::getBookOwner() const {
    return bookOwner;
}

bool Book::isAvailable() const {
    return available;
}

void Book::setAvailable(bool isAvailable) {
    Book::available = isAvailable;
}


