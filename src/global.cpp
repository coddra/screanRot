#include "global.h"

bool locked = false;

Orientation current_orientation = Orientation::TopUp;
Orientation expected_orientation = Orientation::TopUp;

RotateInput* global_rotator = NULL;
DisplayManager* global_manager = NULL;

std::string portrait_command = "";
std::string landscape_command = "";
bool commands = true;
