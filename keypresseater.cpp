#include "keypresseater.h"

KeyPressEater::KeyPressEater(myWindows *my)
{
    parent = my;
}

bool KeyPressEater::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *key = ((QKeyEvent*)event);
        if (parent->preview->isFullScreen    && (key->key() == Qt::Key_Escape
                                              || key->key() == Qt::Key_Right
                                              || key->key() == Qt::Key_Left) ) {
            if (key->key() == Qt::Key_Escape) {
                parent->preview->fullScreen();
            }
            QWidget *focus = parent->columnView->focusWidget();
            QKeyEvent *newKey;
            if (key->key() == Qt::Key_Right) {
                newKey = new QKeyEvent(key->type(), Qt::Key_Down, Qt::NoModifier);
            }else if (key->key() == Qt::Key_Left) {
                newKey = new QKeyEvent(key->type(), Qt::Key_Up  , Qt::NoModifier);
            }else{
                qDebug() << "Should never be printed, else see keypresseater";
            }
            QApplication::sendEvent(focus, newKey);
        } else {
            QWidget *focus = parent->columnView->focusWidget();
            QApplication::sendEvent(focus, event);              //for up down
            QApplication::sendEvent(parent->columnView,event);  //for right left
        }

    }

    if (event->type() == QEvent::MouseButtonDblClick) {
        QMouseEvent * mouseEvent = (QMouseEvent*) (event);

        if (mouseEvent -> button() == Qt::LeftButton) {
            parent->preview->fullScreen();
        }
    }
    return QObject::eventFilter(obj, event);
}

KeyPressEater::~KeyPressEater(){
}
