#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <string>
#include <vector>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  int which_ctl_status_changed = -1;
  enum class PainterType { Points, TSP, Dijkstra };
  PainterType painter_type;
  vector<pair<double, double>> points, path_points;
  vector<string> ids, path_ids;
  QString status_txt;

  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void paintEvent(QPaintEvent *);
  void SwitchMode(bool choice);
  QPoint ToQPoint(const pair<double, double> &pos);
  QStringList ToQStringList(const vector<string> &v);

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
