#ifndef DELETETASK_H
#define DELETETASK_H

#include <QDebug>
#include <QDir>
#include <QLabel>
#include <QRunnable>
#include <QThread>

class deletetask : public QRunnable {
public:
  deletetask(QStringList, QLabel *, QList<QString> *);
  void run() override;
  void deleteFileRm(QString filepath);

private:
  QLabel *status;
  QList<QString> *deleteList;
  QStringList todelete;
};

#endif // DELETETASK_H
