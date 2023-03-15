#include "global.h"
#include <QDebug>

bool locked = false;

Orientation current_orientation = Orientation::TopUp;
Orientation expected_orientation = Orientation::TopUp;

RotateInput* global_rotator = NULL;
DisplayManager* global_manager = NULL;

std::string portrait_command = "";
std::string landscape_command = "";
std::string lock_command = "";
std::string unlock_command = "";

void execcommand() {
    auto command = current_orientation == Orientation::TopUp || current_orientation == Orientation::TopDown ? landscape_command : portrait_command;
    if (command != "") {
        qDebug() << "Running command: " << command.c_str();
        system(command.c_str());
    }
}
