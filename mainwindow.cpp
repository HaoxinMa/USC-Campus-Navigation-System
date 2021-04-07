#include "mainwindow.h"

#include <sys/time.h>

#include <QMessageBox>
#include <QPainter>

#include "trojanmap.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
#define INIT(status)                    \
  ui->groupTSP->setEnabled(status);     \
  ui->lineEditVia1->setEnabled(status); \
  ui->lineEditVia2->setEnabled(status); \
  ui->lineEditVia3->setEnabled(status); \
  ui->lineEditVia4->setEnabled(status); \
  ui->lineEditVia5->setEnabled(status);

  ui->setupUi(this);

  ui->labelLogo->setScaledContents(true);
  ui->labelLogo->setPixmap(QPixmap(":/logo.png"));

  QLabel *labelStatus = new QLabel(this);
  ui->statusbar->addWidget(labelStatus);

  QPushButton *pushbuttonAbout = new QPushButton(this);
  pushbuttonAbout->setText("About");
  pushbuttonAbout->setGeometry(1448, 992, 60, 22);
  connect(pushbuttonAbout, &QPushButton::clicked, [=]() {
    QMessageBox::information(
        this, "About",
        "This is based on the final project of EE599 (Computer Principles) in Spring 2021 at University of Southern "
        "California. \n\nAuthor: Haoxin Ma \nCourse Instructor: Arash Saifhashemi \n\nFor more details please visit "
        "the repository link: \nhttps://github.com/HaoxinMa/Trojan-Map",
        QMessageBox::Close);
  });

  ui->radioButtonAuto->setChecked(true);
  ui->radioButtonBF->setChecked(true);
  ui->radioButton2Opt->setEnabled(false);
  INIT(false)

  connect(ui->radioButtonAuto, &QRadioButton::clicked, [=]() {
    if (ui->radioButtonAuto->isChecked()) {
      INIT(false)
    }
  });

  connect(ui->radioButtonHeli, &QRadioButton::clicked, [=]() {
    if (ui->radioButtonHeli->isChecked()) {
      INIT(true)
    }
  });

  pos.resize(7);
  ids.resize(7);

  connect(ui->lineEditFrom, &QLineEdit::textChanged, ui->listWidget, [&]() {
    status = 0;
    ui->listWidget->clear();
    string str_from = ui->lineEditFrom->text().toStdString();
    vector<string> search_res = TrojanMap().Autocomplete(str_from);
    QStringList q_search_res;
    for (unsigned long i = 0; i < search_res.size(); i++) {
      q_search_res << QString::fromStdString(search_res[i]);
    }
    ui->listWidget->addItems(q_search_res);
  });

  connect(ui->lineEditTo, &QLineEdit::textChanged, ui->listWidget, [&]() {
    status = 1;
    ui->listWidget->clear();
    string str_from = ui->lineEditTo->text().toStdString();
    vector<string> search_res = TrojanMap().Autocomplete(str_from);
    QStringList q_search_res;
    for (unsigned long i = 0; i < search_res.size(); i++) {
      q_search_res << QString::fromStdString(search_res[i]);
    }
    ui->listWidget->addItems(q_search_res);
  });

  connect(ui->lineEditVia1, &QLineEdit::textChanged, ui->listWidget, [&]() {
    status = 2;
    ui->listWidget->clear();
    string str_from = ui->lineEditVia1->text().toStdString();
    vector<string> search_res = TrojanMap().Autocomplete(str_from);
    QStringList q_search_res;
    for (unsigned long i = 0; i < search_res.size(); i++) {
      q_search_res << QString::fromStdString(search_res[i]);
    }
    ui->listWidget->addItems(q_search_res);
  });

  connect(ui->lineEditVia2, &QLineEdit::textChanged, ui->listWidget, [&]() {
    status = 3;
    ui->listWidget->clear();
    string str_from = ui->lineEditVia2->text().toStdString();
    vector<string> search_res = TrojanMap().Autocomplete(str_from);
    QStringList q_search_res;
    for (unsigned long i = 0; i < search_res.size(); i++) {
      q_search_res << QString::fromStdString(search_res[i]);
    }
    ui->listWidget->addItems(q_search_res);
  });

  connect(ui->lineEditVia3, &QLineEdit::textChanged, ui->listWidget, [&]() {
    status = 4;
    ui->listWidget->clear();
    string str_from = ui->lineEditVia3->text().toStdString();
    vector<string> search_res = TrojanMap().Autocomplete(str_from);
    QStringList q_search_res;
    for (unsigned long i = 0; i < search_res.size(); i++) {
      q_search_res << QString::fromStdString(search_res[i]);
    }
    ui->listWidget->addItems(q_search_res);
  });

  connect(ui->lineEditVia4, &QLineEdit::textChanged, ui->listWidget, [&]() {
    status = 5;
    ui->listWidget->clear();
    string str_from = ui->lineEditVia4->text().toStdString();
    vector<string> search_res = TrojanMap().Autocomplete(str_from);
    QStringList q_search_res;
    for (unsigned long i = 0; i < search_res.size(); i++) {
      q_search_res << QString::fromStdString(search_res[i]);
    }
    ui->listWidget->addItems(q_search_res);
  });

  connect(ui->lineEditVia5, &QLineEdit::textChanged, ui->listWidget, [&]() {
    status = 6;
    ui->listWidget->clear();
    string str_from = ui->lineEditVia5->text().toStdString();
    vector<string> search_res = TrojanMap().Autocomplete(str_from);
    QStringList q_search_res;
    for (unsigned long i = 0; i < search_res.size(); i++) {
      q_search_res << QString::fromStdString(search_res[i]);
    }
    ui->listWidget->addItems(q_search_res);
  });

  connect(ui->listWidget, &QListWidget::itemClicked, [&](QListWidgetItem *item) {
    TrojanMap x;
    string str;
    if (status == 0) {
      ui->lineEditFrom->setText(item->text());
      str = ui->lineEditFrom->text().toStdString();
    }
    if (status == 1) {
      ui->lineEditTo->setText(item->text());
      str = ui->lineEditTo->text().toStdString();
    }
    if (status == 2) {
      ui->lineEditVia1->setText(item->text());
      str = ui->lineEditVia1->text().toStdString();
    }
    if (status == 3) {
      ui->lineEditVia2->setText(item->text());
      str = ui->lineEditVia2->text().toStdString();
    }
    if (status == 4) {
      ui->lineEditVia3->setText(item->text());
      str = ui->lineEditVia3->text().toStdString();
    }
    if (status == 5) {
      ui->lineEditVia4->setText(item->text());
      str = ui->lineEditVia4->text().toStdString();
    }
    if (status == 6) {
      ui->lineEditVia5->setText(item->text());
      str = ui->lineEditVia5->text().toStdString();
    }
    ids[status] = x.GetID(str);
    pos[status] = x.GetPosition(str);
    paint_type = 1;
    update();
    status = -1;
  });

  connect(ui->pushButton, &QPushButton::clicked, [=]() {
    double time_start, time_end;
    TrojanMap x;
    v_pos.clear();
    v_id.clear();
    if (ui->radioButtonAuto->isChecked()) {
      string s1 = ui->lineEditFrom->text().toStdString();
      string s2 = ui->lineEditTo->text().toStdString();
      time_start = (double)clock();
      pair<double, vector<string>> pr = x.CalculateShortestPath_Dijkstra(s1, s2);
      time_end = (double)clock();
      if (pr.first == -1) {
        status_txt = "No path found.";
        labelStatus->setText(status_txt);
      }
      status_txt = "Distance: " + QString::number(pr.first) + " miles (" + QString::number(pr.first / 0.62137) +
                   " km). Time elapsed: " + QString::number((time_end - time_start) / 1000) + " s.";
      labelStatus->setText(status_txt);
      for (auto &id : pr.second) {
        v_pos.push_back(x.GetPositionFromID(id));
      }
      paint_type = 3;
    }
    if (ui->radioButtonHeli->isChecked()) {
      vector<string> location_ids;
      for (auto &id : ids) {
        if (id != "") {
          location_ids.push_back(id);
        }
      }
      time_start = (double)clock();
      pair<double, vector<vector<string>>> pr = x.TravellingTrojan(location_ids);
      time_end = (double)clock();
      status_txt = "Distance: " + QString::number(pr.first) + " miles (" + QString::number(pr.first / 0.62137) +
                   " km). Time elapsed: " + QString::number(time_end - time_start) + " ms.";
      labelStatus->setText(status_txt);
      v_id = pr.second[pr.second.size() - 1];
      for (auto &id : v_id) {
        v_pos.push_back(x.GetPositionFromID(id));
      }
      paint_type = 2;
    }
    update();
  });
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.translate(260, 0);
  painter.drawPixmap(0, 0, QPixmap(":/map.jpg"));
  QPen pen(Qt::blue);
  pen.setWidth(8);
  painter.setPen(pen);
  switch (paint_type) {
    case 1:
      for (unsigned long i = 0; i < pos.size(); i++) {
        if (pos[i].first != 0 && pos[i].second != 0) {
          painter.drawPoint(ToQPoint(pos[i]));
        }
      }
      break;
    case 2:
      for (unsigned long i = 0; i < v_pos.size(); i++) {
        painter.drawPoint(ToQPoint(v_pos[i]));
      }
      pen.setWidth(3);
      pen.setColor(Qt::red);
      pen.setStyle(Qt::DashLine);
      painter.setPen(pen);
      for (unsigned long i = 0; i < v_pos.size() - 1; i++) {
        painter.drawLine(ToQPoint(v_pos[i]), ToQPoint(v_pos[i + 1]));
      }
      break;
    case 3:
      painter.drawPoint(ToQPoint(v_pos[0]));
      painter.drawPoint(ToQPoint(v_pos[v_pos.size() - 1]));
      pen.setWidth(3);
      pen.setColor(Qt::red);
      pen.setStyle(Qt::SolidLine);
      painter.setPen(pen);
      for (unsigned long i = 0; i < v_pos.size() - 1; i++) {
        painter.drawLine(ToQPoint(v_pos[i]), ToQPoint(v_pos[i + 1]));
      }
      break;
  }
}

QPoint MainWindow::ToQPoint(const pair<double, double> &pos) {
  QPoint qp;
  constexpr double a = 1248.0 / ((-118.26524) - (-118.29997));
  constexpr double b = 992.0 / (34.01007 - 34.03294);
  qp.setX(a * (pos.first - (-118.29997)));
  qp.setY(b * (pos.second - 34.03294));
  return qp;
}
