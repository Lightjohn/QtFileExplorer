#include "mywindows.h"

myWindows::myWindows(QWidget *parent) : QWidget(parent) {
  // Getting size of the screen
  QList<QScreen *> screenObj = QGuiApplication::screens();
  screen = screenObj.at(0);
  int sizeCol;
  screenH = screen->geometry().height();
  screenW = screen->geometry().width();
  sizeCol = 150;

  sizePreviewH = 512;
  sizePreviewW = 512;

  int minPrev = screenH - sizeCol;
  if (minPrev < sizePreviewH) {
    sizePreviewH = minPrev;
    sizePreviewW = minPrev;
  }

  isShiftOn = false;
  // Globale layout
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

  // Gloval preview

  preview = new imagePreview(this);

  // Preview file part

  layoutPreview = new QHBoxLayout;

  lab = new QLabel("image ici");
  lab->setMaximumHeight(sizePreviewH - 110);
  imDef = QPixmap(":/images/test.png");
  lab->setPixmap(imDef);

  info = new fileInfo;

  // Column view part
  model = new QFileSystemModel(this);
  model->setRootPath(QDir::rootPath());
  model->setResolveSymlinks(true);
  model->setReadOnly(false);
  model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::AllDirs |
                   QDir::System);

  // Loading preferences
  loadSettings();

  columnView = new QColumnView(this);
  columnView->setMinimumHeight(sizeCol);
  columnView->setModel(model);
  // tree->setRootIndex(model->index(QDir::currentPath()));
  columnView->setCurrentIndex(model->index(lastPath));
  // columnView->setRootIndex());
  QItemSelectionModel *itSel = columnView->selectionModel();

  // Adding rename

  QPushButton *rename = new QPushButton("Rename");

  // All the thread deletion part

  QThreadPool::globalInstance()->setMaxThreadCount(1);
  toDelete = new QList<QString>;
  deleteStatus = new QLabel("");

  // Keyboard

  // global space shortcut
  shortcutSpace = new QShortcut(QKeySequence(Qt::Key_Space), this);
  shortcutSpace->setContext(Qt::ApplicationShortcut);

  // global enter shortcut
  shortcutEnter = new QShortcut(QKeySequence(Qt::Key_Return), this);
  // shortcutEnter->setContext(Qt::ApplicationShortcut);

  // Global Supr Shortcut
  shortcutDel = new QShortcut(QKeySequence(Qt::Key_Delete), this);
  shortcutDel->setContext(Qt::ApplicationShortcut);

  // Qconnect
  QObject::connect(shortcutSpace, SIGNAL(activated()), this,
                   SLOT(keyboardEvent()));
  QObject::connect(shortcutEnter, SIGNAL(activated()), this,
                   SLOT(keyboardEnter()));
  QObject::connect(shortcutDel, SIGNAL(activated()), this, SLOT(keyboardDel()));
  // Listen to qColumnView click
  // Selection of a file
  QObject::connect(itSel, SIGNAL(currentChanged(QModelIndex, QModelIndex)),
                   this, SLOT(clickedNew(QModelIndex, QModelIndex)));
  QObject::connect(rename, SIGNAL(clicked()), this, SLOT(rename()));

  // Adding
  layoutPreview->addWidget(lab);
  layoutPreview->addWidget(info);
  layoutGlobal->addLayout(layoutPreview);
  layoutGlobal->addWidget(columnView);
  layoutGlobal->addWidget(rename);
  layoutGlobal->addWidget(deleteStatus);

  // Get event even if not in front
  eater = new KeyPressEater(this);
  preview->installEventFilter(eater);

  this->setLayout(layoutGlobal);
  this->resize(1024, 900);
  this->show();
}

// Update variable last*Path AND if shift is on remember all selected files
void myWindows::updatePath(QModelIndex index) {
  lastFilePath = model->filePath(index);
  QFileInfo infoFile(lastFilePath);
  lastPath = infoFile.canonicalPath();
  if (isShiftOn) {
    shiftList.append(lastFilePath);
  } else {
    shiftList.clear();
    shiftList.append(lastFilePath);
  }
}

// The actionb called by the column view when the user do something
void myWindows::clickedNew(QModelIndex index, QModelIndex) {
  updatePath(index);
  QString fileName = model->fileName(index);
  QFileInfo infoFile(lastFilePath);
  QString ext = fileName.split(".")
                    .back(); // We could use here QFileInfo::completeSuffix()
  int SIZE_NAME_MAX = 50;
  if (fileName.length() > SIZE_NAME_MAX) {
    info->setName(fileName.mid(0, SIZE_NAME_MAX));
  } else {
    info->setName(fileName);
  }
  if (ext.length() == 1 || ext.length() >= 5) {
    info->setType("Not a standard file");
  } else {
    info->setType(ext.toLower());
  }
  info->setSize(int(model->size(index)));
  info->setResolution(0, 0);
  // If it's an image we update the previews and the informations
  QString lowExt = ext.toLower();
  if (infoFile.isFile() && isImage(lowExt)) {
    updateImage();
  } else if (infoFile.isDir()) {
    // If there is an image inside we try to show it
    bool found = parseFolderAndUpdate(lastFilePath, MAX_DEPTH);
    // else we show the default image if no file is an image
    if (!found) {
      lab->setPixmap(imDef);
    }
  } else {
    // else we show the default image
    lab->setPixmap(imDef);
  }
}

bool myWindows::parseFolderAndUpdate(QString path, int depth) {

  QDir dir = QDir(path);
  dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
  QString lowExt;
  QFileInfoList list = dir.entryInfoList();
  // qDebug() << depth << path << list.size();
  bool found = false;
  for (int i = 0; i < list.size(); ++i) {
    QFileInfo fileInfo = list.at(i);
    lowExt = fileInfo.suffix().toLower();
    if (fileInfo.isFile() && isImage(lowExt)) {
      updateImage(fileInfo.absoluteFilePath());
      found = true;
    } else if (fileInfo.isDir() && depth > 0) {
      // qDebug() << "Deeper" << fileInfo.absoluteFilePath();
      found = parseFolderAndUpdate(fileInfo.absoluteFilePath(), depth - 1);
    }
    if (found) {
      break;
    }
  }
  return found;
}

bool myWindows::isImage(QString suffix) {
  QString lowSuffix = suffix.toLower();
  return (lowSuffix == "jpg" || lowSuffix == "jpeg" || lowSuffix == "png");
}

void myWindows::updateImage() { updateImage(lastFilePath); }

void myWindows::updateImage(QString image) {
  lastImagePath = QString(image); // For later in case of fullscreen
  QPixmap imtmp(image);
  if (imtmp.isNull()) { // in the case someone give a bad extension (png instead
                        // of jpg)...
    imtmp = imDef;
  }
  QPixmap imtmp2 = imtmp.scaledToHeight(sizePreviewH, Qt::SmoothTransformation);

  if (imtmp2.width() > sizePreviewW) {
    lab->setPixmap(imtmp2.copy(0, 0, sizePreviewW, sizePreviewH));
  } else {
    lab->setPixmap(imtmp2);
  }
  info->setResolution(imtmp.width(), imtmp.height());
  preview->updateImage(imtmp);
}

// Function to watch the global shortcut SPACE that is for showing preview
void myWindows::keyboardEvent() {
  // qDebug() << "SPACE ";
  if (preview->showing) {
    preview->hidePreview();
  } else {
    if (lastImagePath != nullptr) {
      preview->showImage(lastImagePath);
      preview->activateWindow();
    }
  }
}

// Function to watch the global shortcut SPACE that is for opening the file with
// default app
void myWindows::keyboardEnter() {
  // qDebug() << "ENTER ";
  QDesktopServices::openUrl(QUrl::fromLocalFile(lastFilePath));
}

// Debug funtion to show all keyboard event
void myWindows::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Shift) {
    // qDebug() << "Key Shift";
    isShiftOn = true;
  }
}

void myWindows::rename() {
  bool ok;
  QString text = QInputDialog::getText(this, tr("Renamming"), tr("base name:"),
                                       QLineEdit::Normal, "", &ok);
  int num = 0;
  if (ok) {
    for (int var = 0; var < shiftList.length(); ++var) {
      _rename(shiftList.at(var), text, &num);
    }
  }
}

void myWindows::_rename(QString path, QString newName, int *num) {
  QFileInfo tmp(path);
  if (tmp.isFile()) {
    QFile file(path);
    QString newConstructedName =
        tmp.canonicalPath() + QDir::separator() + newName;
    // If the name if something XXX-01 else 01
    if (newName != "") {
      newConstructedName += "-";
    }
    if (*num >= 10) {
      if (*num < 100) {
        newConstructedName += QString("0");
      }
    } else {
      newConstructedName += QString("00");
    }
    newConstructedName += QString::number(*num);
    // if the file had an extension we keep it else nothing
    // prev.jpg -> XXX-01.jpg
    if (tmp.completeSuffix() != "") {
      newConstructedName += "." + tmp.completeSuffix();
    }
    file.rename(newConstructedName);
    *num = *num + 1;
  } else if (tmp.isDir()) {
    // If we have a dir we get folders and files inside and try to rename them
    QDir fold(path);
    QStringList elmts =
        fold.entryList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files);
    for (int var = 0; var < elmts.length(); ++var) {
      _rename(path + QDir::separator() + elmts.at(var), newName, num);
    }
  }
}

void myWindows::keyReleaseEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Shift) {
    // qDebug() <<"You Release Key " <<event->text();
    isShiftOn = false;
  }
}

void myWindows::loadSettings() {
  QSettings settings("IntCorpLightAssociation", "FileViewer");
  lastPath = settings.value("lastPath").toString();
}
void myWindows::saveSettings() {
  QSettings settings("IntCorpLightAssociation", "FileViewer");
  settings.setValue("lastPath", lastPath);
}

void myWindows::keyboardDel() {
  QMessageBox box;
  box.setText("Selected files/folders will be eternally deleted !!");
  box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
  box.setWindowFlags(Qt::WindowStaysOnTopHint);
  box.setDefaultButton(QMessageBox::Ok);
  int ret = box.exec();
  if (ret == QMessageBox::Ok) {
    deletetask *task = new deletetask(shiftList, deleteStatus, toDelete);
    QThreadPool::globalInstance()->start(task);
  }
}

// To add coloration to folders/files
// http://stackoverflow.com/questions/1397484/custom-text-color-for-certain-indexes-in-qtreeview

// When the app is closed we saved what is necessary to save
void myWindows::closeEvent(QCloseEvent *) { saveSettings(); }

myWindows::~myWindows() { delete eater; }
