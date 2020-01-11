
#include "keyboardHandler.h"
#include "../include/StompBookClubClient.h"
#include <thread>

using namespace std;

int main () {

keyboardHandler keyboardHandler_ =  keyboardHandler();
thread th1(&keyboardHandler::run, &keyboardHandler_);
th1.join();

return 0;
}



