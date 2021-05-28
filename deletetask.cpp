#include "deletetask.h"

deletetask::deletetask(QStringList something, QLabel *status,
                       QList<QString> *deleteList) {
  this->status = status;
  this->deleteList = deleteList;
  this->todelete = something;
}

void deletetask::deleteFileRm(QString filepath) {
    QFileInfo tmp(filepath);
    if (tmp.isFile()) {
      QFile file(filepath);
      if (!file.remove()) {
        qDebug() << "File not deleted: " << file.fileName();
      }
    } else {
      QDir folder(filepath);
      if (!folder.removeRecursively()) {
        qDebug() << "Not all was deleted: " << folder.absolutePath();
      }
    }
}

void deletetask::run() {
  status->setText("DELETING " + todelete.at(0));

  for (int i = 0; i < todelete.length(); ++i) {
    // qDebug() << "DELETE" << shiftList.at(i);
    // Old delete = RM -r
    QString toDelete = todelete.at(i);
#if QT_VERSION < QT_VERSION_CHECK(5, 15, 0)
    deleteFileRm(toDelete);
#else
    // New delete = Move to Trash
    if (!QFile::moveToTrash(toDelete)) {
      qDebug() << "Not deleted: " << toDelete;
      qDebug() << "Trying to rm ";
      deleteFileRm(toDelete);

    }
#endif
  }
  status->setText("");
}
