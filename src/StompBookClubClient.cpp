
#include <include/keyboardHandler.h>
#include "../include/StompBookClubClient.h"
#include <thread>

using namespace std;

int main () {

keyboardHandler *keyboardHandler_ = new keyboardHandler;
thread th1(ref(keyboardHandler_));
// TODO : check if need to delete keyboardHandler
th1.join();

return 0;
}



