#include "imagepreview.h"

imagePreview::imagePreview(QWidget *parent) :
    QWidget(parent,Qt::Window)
{
    layout = new QVBoxLayout(this);
    image = new QLabel("Wrong image chosen");
    image->setStyleSheet("QLabel { background-color : black; }");
    image->setAlignment(Qt::AlignCenter);
    image->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(image);
    showing = false;
    isFullScreen = false;
    this->setGeometry(50,50,image->width(),image->height());
}

void imagePreview::showImage(QString path){
    updateImage(path);
    showing = true;
    this->show();
}

void imagePreview::updateImage(QPixmap im){
    int height = ((myWindows*)(this->parent()))->screenH;
    int width = ((myWindows*)(this->parent()))->screenW;

    QPixmap tmp;
    //Replace all of that by some computation on size and do one resize only
    if (im.height() > height) {
        tmp = im.scaledToHeight(height - 20, Qt::SmoothTransformation);
    }else{
        tmp = im;
    }
    if (tmp.width() > width) {
        image->setPixmap(tmp.scaledToWidth(width - 50, Qt::SmoothTransformation));
    }else{
        image->setPixmap(tmp);
    }
    if (!isFullScreen) {
        this->adjustSize();
    }
}

//This function is called when we want to have the opposite effect as the actual one
//Hided -> Shown
//Shown -> Hided
void imagePreview::hidePreview(){
    if (isFullScreen) {
       fullScreen();
    }
    this->hide();
    showing = false;
}

//Same idea that hidePreview: we got from fullScreen to normal or vice versa according to actual state
void imagePreview::fullScreen(){
    if (isFullScreen) {
        this->showNormal();
    } else {
        this->showFullScreen();
    }
    isFullScreen = !isFullScreen;
}

//If the user close manually the preview windows
void imagePreview::closeEvent(QCloseEvent*)
{
    showing = false;
}
