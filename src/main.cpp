//
// Created by kadurin@wincs.cs.bgu.ac.il on 08/01/2020.
//

#include "main.h"
#include <string>
using namespace std;
#include <iostream>


int main(int argc, char** argv) {
    string output = string("CONNECT") + ('\n') + string("accept-version:1.2");
    cout << output << endl;
}