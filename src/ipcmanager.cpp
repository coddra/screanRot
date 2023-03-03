#include "ipcmanager.h"
#include "global.h"
#include <QDebug>
#include <QTimer>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <thread>
#include <queue>

std::queue<std::string> messages;

IpcManager::IpcManager(QObject* parent) : QObject{parent} { }
IpcManager::~IpcManager() { }

void lock() {
    locked = true;
    qDebug() << "IPC message: locked";
}

void unlock() {
    if (locked && current_orientation != expected_orientation) {
        locked = false;
        global_manager->setOrientation(expected_orientation);
        global_rotator->rotate(expected_orientation);
    } else
        locked = false;
    qDebug() << "IPC message: unlocked";
}

void toggle_lock() {
    if (locked)
        unlock();
    else
        lock();
}

void reset() {
    auto tmp = expected_orientation;
    locked = false;
    global_manager->setOrientation(Orientation::TopUp);
    global_rotator->rotate(Orientation::TopUp);
    expected_orientation = tmp;
    qDebug() << "IPC message: reset";
}

void ipc()
{
    const char* file = "/tmp/screenrotator";
    mkfifo(file, 0666);
    std::ifstream fifo{file};
    std::string line;
    while (1) {
        while (std::getline(fifo, line)) {
            messages.push(line);

        }
        //this is much more performant, than just clearing the file, for some reason
        fifo.close();
        fifo = std::ifstream(file);
    }
}

void IpcManager::processMessages() {
    while (!messages.empty()) {
        if (messages.front() == "lock")
            lock();
        else if (messages.front() == "unlock")
            unlock();
        else if (messages.front() == "toggle-lock")
            toggle_lock();
        else if (messages.front() == "reset")
            reset();
        messages.pop();
    }
}

void runipc(IpcManager* ipcManager) {
    QTimer* timer = new QTimer(ipcManager);
    QObject::connect(timer, &QTimer::timeout, ipcManager, &IpcManager::processMessages);
    timer->start(100);
    std::thread(ipc).detach();
}
