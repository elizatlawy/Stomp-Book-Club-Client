//
// Created by zatlawy@wincs.cs.bgu.ac.il on 09/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_BOOK_H
#define BOOST_ECHO_CLIENT_BOOK_H

#include <string>
using namespace std;


class Book {
public:
    Book(const string &bookName, const string &bookOwner, bool isBorrowed); // constructor

    const string &getBookName() const;

    const string &getBookOwner() const;

    bool isBorrowed() const;

    void setBorrowed(bool isBorrowed);

private:
    string bookName;
    string bookOwner;
    bool borrowed;

};


#endif //BOOST_ECHO_CLIENT_BOOK_H
