//
// Created by zatlawy@wincs.cs.bgu.ac.il on 08/01/2020.
//


#include <iostream>


using namespace std;

int main(int argc, char **argv) {

    string test = "1.1.1.1:2000";
    string host = test.substr(0, test.find(':'));
    string port = test.substr(test.find(':')+1, test.size());

    cout << "host: " + host << endl;
    cout << "port: " + port << endl;


}



