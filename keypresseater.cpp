#include "keypresseater.h"

KeyPressEater::KeyPressEater(myWindows *my)
{
    parent = my;
}

bool KeyPressEater::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QWidget *focus = parent->columnView->focusWidget();
        QApplication::sendEvent(focus, event);
        QApplication::sendEvent(parent->columnView,event);
    }
    return QObject::eventFilter(obj, event);
}
