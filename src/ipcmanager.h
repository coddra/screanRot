#ifndef IPCMANAGER_H_
#define IPCMANAGER_H_

#include <QObject>

class IpcManager: public QObject
{
    Q_OBJECT
public:
  IpcManager(QObject* parent = nullptr);
  ~IpcManager();
public slots:
  void processMessages();
};

void runipc(IpcManager*);

#endif // IPCMANAGER_H_
