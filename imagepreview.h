#ifndef IMAGEPREVIEW_H
#define IMAGEPREVIEW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QShortcut>
#include <QScreen>
#include <QRect>

#include "mywindows.h"

class imagePreview : public QWidget
{
    Q_OBJECT
public:
    explicit imagePreview(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
    void showImage(QString path);
    void updateImage(QPixmap im);
    void hidePreview();
    void fullScreen();

    bool showing;
    bool isFullScreen;


signals:

public slots:

private:
    QVBoxLayout *layout;
    QLabel *image;
    QShortcut *shortcut;
};

#endif // IMAGEPREVIEW_H
