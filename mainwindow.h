#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  int status = -1;
  int paint_type = 0;
  vector<pair<double, double>> pos, v_pos;
  vector<string> ids, v_id;
  QString status_txt;

  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void paintEvent(QPaintEvent *);
  QPoint ToQPoint(const pair<double, double> &pos);

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
