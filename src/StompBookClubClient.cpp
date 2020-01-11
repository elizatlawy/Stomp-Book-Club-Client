
#include <include/keyboardHandler.h>
#include "../include/StompBookClubClient.h"
#include <thread>

using namespace std;

int main (int argc, char *argv[]) {

keyboardHandler *keyboardHandler_ = new keyboardHandler;
thread t1(ref(keyboardHandler_));
// TODO : check if need to delete keyboardHandler
}



