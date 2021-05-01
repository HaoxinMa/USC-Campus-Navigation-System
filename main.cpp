#include <gtest/gtest.h>

#include <QApplication>

#include "mainwindow.h"
#include "trojanmap.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  testing::InitGoogleTest(&argc, argv);
  MainWindow w;
  w.show();
  RUN_ALL_TESTS();
  return a.exec();
}
