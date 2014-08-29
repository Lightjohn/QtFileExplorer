#include "imagepreview.h"

imagePreview::imagePreview(QWidget *parent) :
    QWidget(parent,Qt::Window)
{
    layout = new QVBoxLayout;
    image = new QLabel("Wrong image chosen");
    image->setStyleSheet("QLabel { background-color : black; }");
    image->setAlignment(Qt::AlignCenter);
    layout->addWidget(image);
    showing = false;
    isFullScreen = false;
    this->setLayout(layout);
}

void imagePreview::showImage(QString path){
    updateImage(path);
    showing = true;
    this->show();
}

void imagePreview::hidePreview(){
    this->hide();
    showing = false;
}

void imagePreview::updateImage(QPixmap im){

    int height = ((myWindows*)(this->parent()))->screenH;
    int width = ((myWindows*)(this->parent()))->screenW;

    QPixmap tmp;
    //Replace all of that by some computation on size and do one resize only
    if (im.height() > im.width()) {
        tmp = im.scaledToHeight(height - 100, Qt::SmoothTransformation);
    }else{
        tmp = im;
    }
    if (tmp.width() > width) {
        image->setPixmap(tmp.scaledToWidth(width - 50, Qt::SmoothTransformation));
    }else{
        image->setPixmap(tmp);
    }
    this->adjustSize();
}

void imagePreview::fullScreen(){
    if (isFullScreen) {
        this->showNormal();
    } else {
        this->showFullScreen();
    }
    isFullScreen = !isFullScreen;
}

void imagePreview::closeEvent(QCloseEvent*)
{
    showing = false;
}
