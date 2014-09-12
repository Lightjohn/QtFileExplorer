#ifndef MYWINDOWS_H
#define MYWINDOWS_H

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
#include <stdio.h>
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
#include <QUrl>

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
    QShortcut *shortcut;
    QShortcut *shortcutEnter;
    QColumnView *columnView;
    QFileSystemModel *model;
    imagePreview *preview;
    int screenH;
    int screenW;
public slots:

    void clickedNew(QModelIndex index, QModelIndex index2);
    void keyboardEvent();
    void keyboardEnter();

private:
    int sizePreviewW;
    int sizePreviewH;
    QPixmap imDef;
    QScreen *screen;
    QVBoxLayout *layoutGlobal;
    QHBoxLayout *layoutPreview;
    QLabel *lab;
    fileInfo *info;
    QString lastFilePath;
    KeyPressEater *eater;


};

#endif // MYWINDOWS_H
