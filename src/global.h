#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "rotateinput.h"
#include "displaymanager.h"
#include <string>

extern bool locked;

extern Orientation current_orientation;
extern Orientation expected_orientation;

extern RotateInput* global_rotator;
extern DisplayManager* global_manager;

extern const char* portrait_command;
extern const char* landscape_command;
extern bool commands;

#endif // GLOBAL_H_
