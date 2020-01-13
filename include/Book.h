
#ifndef BOOST_ECHO_CLIENT_BOOK_H
#define BOOST_ECHO_CLIENT_BOOK_H

#include <string>
using namespace std;


class Book {
public:
    Book(const string &bookName, const string &bookOwner, bool available); // constructor

    virtual ~Book(); // destructor

    const string &getBookName() const;

    const string &getBookOwner() const;

    bool isAvailable() const;
    void setAvailable(bool available);

private:
    string bookName;
    string bookOwner;
    bool available;

};

#endif //BOOST_ECHO_CLIENT_BOOK_H
