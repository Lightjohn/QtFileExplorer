#ifndef MYWINDOWS_H
#define MYWINDOWS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QPicture>
#include <QPixmap>
#include <QFileSystemModel>
#include <QTableView>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QColumnView>
#include <QDir>
#include <QModelIndex>
#include <QItemSelectionModel>
#include <QString>
#include <QSizePolicy>
#include <QRect>
#include <QScreen>
#include <QGuiApplication>
#include <QKeyEvent>
#include <QShortcut>
#include <QDesktopServices>
#include <QModelIndexList>
#include <QUrl>
#include <QSettings>
#include <QCloseEvent>
#include <QMessageBox>
#include <QInputDialog>

#include "imagepreview.h"
#include "fileinfo.h"
#include "keypresseater.h"

class imagePreview;
class KeyPressEater;

class myWindows : public QWidget
{
    Q_OBJECT
public:
    explicit myWindows(QWidget *parent = 0);
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

public slots:
    void clickedNew(QModelIndex index, QModelIndex index2);
    void keyboardEvent();
    void keyboardEnter();
    void keyboardDel();
    void rename();
    void keyReleaseEvent(QKeyEvent* event);

private:
    void _rename(QString path, QString newName, int *num);
    void loadSettings();
    void saveSettings();
    void updatePath(QModelIndex index);
    void updateImage();
    void updateImage(QString image);
    bool isImage(QString suffix);
    int sizePreviewW;
    int sizePreviewH;

    bool isShiftOn;

    QPixmap imDef;
    QScreen *screen;
    QVBoxLayout *layoutGlobal;
    QHBoxLayout *layoutPreview;
    QLabel *lab;
    fileInfo *info;
    QString lastImagePath;
    QString lastFilePath;
    QString lastPath;
    KeyPressEater *eater;
    QStringList shiftList;
};

#endif // MYWINDOWS_H
