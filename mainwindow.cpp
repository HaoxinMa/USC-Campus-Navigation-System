#include "mainwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QPainter>

#include "trojanmap.h"
#include "ui_mainwindow.h"

#define CAR false
#define UAV true

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
  ids.resize(7);

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
    path_ids.clear();
    // fill(path_ids.begin(), path_ids.end(), 0);
  });

  connect(ui->radioButtonUav, &QRadioButton::clicked, [this]() {
    if (ui->radioButtonUav->isChecked()) SwitchMode(UAV);
    path_ids.clear();
    // fill(path_ids.begin(), path_ids.end(), 0);
  });

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
    ids[which_ctl_status_changed] = x.GetID(str);
    auto pr = x.GetPosition(str);
    status_txt =
        QString::fromStdString(str) + " (" + QString::number(pr.first) + ", " + QString::number(pr.second) + ")";
    labelStatus->setText(status_txt);
    painter_type = PainterType::Points;
    update();
    which_ctl_status_changed = -1;
  });

  connect(ui->pushButton, &QPushButton::clicked, [=]() {
    TrojanMap x;
    path_ids.clear();

    if (ui->radioButtonCar->isChecked()) {
      string id1 = x.GetID(ui->lineEditFrom->text().toStdString());
      string id2 = x.GetID(ui->lineEditTo->text().toStdString());
      if (id1 == "") {
        QMessageBox::warning(this, "Warning", "Please choose a starting point");
        return;
      }
      if (id2 == "") {
        QMessageBox::warning(this, "Warning", "Please choose a ending point");
        return;
      }
      pair<double, vector<string>> pr = x.Dijkstra(id1, id2);
      if (pr.first == -1) {
        QMessageBox::warning(this, "Warning", "Sorry. Due to our limited map data, no path is found.");
        return;
      } else {
        status_txt =
            "Distance: " + QString::number(pr.first) + " miles (" + QString::number(pr.first / 0.62137) + " km)";
        labelStatus->setText(status_txt);
      }
      path_ids = pr.second;
      painter_type = PainterType::Dijkstra;
    }

    if (ui->radioButtonUav->isChecked()) {
      vector<string> location_ids;
      if (!ui->lineEditFrom->text().isEmpty())
        location_ids.push_back((x.GetID(ui->lineEditFrom->text().toStdString())));
      else {
        QMessageBox::warning(this, "Warning", "Please choose a starting point");
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
      path_ids = (pr.second)[pr.second.size() - 1];
      painter_type = PainterType::TSP;
    }
    update();
  });
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::paintEvent(QPaintEvent *) {
  TrojanMap x;
  QPainter painter(this);
  painter.translate(260, 0);
  painter.drawPixmap(0, 0, QPixmap(":/img/map.jpg"));
  painter.setRenderHint(QPainter::Antialiasing);

  QPen pen;
  pen.setColor(Qt::black);
  pen.setWidth(8);
  painter.setPen(pen);

  switch (painter_type) {
    case PainterType::Points: {
      for (unsigned long i = 0; i < ids.size(); i++) {
        if (ui->radioButtonUav->isChecked() && i == 1) continue;
        if (ids[i] != "") {
          auto pos = make_pair(x.data[ids[i]].lon, x.data[ids[i]].lat);
          painter.drawPoint(ToQPoint(pos));                                              // draw the point
          painter.drawText(ToQPoint(pos), QString::fromStdString(x.data[ids[i]].name));  // print the location name
        }
      }
      break;
    }

    case PainterType::Dijkstra: {
      if (path_ids.empty()) break;
      // draw path
      pen.setWidth(3);
      pen.setColor(Qt::red);
      pen.setStyle(Qt::SolidLine);
      painter.setPen(pen);
      for (unsigned long i = 0; i < path_ids.size() - 1; i++) {
        // the source point of current segment
        auto point1 = make_pair(x.data[path_ids[i]].lon, x.data[path_ids[i]].lat);
        // the destination point of current segment
        auto point2 = make_pair(x.data[path_ids[i + 1]].lon, x.data[path_ids[i + 1]].lat);
        painter.drawLine(ToQPoint(point1), ToQPoint(point2));  // draw the current segment
      }

      // draw the source and destination points and print their location names
      pen.setColor(Qt::black);
      pen.setWidth(8);
      painter.setPen(pen);
      auto point1 = make_pair(x.data[ids[0]].lon, x.data[ids[0]].lat);  // the source point
      auto point2 = make_pair(x.data[ids[1]].lon, x.data[ids[1]].lat);  // the destination point
      painter.drawPoint(ToQPoint(point1));                              // draw the source point
      painter.drawPoint(ToQPoint(point2));                              // draw the destination point
      // print the source and the destination location name
      painter.drawText(ToQPoint(point1), "From: " + QString::fromStdString(x.data[ids[0]].name));
      painter.drawText(ToQPoint(point2), "To: " + QString::fromStdString(x.data[ids[1]].name));
      break;
    }

    case PainterType::TSP: {
      if (path_ids.empty()) break;
      // draw path
      pen.setWidth(3);
      pen.setColor(Qt::red);
      pen.setStyle(Qt::DotLine);
      painter.setPen(pen);
      for (unsigned long i = 0; i < path_ids.size() - 1; i++) {
        // the source point of current segment
        auto point1 = make_pair(x.data[path_ids[i]].lon, x.data[path_ids[i]].lat);
        // the destination point of current segment
        auto point2 = make_pair(x.data[path_ids[i + 1]].lon, x.data[path_ids[i + 1]].lat);
        painter.drawLine(ToQPoint(point1), ToQPoint(point2));  // draw the current segment
      }

      pen.setColor(Qt::black);
      pen.setWidth(8);
      painter.setPen(pen);
      for (unsigned long i = 0; i < ids.size(); i++) {
        if (i == 1) continue;  // ids[1] is the destination of Dijkstra function

        // draw points
        painter.drawPoint(ToQPoint(make_pair(x.data[ids[i]].lon, x.data[ids[i]].lat)));

        // print location names
        if (i == 0)
          painter.drawText(ToQPoint(make_pair(x.data[ids[0]].lon, x.data[ids[0]].lat)),
                           "From/To: " + QString::fromStdString(x.data[ids[0]].name));
        else
          painter.drawText(ToQPoint(make_pair(x.data[ids[i]].lon, x.data[ids[i]].lat)),
                           QString::fromStdString(x.data[ids[i]].name));
      }
      break;
    }
  }
}

/**
 * SwitchMode: Set controls enabled/disabled according to mode choice
 *
 * @param  {bool} choice : 0 - CAR, 1 - UAV
 */

void MainWindow::SwitchMode(bool choice) {
  ui->lineEditTo->setEnabled(choice == CAR);
  // if (choice == UAV) ui->lineEditTo->setText("");
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
