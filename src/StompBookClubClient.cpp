
#include "keyboardHandler.h"

using namespace std;

// TODO: 1. check with valgrind
// TODO: 2. handle the disconnect from server - socket close
// TODO: 4. refactor the reactor
// TODO: 5. check with multiple clients - multiple borrow and multiple return
// TODO: 6. synchronize sendLine



int main() {
    keyboardHandler keyboardHandler_ = keyboardHandler();
    keyboardHandler_.run();

    return 0;
}



