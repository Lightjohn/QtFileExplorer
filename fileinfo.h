#ifndef FILEINFO_H
#define FILEINFO_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class fileInfo : public QWidget
{
    Q_OBJECT
public:
    explicit fileInfo(QWidget *parent = 0);
    void setName(QString name);
    void setSize(int size);

signals:

public slots:

private:
    QString *commonName;
    QString *commonSize;
    QString *commonSizeEnd;
    QString *fontSize;

    QLabel *name;
    QLabel *size;
    QVBoxLayout *layout;
};

#endif // FILEINFO_H
