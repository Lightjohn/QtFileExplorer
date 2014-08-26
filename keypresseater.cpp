#include "keypresseater.h"

KeyPressEater::KeyPressEater(myWindows *my)
{
    parent = my;
}

bool KeyPressEater::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QApplication::sendEvent(parent->columnView, event);
        //QApplication::sendEvent(parent,event);
    }
    return QObject::eventFilter(obj, event);
}
