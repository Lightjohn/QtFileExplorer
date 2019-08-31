#ifndef KEYPRESSEATER_H
#define KEYPRESSEATER_H
#include <QApplication>
#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QObject>

#include "mywindows.h"

class myWindows;

class KeyPressEater : public QObject {
  Q_OBJECT

protected:
  bool eventFilter(QObject *obj, QEvent *event);

public:
  KeyPressEater(myWindows *my);
  ~KeyPressEater();

private:
  myWindows *parent;
};

#endif // KEYPRESSEATER_H
