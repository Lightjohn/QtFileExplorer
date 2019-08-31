#ifndef IMAGEPREVIEW_H
#define IMAGEPREVIEW_H

#include <QDebug>
#include <QLabel>
#include <QRect>
#include <QScreen>
#include <QShortcut>
#include <QVBoxLayout>
#include <QWidget>

#include "mywindows.h"

class imagePreview : public QWidget {
  Q_OBJECT
public:
  explicit imagePreview(QWidget *parent = nullptr);
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
};

#endif // IMAGEPREVIEW_H
