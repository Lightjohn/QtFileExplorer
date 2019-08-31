#ifndef DELETETASK_H
#define DELETETASK_H

#include <QLabel>
#include <QRunnable>
#include <QThread>
#include <QDir>
#include <QDebug>


class deletetask : public QRunnable
{
public:
    deletetask(QStringList ,QLabel*, QList<QString>*);
    void run() override;

private:
    QLabel *status;
    QList<QString> *deleteList;
    QStringList todelete;
};

#endif // DELETETASK_H
