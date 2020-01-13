
#include "keyboardHandler.h"
#include "../include/StompBookClubClient.h"
#include <thread>

using namespace std;

// TODO: 1. check with valgrid
// TODO: 2. handle the disconnect from server
// TODO: 3. handle the bye from client
// TODO: 4. refactor the reactor
// TODO: 5. check with multiple clients




int main() {
    keyboardHandler keyboardHandler_ = keyboardHandler();
    keyboardHandler_.run();

    return 0;
}



