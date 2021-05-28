#ifndef REFRESHTASK_H
#define REFRESHTASK_H

#include <QRunnable>
#include <QFileInfo>
#include <QLabel>
#include <QDir>


class refreshtask: public QRunnable
{
public:
  refreshtask(QLabel *preview, QString currentPath, int depth);
  void run() override;
  void stop();
private:
  bool shouldrun;
  QLabel *preview;
  QString currentPath;
  int maxdepth;
};

#endif // REFRESHTASK_H
