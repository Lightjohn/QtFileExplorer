#include "deletetask.h"

deletetask::deletetask(QStringList something, QLabel *status,
                       QList<QString> *deleteList) {
  this->status = status;
  this->deleteList = deleteList;
  this->todelete = something;
}

void deletetask::run() {
  status->setText("DELETING " + todelete.at(0));

  for (int i = 0; i < todelete.length(); ++i) {
    // qDebug() << "DELETE" << shiftList.at(i);
    // Old delete = RM -r
#if QT_VERSION < QT_VERSION_CHECK(5, 15, 0)

    QFileInfo tmp(todelete.at(i));
    if (tmp.isFile()) {
      QFile file(todelete.at(i));
      if (!file.remove()) {
        qDebug() << "File not deleted: " << file.fileName();
      }
    } else {
      QDir folder(todelete.at(i));
      if (!folder.removeRecursively()) {
        qDebug() << "Not all was deleted: " << folder.absolutePath();
      }
    }
#else
    // New delete = Move to Trash
    QString toDelete = todelete.at(i);
    if (!QFile::moveToTrash(toDelete)) {
      qDebug() << "Not deleted: " << toDelete;
    }
#endif
  }
  status->setText("");
}
