#include "refreshtask.h"

refreshtask::refreshtask(QLabel *preview, QString path, int depth) {
  shouldrun = false;
  maxdepth = depth;
  currentPath = path;
  this->preview = preview;
}

void refreshtask::run() {}

void refreshtask::stop() { shouldrun = true; }
