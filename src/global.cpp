#include "global.h"

bool locked = false;

Orientation current_orientation = Orientation::TopUp;
Orientation expected_orientation = Orientation::TopUp;

RotateInput* global_rotator = NULL;
DisplayManager* global_manager = NULL;

const char* portrait_command = NULL;
const char* landscape_command = NULL;
bool commands = false;
