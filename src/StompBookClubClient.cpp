
#include "keyboardHandler.h"

using namespace std;

// TODO: 1. check with valgrind
// TODO: 4. refactor the reactor
// TODO: 5. check with multiple clients - multiple borrow and multiple return




int main() {
    keyboardHandler keyboardHandler_ = keyboardHandler();
    keyboardHandler_.run();

    return 0;
}



