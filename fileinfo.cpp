#include "fileinfo.h"

fileInfo::fileInfo(QWidget *parent) :
    QWidget(parent)
{
    layout = new QVBoxLayout;

    commonName = QString("Name: ");
    commonSize = QString("Size: ");
    commonSizeEnd = QString("");
    fontSize = QString("font: 14pt;");
    width = QString("Width: Unknown");
    height = QString("Height: Unknown");

    name = new QLabel(commonName+"No file chosen");
    size = new QLabel(commonSize+"0");
    labelWidth = new QLabel(width);
    labelHeight = new QLabel(height);

    name->setStyleSheet(fontSize);
    size->setStyleSheet(fontSize);
    labelWidth->setStyleSheet(fontSize);
    labelHeight->setStyleSheet(fontSize);

    layout->addWidget(name);
    layout->addWidget(labelWidth);
    layout->addWidget(labelHeight);
    layout->addWidget(size);

    this->setLayout(layout);
}

void fileInfo::setName(QString nameIn){
    name->setText(commonName+nameIn);
}

void fileInfo::setResolution(int width, int height){
    labelWidth->setText("Width: "+QString::number(width));
    labelHeight->setText("Height: "+QString::number(height));
}

void fileInfo::setSize(int sizeIn){
    commonSizeEnd = QString(" B");
    if (sizeIn > 1000) {
        sizeIn = sizeIn/1000;
        commonSizeEnd = QString(" kB");
        if (sizeIn > 1000) {
            sizeIn = sizeIn/1000;
            commonSizeEnd = QString(" mB");
            if (sizeIn > 1000) {
                sizeIn = sizeIn/1000;
                commonSizeEnd = QString(" gB");
            }
        }

    }
    size->setText(commonSize+QString::number(sizeIn)+commonSizeEnd);
}

fileInfo::~fileInfo(){
}
