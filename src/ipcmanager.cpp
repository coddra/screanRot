#include "ipcmanager.h"
#include "global.h"
#include <QDebug>
#include <QTimer>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <thread>
#include <queue>
#include <stdio.h>

std::queue<std::string> messages;

IpcManager::IpcManager(QObject* parent) : QObject{parent} { }
IpcManager::~IpcManager() { }

void lock() {
    locked = true;
    if (lock_command != "") {
        qDebug() << "Running command: " << lock_command.c_str();
        system(lock_command.c_str());
    }
    qDebug() << "IPC message: lock";
}

void unlock() {
    if (locked && current_orientation != expected_orientation) {
        locked = false;
        global_manager->setOrientation(expected_orientation);
        global_rotator->rotate(expected_orientation);
    } else
        locked = false;
    if (unlock_command != "") {
        qDebug() << "Running command: " << unlock_command.c_str();
        system(unlock_command.c_str());
    }
    qDebug() << "IPC message: unlock";
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
    commands = false;
    global_manager->setOrientation(Orientation::TopUp);
    global_rotator->rotate(Orientation::TopUp);
    expected_orientation = tmp;
    commands = true;
    qDebug() << "IPC message: reset";
}

void ipc()
{
    const char* file = "/tmp/screenrotator";
    remove(file); //resolves infinite ipc messages
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
