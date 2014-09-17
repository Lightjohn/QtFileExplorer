#include "fileinfo.h"

/*  Informations displayed
 *
 *  NAME : filename, size limited to xx char see mywindows.cpp
 *
 *  WIDTH : int or 0 if not a image
 *
 *  HEIGHT : int or 0 if not a image
 *
 *  TYPE : extension of the file or "Not a standard file"
 *
 *  SIZE : size in B, KB, GB..
 *
 **/

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
    fileType = QString("Type: Unknown");

    name = new QLabel(commonName+"No file chosen");
    size = new QLabel(commonSize+"0");
    labelWidth = new QLabel(width);
    labelHeight = new QLabel(height);
    type = new QLabel(fileType);

    name->setStyleSheet(fontSize);
    size->setStyleSheet(fontSize);
    labelWidth->setStyleSheet(fontSize);
    labelHeight->setStyleSheet(fontSize);
    type->setStyleSheet(fontSize);

    layout->addWidget(name);
    layout->addWidget(labelWidth);
    layout->addWidget(labelHeight);
    layout->addWidget(type);
    layout->addWidget(size);

    this->setLayout(layout);
}

void fileInfo::setType(QString ext){
    type->setText("Type: "+ext);
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
