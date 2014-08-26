#include "imagepreview.h"

imagePreview::imagePreview(QWidget *parent) :
    QWidget(parent,Qt::Window)
{
    layout = new QVBoxLayout;
    image = new QLabel("Wrong image chosen");
    layout->addWidget(image);
    showing = false;
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

void imagePreview::updateImage(QString path){
    //TODO get size from parent
    QList<QScreen*> screenObj = QGuiApplication::screens();
    QScreen *screen = screenObj.at(0);
    int height, width;
    height = screen->geometry().height();
    width = screen->geometry().width();

    im = new QPixmap(path);
    QPixmap tmp;
    if (im->height() > height) {
        tmp = im->scaledToHeight(height - 100, Qt::SmoothTransformation);
    }else{
        tmp = *im;
    }
    if (tmp.width() > width) {
        image->setPixmap(tmp.scaledToWidth(width - 50, Qt::SmoothTransformation));
    }else{
        image->setPixmap(tmp);
    }
    this->adjustSize();
}

void imagePreview::closeEvent(QCloseEvent*)
{
    showing = false;
}
