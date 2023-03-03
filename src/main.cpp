#include <QApplication>
#include "displaymanager.h"
#include "orientationsensor.h"
#include "trayicon.h"
#include "rotateinput.h"
#include "ipcmanager.h"
#include "global.h"
#include <QtDBus/QDBusConnection>
#include <QDebug>
#include <iostream>

void processargs(int argc, char *argv[]) {
    unsigned char command = 0;
    std::string tmp;
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "---") {
            if (tmp != "") {
                switch (command) {
                    case 1:
                        landscape_command = "/bin/bash" + tmp + " &";
                        tmp = "";
                        break;
                    case 2:
                        portrait_command = "/bin/bash" + tmp + " &";
                        tmp = "";
                        break;
                }
            }
            command++;
        } else if (command == 1 || command == 2)
            tmp += " " + std::string(argv[i]);
    }
    if (command == 2 && tmp != "")
        portrait_command = "/bin/bash" + tmp + " &";
}

int main(int argc, char *argv[])
{
    processargs(argc, argv);

    QApplication app(argc, argv);
    QDBusConnection connection = QDBusConnection::sessionBus();
    if(!connection.registerService("net.gulinux.ScreenRotator")) {
      qCritical() << "Unable to register DBUS interface \"net.gulinux.ScreenRotator\". More than one instances running?";
      return 1;
    }

    DisplayManager displayManager;
    TrayIcon tray;
    OrientationSensor sensor;
    RotateInput rotateInput;
    IpcManager ipcManager;
    global_rotator = &rotateInput;
    global_manager = &displayManager;
    runipc(&ipcManager);
    QObject::connect(&sensor, &OrientationSensor::reading, &displayManager, &DisplayManager::setOrientation);
    QObject::connect(&sensor, &OrientationSensor::reading, &rotateInput, &RotateInput::rotate);
    return app.exec();
}
