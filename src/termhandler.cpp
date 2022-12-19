#include "termhandler.h"
#include "rotateinput.h"
#include <iostream>

RotateInput *globalInputRotator = NULL;
DisplayManager *globalDisplayManager = NULL;
void termHandler(int signum) {
    globalDisplayManager->setOrientation(Orientation::TopUp);
    globalInputRotator->rotate(Orientation::TopUp);
    exit(signum);
}
