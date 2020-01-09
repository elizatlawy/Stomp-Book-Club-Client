//
// Created by zatlawy@wincs.cs.bgu.ac.il on 08/01/2020.
//


#include <iostream>
#include <vector>
#include <sstream>


using namespace std;

int main(int argc, char **argv) {

    string msg = string("SEND") + '\n'
                 + string("destination:") + "1234" + '\n'
                 + ("user") + (":") + "bookList" + '\n' + '\0';
    std::stringstream ss(msg);
    std::string line;
    vector<string> results;
    while(std::getline(ss,line,'\n')){
        results.push_back(line);
    }
    for(string currStr: results){
        cout << currStr << endl;


}




}
