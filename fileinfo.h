#ifndef FILEINFO_H
#define FILEINFO_H

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class fileInfo : public QWidget {
  Q_OBJECT
public:
  explicit fileInfo(QWidget *parent = 0);
  void setName(QString name);
  void setSize(int size);
  void setType(QString type);
  void setResolution(int width, int height);
  ~fileInfo();

signals:

public slots:

private:
  QString commonName;
  QString commonSize;
  QString commonSizeEnd;
  QString fontSize;
  QString width;
  QString height;
  QString fileType;

  QLabel *labelWidth;
  QLabel *labelHeight;
  QLabel *name;
  QLabel *type;
  QLabel *size;
  QVBoxLayout *layout;
};

#endif // FILEINFO_H
