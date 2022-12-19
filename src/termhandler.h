#include "rotateinput.h"
#include "displaymanager.h"
#include <csignal>

extern RotateInput *globalInputRotator;
extern DisplayManager *globalDisplayManager;
void termHandler(int signum);
