#include "mainwindow.h"

#include <QMessageBox>
#include <QPainter>

#include "trojanmap.h"
#include "ui_mainwindow.h"

#define CAR false
#define UAV true

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

  ui->setupUi(this);

  ui->labelLogo->setScaledContents(true);
  ui->labelLogo->setPixmap(QPixmap(":/img/logo.png"));

  QLabel *labelStatus = new QLabel(this);
  ui->statusbar->addWidget(labelStatus);

  QPushButton *pushbuttonAbout = new QPushButton(this);
  pushbuttonAbout->setText("About");
  pushbuttonAbout->setGeometry(1448, 992, 60, 22);
  connect(pushbuttonAbout, &QPushButton::clicked, [this]() {
    QString about_txt =
        "This project is based on the final project of EE599 (Computer Principles) in Spring 2021 at University of "
        "Southern California. \n\n"
        "Author: Haoxin Ma \n"
        "Course Instructor: Arash Saifhashemi \n\n"
        "For more details please visit the repository link: \n"
        "https://github.com/HaoxinMa/Trojan-Map";
    QMessageBox::information(this, "About", about_txt, QMessageBox::Close);
  });
  ui->radioButtonCar->setChecked(true);
  ui->radioButtonBF->setChecked(true);
  SwitchMode(CAR);

  connect(ui->radioButtonCar, &QRadioButton::clicked, [this]() {
    if (ui->radioButtonCar->isChecked()) SwitchMode(CAR);
  });

  connect(ui->radioButtonUav, &QRadioButton::clicked, [this]() {
    if (ui->radioButtonUav->isChecked()) SwitchMode(UAV);
  });

  points.resize(7);

  connect(ui->lineEditFrom, &QLineEdit::textChanged, ui->listWidget, [&]() {
    which_ctl_status_changed = 0;
    ui->listWidget->clear();
    string str = ui->lineEditFrom->text().toStdString();
    vector<string> search_res = TrojanMap().Autocomplete(str);
    QStringList q_search_res = ToQStringList(search_res);
    ui->listWidget->addItems(q_search_res);
  });

  connect(ui->lineEditTo, &QLineEdit::textChanged, ui->listWidget, [&]() {
    which_ctl_status_changed = 1;
    ui->listWidget->clear();
    string str_from = ui->lineEditTo->text().toStdString();
    vector<string> search_res = TrojanMap().Autocomplete(str_from);
    QStringList q_search_res = ToQStringList(search_res);
    ui->listWidget->addItems(q_search_res);
  });

  connect(ui->lineEditVia1, &QLineEdit::textChanged, ui->listWidget, [&]() {
    which_ctl_status_changed = 2;
    ui->listWidget->clear();
    string str_from = ui->lineEditVia1->text().toStdString();
    vector<string> search_res = TrojanMap().Autocomplete(str_from);
    QStringList q_search_res = ToQStringList(search_res);
    ui->listWidget->addItems(q_search_res);
  });

  connect(ui->lineEditVia2, &QLineEdit::textChanged, ui->listWidget, [&]() {
    which_ctl_status_changed = 3;
    ui->listWidget->clear();
    string str_from = ui->lineEditVia2->text().toStdString();
    vector<string> search_res = TrojanMap().Autocomplete(str_from);
    QStringList q_search_res = ToQStringList(search_res);
    ui->listWidget->addItems(q_search_res);
  });

  connect(ui->lineEditVia3, &QLineEdit::textChanged, ui->listWidget, [&]() {
    which_ctl_status_changed = 4;
    ui->listWidget->clear();
    string str_from = ui->lineEditVia3->text().toStdString();
    vector<string> search_res = TrojanMap().Autocomplete(str_from);
    QStringList q_search_res = ToQStringList(search_res);
    ui->listWidget->addItems(q_search_res);
  });

  connect(ui->lineEditVia4, &QLineEdit::textChanged, ui->listWidget, [&]() {
    which_ctl_status_changed = 5;
    ui->listWidget->clear();
    string str_from = ui->lineEditVia4->text().toStdString();
    vector<string> search_res = TrojanMap().Autocomplete(str_from);
    QStringList q_search_res = ToQStringList(search_res);
    ui->listWidget->addItems(q_search_res);
  });

  connect(ui->lineEditVia5, &QLineEdit::textChanged, ui->listWidget, [&]() {
    which_ctl_status_changed = 6;
    ui->listWidget->clear();
    string str_from = ui->lineEditVia5->text().toStdString();
    vector<string> search_res = TrojanMap().Autocomplete(str_from);
    QStringList q_search_res = ToQStringList(search_res);
    ui->listWidget->addItems(q_search_res);
  });

  connect(ui->listWidget, &QListWidget::itemClicked, [this, labelStatus](QListWidgetItem *item) {
    TrojanMap x;
    string str;
    switch (which_ctl_status_changed) {
      case 0:
        ui->lineEditFrom->setText(item->text());
        str = ui->lineEditFrom->text().toStdString();
        break;
      case 1:
        ui->lineEditTo->setText(item->text());
        str = ui->lineEditTo->text().toStdString();
        break;
      case 2:
        ui->lineEditVia1->setText(item->text());
        str = ui->lineEditVia1->text().toStdString();
        break;
      case 3:
        ui->lineEditVia2->setText(item->text());
        str = ui->lineEditVia2->text().toStdString();
        break;
      case 4:
        ui->lineEditVia3->setText(item->text());
        str = ui->lineEditVia3->text().toStdString();
        break;
      case 5:
        ui->lineEditVia4->setText(item->text());
        str = ui->lineEditVia4->text().toStdString();
        break;
      case 6:
        ui->lineEditVia5->setText(item->text());
        str = ui->lineEditVia5->text().toStdString();
        break;
    }
    auto pr = x.GetPosition(str);
    points[which_ctl_status_changed] = pr;
    status_txt =
        QString::fromStdString(str) + " (" + QString::number(pr.first) + ", " + QString::number(pr.second) + ")";
    labelStatus->setText(status_txt);
    painter_type = PainterType::Points;
    update();
    which_ctl_status_changed = -1;
  });

  connect(ui->pushButton, &QPushButton::clicked, [=]() {
    TrojanMap x;
    path_points.clear();

    if (ui->radioButtonCar->isChecked()) {
      string id1 = x.GetID(ui->lineEditFrom->text().toStdString());
      string id2 = x.GetID(ui->lineEditTo->text().toStdString());
      pair<double, vector<string>> pr = x.Dijkstra(id1, id2);
      if (pr.first == -1) {
        QMessageBox::warning(this, "Warning", "Sorry. Due to our limited map data, no path is found.");
        return;
      } else {
        status_txt =
            "Distance: " + QString::number(pr.first) + " miles (" + QString::number(pr.first / 0.62137) + " km)";
        labelStatus->setText(status_txt);
      }
      for (auto &id : pr.second) {
        path_points.push_back(make_pair(x.data[id].lon, x.data[id].lat));
      }
      painter_type = PainterType::Dijkstra;
    }

    if (ui->radioButtonUav->isChecked()) {
      vector<string> location_ids;
      if (!ui->lineEditFrom->text().isEmpty())
        location_ids.push_back((x.GetID(ui->lineEditFrom->text().toStdString())));
      else {
        QMessageBox::warning(this, "Warning", "Please input a starting point");
        return;
      }
      if (!ui->lineEditVia1->text().isEmpty())
        location_ids.push_back((x.GetID(ui->lineEditVia1->text().toStdString())));
      if (!ui->lineEditVia2->text().isEmpty())
        location_ids.push_back((x.GetID(ui->lineEditVia2->text().toStdString())));
      if (!ui->lineEditVia3->text().isEmpty())
        location_ids.push_back((x.GetID(ui->lineEditVia3->text().toStdString())));
      if (!ui->lineEditVia4->text().isEmpty())
        location_ids.push_back((x.GetID(ui->lineEditVia4->text().toStdString())));
      if (!ui->lineEditVia5->text().isEmpty())
        location_ids.push_back((x.GetID(ui->lineEditVia5->text().toStdString())));
      pair<double, vector<vector<string>>> pr;
      if (location_ids.size() <= 1) {
        QMessageBox::warning(this, "Warning", "Please input at least one intermediate point");
        return;
      }
      if (ui->radioButtonBF->isChecked()) pr = x.TSP(location_ids);
      if (ui->radioButton2Opt->isChecked()) pr = x.TSP_2opt(location_ids);
      status_txt = "Distance: " + QString::number(pr.first) + " miles (" + QString::number(pr.first / 0.62137) + " km)";
      labelStatus->setText(status_txt);
      for (auto &id : pr.second[pr.second.size() - 1]) {
        path_points.push_back(make_pair(x.data[id].lon, x.data[id].lat));
      }
      painter_type = PainterType::TSP;
    }
    update();
  });
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.translate(260, 0);
  painter.drawPixmap(0, 0, QPixmap(":/img/map.jpg"));

  QPen pen;
  pen.setColor(Qt::black);
  pen.setWidth(8);
  painter.setPen(pen);

  switch (painter_type) {
    case PainterType::Points:
      for (unsigned long i = 0; i < points.size(); i++) {
        if (points[i].first != 0 && points[i].second != 0) {
          painter.drawPoint(ToQPoint(points[i]));
        }
      }
      break;

    case PainterType::Dijkstra:
      // draw verticies
      painter.drawPoint(ToQPoint(points[0]));
      painter.drawPoint(ToQPoint(points[1]));

      // draw edges
      pen.setWidth(3);
      pen.setColor(Qt::red);
      pen.setStyle(Qt::SolidLine);
      painter.setPen(pen);
      for (unsigned long i = 0; i < path_points.size() - 1; i++) {
        painter.drawLine(ToQPoint(path_points[i]), ToQPoint(path_points[i + 1]));
      }

      // draw text
      pen.setColor(Qt::black);
      painter.setPen(pen);
      painter.drawText(ToQPoint(points[0]), "FROM");
      painter.drawText(ToQPoint(points[1]), "TO");
      break;

    case PainterType::TSP:
      // draw verticies
      for (unsigned long i = 0; i < path_points.size(); i++) {
        painter.drawPoint(ToQPoint(path_points[i]));
      }

      // draw edges
      pen.setWidth(3);
      pen.setColor(Qt::red);
      pen.setStyle(Qt::DashLine);
      painter.setPen(pen);
      for (unsigned long i = 0; i < path_points.size() - 1; i++) {
        painter.drawLine(ToQPoint(path_points[i]), ToQPoint(path_points[i + 1]));
      }

      // draw text
      pen.setColor(Qt::black);
      painter.setPen(pen);
      painter.drawText(ToQPoint(points[0]), "FROM/TO");
      break;
  }
}

/**
 * SwitchMode: Set controls enabled/disabled according to mode choice
 *
 * @param  {bool} choice : 0: automobile, 1: helicopter
 */

void MainWindow::SwitchMode(bool choice) {
  ui->lineEditTo->setEnabled(choice == CAR);
  if (choice == UAV) ui->lineEditTo->setText("");
  ui->lineEditVia1->setEnabled(choice == UAV);
  ui->lineEditVia2->setEnabled(choice == UAV);
  ui->lineEditVia3->setEnabled(choice == UAV);
  ui->lineEditVia4->setEnabled(choice == UAV);
  ui->lineEditVia5->setEnabled(choice == UAV);
  ui->groupTSP->setEnabled(choice == UAV);
}

/**
 * ToQPoint: Convert from longitude, latitude to coordinates in the main window
 *
 * @param  {const pair<double, double>&} pos : longitude, latitude
 * @return {QPoint}                          : QPoint object with coordinates in the main window
 */

QPoint MainWindow::ToQPoint(const pair<double, double> &pos) {
  QPoint qpoint;
  constexpr double a = 1248.0 / ((-118.26524) - (-118.29997));
  constexpr double b = 992.0 / (34.01007 - 34.03294);
  qpoint.setX(a * (pos.first - (-118.29997)));
  qpoint.setY(b * (pos.second - 34.03294));
  return qpoint;
}

/**
 * ToQStringList: Convert from vector<string> to QStringList
 *
 * @param  {const vector<string> &} v
 * @return {QStringList}
 */

QStringList MainWindow::ToQStringList(const vector<string> &v) {
  QStringList qstringlist;
  for (unsigned long i = 0; i < v.size(); i++) {
    qstringlist << QString::fromStdString(v[i]);
  }
  return qstringlist;
}
