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
    layoutGlobal = new QVBoxLayout();
    layoutGlobal->setAlignment(Qt::AlignCenter);

    //Gloval preview

    preview = new imagePreview(this);

    //Preview file part

    layoutPreview = new QHBoxLayout;


    lab = new QLabel("image ici");
    lab->setMaximumHeight(screenH-sizeCol-100);

    QPixmap *im = new QPixmap("test.png");
    lab->setPixmap(*im);

    info = new fileInfo;



    //Column view part

    model = new QFileSystemModel;
    model->setRootPath(QDir::rootPath());

    columnView = new QColumnView;
    columnView->setMinimumHeight(sizeCol);
    columnView->setModel(model);
    columnView->setRootIndex(model->setRootPath(QDir::homePath()));
    QItemSelectionModel* itSel = columnView->selectionModel();

    //Keyboard

    //global space shortcut
    shortcut = new QShortcut(QKeySequence(Qt::Key_Space), this);
    shortcut->setContext(Qt::ApplicationShortcut);

    //Qconnect
    QObject::connect(shortcut,SIGNAL(activated()),this, SLOT(keyboardEvent()));
    //Listen to qColumnView click
    QObject::connect(itSel,SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(clickedNew(QModelIndex,QModelIndex)));

    //Adding
    layoutPreview->addWidget(lab);
    layoutPreview->addWidget(info);
    layoutGlobal->addLayout(layoutPreview);
    layoutGlobal->addWidget(columnView);

    //Get event even if not in front
    KeyPressEater *eater = new KeyPressEater(this);
    preview->installEventFilter(eater);

    this->setLayout(layoutGlobal);
    this->resize(1024,900);
    this->show();
}

//The actionb called by the column view when the user do something
void myWindows::clickedNew(QModelIndex index,QModelIndex index2){
    index2.row();//useless just to remove warning
    QString fileName = model->fileName(index);
    QString filePath = model->filePath(index);
    QString ext = fileName.split(".").back();

    if (ext.toLower() == "jpg" || ext.toLower() == "png") {
        lastFilePath = new QString(filePath);
        QPixmap imtmp(filePath);
        QPixmap imtmp2 = imtmp.scaledToHeight(sizePreviewH, Qt::SmoothTransformation);
        if (imtmp2.width() > sizePreviewW) {
            lab->setPixmap(imtmp2.copy(0,0,sizePreviewW,sizePreviewH));
        }else{
            lab->setPixmap(imtmp2);
        }
        //lab->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        preview->updateImage(imtmp);
    }
    info->setName(fileName);
    info->setSize(model->size(index));
}

void myWindows::keyboardEvent(){
    //qDebug() << "SPACE ";
    if (preview->showing) {
        preview->hidePreview();
        this->setFocus();
    } else {
        if (lastFilePath != NULL) {
            preview->showImage(*lastFilePath);
            preview->setFocus();
        }
    }
}

void myWindows::keyPressEvent(QKeyEvent* event) {
    if(event->type() == QEvent::KeyPress) {
        if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down) {
                    qDebug() << "Key up/down recu";
        }else{
            qDebug() << "Key recu";
        }
    }
    if(event->type() == QEvent::ShortcutOverride) {
        qDebug() << "Override recu";
    }
}

myWindows::~myWindows(){
    //delete layoutGlobal;//Will delete layoutPreview
    //delete shortcut;
    //delete screen;
    //delete preview;
}
