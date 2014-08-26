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

#include "imagepreview.h"
#include "fileinfo.h"
#include "keypresseater.h"

class imagePreview;

class myWindows : public QWidget
{
    Q_OBJECT
public:
    explicit myWindows(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    ~myWindows();
    QShortcut *shortcut;
    QColumnView *columnView;
    QFileSystemModel *model;

public slots:

    void clickedNew(QModelIndex index, QModelIndex index2);
    void keyboardEvent();

private:
    int sizePreviewW;
    int sizePreviewH;

    QScreen *screen;
    QVBoxLayout *layoutGlobal;
    QHBoxLayout *layoutPreview;
    QLabel *lab;
    fileInfo *info;
    QString *lastFilePath;
    imagePreview *preview;
};

#endif // MYWINDOWS_H
