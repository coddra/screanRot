#include <QApplication>
#include "displaymanager.h"
#include "orientationsensor.h"
#include "trayicon.h"
#include "rotateinput.h"
#include "ipcmanager.h"
#include "global.h"
#include <QtDBus/QDBusConnection>
#include <QDebug>

int main(int argc, char *argv[])
{
    if (argc > 2) {
        landscape_command = (std::string(argv[1]) + " &").c_str();
        portrait_command = (std::string(argv[2]) + " &").c_str();
        commands = true;
    }

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
