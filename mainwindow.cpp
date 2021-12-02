#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->tab_widget = new QTabWidget(this);
  this->stacked_widget = new QStackedWidget(this);
  QWidget *widget = new QWidget(this);

  QHBoxLayout *h_layout = new QHBoxLayout(this);
  widget->setLayout(h_layout);

  QWidget *left_widget = new QWidget(this);
  h_layout->addWidget(left_widget);
  h_layout->addWidget(this->tab_widget);

  h_layout->setStretchFactor(left_widget, 1);
  h_layout->setStretchFactor(tab_widget, 4);

  // set centralWiget layout
  QHBoxLayout *central_layout = new QHBoxLayout(this);
  central_layout->addWidget(widget);
  this->centralWidget()->setLayout(central_layout);

  // tabs
  QWidget *tab1 = new QWidget(this);
  QWidget *tab2 = new QWidget(this);
  this->tab_widget->addTab(tab1, "tab1");
  this->tab_widget->addTab(tab2, "tab2");

  // test cam
  QList<QCameraInfo> info = QCameraInfo::availableCameras();
  qDebug() << "cam infos" << info.size();
  for (auto one : info) {
    qDebug() << one.deviceName();
  }
  qDebug() << info[0];

  //  cam_widget = new QWidget(this);
  //  cam_widget->resize(640, 320);
  cam = new QCamera(info[0], this);
  connect(cam, &QCamera::stateChanged, this,
          []() { qDebug() << "status:stateChanged"; });
  connect(cam, QOverload<QCamera::Error>::of(&QCamera::error), this,
          []() { qDebug() << "error"; });
  cam_image_capture = new QCameraImageCapture(cam);

  cam->setCaptureMode(QCamera::CaptureMode::CaptureStillImage);
  cam->setCaptureMode(QCamera::CaptureMode::CaptureViewfinder);

  cam_view_finder = new QCameraViewfinder();
  cam_view_finder->resize(640, 320);
  cam->setViewfinder(cam_view_finder);
  cam_view_finder->show();
  cam->start();

  //  QVideoWidget *video_widget = new QVideoWidget();
  //  cam->setViewfinder(video_widget);
  //  video_widget->show();
  //  cam->start();
}

MainWindow::~MainWindow() { delete ui; }
