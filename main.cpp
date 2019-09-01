#include "mywindows.h"
#include <QApplication>
#include <QColumnView>
#include <QStandardItemModel>

int main(int argc, char *argv[])  {
  QApplication a(argc, argv);

  myWindows wid;

   a.setObjectName("TEST");
  return a.exec();
}