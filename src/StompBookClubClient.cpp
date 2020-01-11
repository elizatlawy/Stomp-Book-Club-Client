
#include "keyboardHandler.h"
#include "../include/StompBookClubClient.h"
#include <thread>

using namespace std;

int main() {
    mutex mutex;
    keyboardHandler keyboardHandler_ =  keyboardHandler(mutex);
    keyboardHandler_.run();

    return 0;
}



