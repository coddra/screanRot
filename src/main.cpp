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
        if (std::string(argv[i]) != "---" && command >= 1 && command <= 4)
            tmp += " " + std::string(argv[i]);
        if (std::string(argv[i]) == "---" || i == argc - 1) {
            if (tmp != "") {
                switch (command) {
                    case 1:
                        landscape_command = tmp + " &";
                        break;
                    case 2:
                        portrait_command = tmp + " &";
                        break;
                    case 3:
                        lock_command = tmp + " &";
                        break;
                    case 4:
                        unlock_command = tmp + " &";
                        break;
                }
                tmp = "";
            }
            command++;
        }
    }
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
