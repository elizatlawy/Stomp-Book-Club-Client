//
// Created by zatlawy@wincs.cs.bgu.ac.il on 08/01/2020.
//


#include <iostream>
using namespace std;

int main(int argc, char **argv) {
    string topic = "topic";
    string receiptId = "receiptId";
    string output = string("SEND") + '\n'
                    + string("destination:") + topic + '\n'
                    + ("Eli ") + string("has ") + ("bookname") + '\n' + '\0';
    cout << output << endl;
    return 0;
}
