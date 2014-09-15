#include "mywindows.h"

myWindows::myWindows(QWidget *parent) :QWidget(parent)
{ 
    //Getting size of the screen
    QList<QScreen*> screenObj = QGuiApplication::screens();
    screen = screenObj.at(0);
    int sizeCol;
    screenH = screen->geometry().height();
    screenW = screen->geometry().width();
    sizeCol = 150;

    sizePreviewH = 512;
    sizePreviewW = 512;

    //Globale layout
    // _____Vlayout______
    // |                |
    // |  ___HLayout___ |
    // | |            | |
    // | |   preview  | |
    // | |            | |
    // | |   file info| |
    // | |____________| |
    // |                |
    // |  column view   |
    // |________________|
    //
    layoutGlobal = new QVBoxLayout;
    layoutGlobal->setAlignment(Qt::AlignCenter);

    //Gloval preview

    preview = new imagePreview(this);

    //Preview file part

    layoutPreview = new QHBoxLayout;

    lab = new QLabel("image ici");
    lab->setMaximumHeight(screenH-sizeCol-100);
    imDef = QPixmap(":/images/test.png");
    lab->setPixmap(imDef);

    info = new fileInfo;

    //Column view part
    model = new QFileSystemModel(this);
    model->setRootPath(QDir::rootPath());


    columnView = new QColumnView(this);
    columnView->setMinimumHeight(sizeCol);
    columnView->setModel(model);
    //columnView->setRootIndex(model->setRootPath(QDir::rootPath()));
    QItemSelectionModel* itSel = columnView->selectionModel();

    //Keyboard

    //global space shortcut
    shortcut = new QShortcut(QKeySequence(Qt::Key_Space), this);
    shortcut->setContext(Qt::ApplicationShortcut);

    //global enter shortcut
    shortcutEnter = new QShortcut(QKeySequence(Qt::Key_Return), this);
    shortcutEnter->setContext(Qt::ApplicationShortcut);

    //Qconnect
    QObject::connect(shortcut,SIGNAL(activated()),this, SLOT(keyboardEvent()));
    QObject::connect(shortcutEnter,SIGNAL(activated()),this, SLOT(keyboardEnter()));
    //Listen to qColumnView click
    //Selection of a file
    QObject::connect(itSel,SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(clickedNew(QModelIndex,QModelIndex)));
    QObject::connect(model,SIGNAL(fileRenamed(QString,QString,QString)),this,SLOT(fileMoved(QString,QString,QString)));

    //Adding
    layoutPreview->addWidget(lab);
    layoutPreview->addWidget(info);
    layoutGlobal->addLayout(layoutPreview);
    layoutGlobal->addWidget(columnView);

    //Get event even if not in front
    eater = new KeyPressEater(this);
    preview->installEventFilter(eater);

    this->setLayout(layoutGlobal);
    this->resize(1024,900);
    this->show();
}

//The actionb called by the column view when the user do something
void myWindows::clickedNew(QModelIndex index,QModelIndex){
    QString fileName = model->fileName(index);
    lastFilePath = model->filePath(index);
    QString ext = fileName.split(".").back();
    info->setName(fileName);
    info->setSize(model->size(index));
    info->setResolution(0,0);
    //If it's an image we update the previews and the informations
    if (ext.toLower() == "jpg" || ext.toLower() == "jpeg" || ext.toLower() == "png") {
        lastImagePath = QString(lastFilePath);
        QPixmap imtmp(lastFilePath);
        QPixmap imtmp2 = imtmp.scaledToHeight(sizePreviewH, Qt::SmoothTransformation);
        if (imtmp2.width() > sizePreviewW) {
            lab->setPixmap(imtmp2.copy(0,0,sizePreviewW,sizePreviewH));
        }else{
            lab->setPixmap(imtmp2);
        }
        info->setResolution(imtmp.width(),imtmp.height());
        preview->updateImage(imtmp);
    }else{
        //else we show the default image
        lab->setPixmap(imDef);
    }
}

//Function to watch the global shortcut SPACE that is for showing preview
void myWindows::keyboardEvent(){
    //qDebug() << "SPACE ";
    if (preview->showing) {
        preview->hidePreview();
    } else {
        if (lastImagePath != NULL) {
            preview->showImage(lastImagePath);
            preview->activateWindow();
        }
    }
}

//Function to watch the global shortcut SPACE that is for opening the file with default app
void myWindows::keyboardEnter(){
    QDesktopServices::openUrl(QUrl::fromLocalFile(lastFilePath));
}

void myWindows::fileMoved(QString path, QString oldNameFile, QString newNameFile){
    qDebug()<<path<<" "<<oldNameFile<<" "<<newNameFile;
}

//Debug funtion to show all keyboard event
void myWindows::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Shift) {
        //qDebug() << "Key Shift";
        isShiftOn = true;
    }
}

void myWindows::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Shift) {
        //qDebug() <<"You Release Key " <<event->text();
        isShiftOn = false;
    }
}

myWindows::~myWindows(){
    delete eater;
}
