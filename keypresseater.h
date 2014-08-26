#ifndef KEYPRESSEATER_H
#define KEYPRESSEATER_H
#include <QObject>
#include <QEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QApplication>

#include "mywindows.h"

class myWindows;

class KeyPressEater : public QObject
{
Q_OBJECT

protected:
    bool eventFilter(QObject *obj, QEvent *event);

public:
    KeyPressEater(myWindows *my);

private:
    myWindows *parent;
};

#endif // KEYPRESSEATER_H
