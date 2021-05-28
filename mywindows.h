#ifndef MYWINDOWS_H
#define MYWINDOWS_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <QCloseEvent>
#include <QColumnView>
#include <QDebug>
#include <QDesktopServices>
#include <QDir>
#include <QFileSystemModel>
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QInputDialog>
#include <QItemSelectionModel>
#include <QKeyEvent>
#include <QLabel>
#include <QMessageBox>
#include <QModelIndex>
#include <QModelIndexList>
#include <QPicture>
#include <QPixmap>
#include <QPushButton>
#include <QRect>
#include <QScreen>
#include <QSettings>
#include <QShortcut>
#include <QSizePolicy>
#include <QSpinBox>
#include <QStandardItemModel>
#include <QString>
#include <QTableView>
#include <QThreadPool>
#include <QUrl>
#include <QVBoxLayout>
#include <QWidget>

#include "deletetask.h"
#include "fileinfo.h"
#include "imagepreview.h"
#include "keypresseater.h"

class imagePreview;
class KeyPressEater;

class myWindows : public QWidget {
  Q_OBJECT
public:
  explicit myWindows(QWidget *parent = nullptr);
  void keyPressEvent(QKeyEvent *event);
  ~myWindows();
  QShortcut *shortcutSpace;
  QShortcut *shortcutEnter;
  QShortcut *shortcutDel;
  QColumnView *columnView;
  QFileSystemModel *model;
  imagePreview *preview;
  int screenH;
  int screenW;
  void closeEvent(QCloseEvent *);

  int canDelete();
public slots:
  void clickedNew(QModelIndex index, QModelIndex index2);
  void keyboardEvent();
  void keyboardEnter();
  void keyboardDel();
  void rename();
  void keyReleaseEvent(QKeyEvent *event);
  void depthChanged(int);

private:
  void _rename(QString path, QString newName, int *num);
  void loadSettings();
  void saveSettings();
  void updatePath(QModelIndex index);
  void updateImage();
  void updateImage(QString image);
  bool parseFolderAndUpdate(QString path, int depth);
  bool isImage(QString suffix);
  int sizePreviewW;
  int sizePreviewH;

  int MAX_DEPTH = 2;

  bool isShiftOn;

  QList<QString> *toDelete;

  QPixmap imDef;
  QScreen *screen;
  QVBoxLayout *layoutGlobal;
  QHBoxLayout *layoutPreview;
  QLabel *lab;
  QLabel *deleteStatus;
  fileInfo *info;
  QString lastImagePath;
  QString lastFilePath;
  QString lastPath;
  KeyPressEater *eater;
  QStringList shiftList;
  QSpinBox *spinBox;
};

#endif // MYWINDOWS_H
