
#include "keyboardHandler.h"

using namespace std;

// TODO: 4. refactor the reactor
// TODO: 5. check with multiple clients - multiple borrow and multiple return

int main(int argc, char **argv) {
    keyboardHandler keyboardHandler_ = keyboardHandler();
    keyboardHandler_.run();

    return 0;
}



