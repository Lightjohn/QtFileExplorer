#include "keypresseater.h"

KeyPressEater::KeyPressEater(myWindows *my) { parent = my; }

// Here we intercept all keyboard events like
// Escape -> To disable fullscreen
// Right-Left became Up-Down because in fullscreen mode we stay in the same
// folder
bool KeyPressEater::eventFilter(QObject *obj, QEvent *event) {
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent *key = (static_cast<QKeyEvent *>(event));
    if (parent->preview->isFullScreen &&
        (key->key() == Qt::Key_Escape || key->key() == Qt::Key_Right ||
         key->key() == Qt::Key_Left)) {
      if (key->key() == Qt::Key_Escape) {
        parent->preview->fullScreen();
      } else {
        QWidget *focus = parent->columnView->focusWidget();
        QKeyEvent *newKey;
        if (key->key() == Qt::Key_Right) {
          newKey = new QKeyEvent(key->type(), Qt::Key_Down, Qt::NoModifier);
        } else if (key->key() == Qt::Key_Left) {
          newKey = new QKeyEvent(key->type(), Qt::Key_Up, Qt::NoModifier);
        } else {
          newKey = nullptr;
          qDebug() << "Should never be printed, else see keypresseater";
        }
        QApplication::sendEvent(focus, newKey);
      }
    } else {
      // There is a little problem: i need to manually send some events to the
      // good receiver
      QWidget *focus = parent->columnView->focusWidget();
      QApplication::sendEvent(focus, event);              // for up down
      QApplication::sendEvent(parent->columnView, event); // for right left
    }
  }
  // The double click mouse on preview mode launch fullscreen
  if (event->type() == QEvent::MouseButtonDblClick) {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    if (mouseEvent->button() == Qt::LeftButton) {
      parent->preview->fullScreen();
    }
  }
  return QObject::eventFilter(obj, event);
}

KeyPressEater::~KeyPressEater() {}
