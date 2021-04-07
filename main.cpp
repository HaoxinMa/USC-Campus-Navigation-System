#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <QPluginLoader>

#include "mainwindow.h"
#include "trojanmap.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}