#ifndef DELETETASK_H
#define DELETETASK_H

#include <QDebug>
#include <QDir>
#include <QLabel>
#include <QRunnable>
#include <QThread>

class deletetask : public QRunnable {
public:
  deletetask(QStringList, QLabel *, QList<QString> *, bool);
  void run() override;

private:
  QLabel *status;
  QList<QString> *deleteList;
  QStringList todelete;
  bool oldDelete;
};

#endif // DELETETASK_H
