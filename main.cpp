#include <QApplication>
#include "mywindows.h"
#include <QStandardItemModel>
#include <QColumnView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    myWindows wid;

    a.setObjectName("TEST");
    return a.exec();
}
