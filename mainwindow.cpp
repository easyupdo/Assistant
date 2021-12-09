#include "mainwindow.h"

#include <map>

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
  // main layout
  QVBoxLayout *v_layout = new QVBoxLayout(this);

  // top layout
  QHBoxLayout *top_layout = new QHBoxLayout(this);
  QPushButton *conn_button = new QPushButton(this);
  // QLabel *ip_label = new QLabel(this);
  QLineEdit *ip_lineEdit = new QLineEdit(this);

  // set centralWiget layout
  QHBoxLayout *central_layout = new QHBoxLayout(this);
  central_layout->addWidget(widget);
  this->centralWidget()->setLayout(central_layout);

  // tabs
  QWidget *tab1 = new QWidget(this);
  QWidget *tab2 = new QWidget(this);
  this->tab_widget->addTab(tab1, "tab1");
  this->tab_widget->addTab(tab2, "tab2");

  // TODO Test Qr Code
  TestQrCode();

  // TODO Test Cam
  //  TestCam();

  // TODO Test sql
  TestSql();
}

void MainWindow::TestSql() {
  QSqlDatabase info_db = QSqlDatabase::addDatabase("QSQLITE");
  info_db.setDatabaseName("assistant.db");
  if (!info_db.open()) {
    qDebug() << "db open failed!";
  } else {
  }

  QString select_sql = "select * from info";
  QSqlQuery query;
  query.prepare("select * from info");
  if (!query.exec()) {
    qDebug() << "query select exec failed!";
    qDebug() << query.lastError();
  } else {
    qDebug() << "query select exec successful";
    while (query.next()) {
      int id = query.value(0).toInt();
      qDebug() << "id:" << id;
    }
  }
}

void MainWindow::TestCam() {
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

typedef struct {
  std::string id;
  std::string type;
  std::string code;
  std::string number;
  std::string price;  // price excluding tax
  std::string date;   // invoice data
  std::string check_code;
  std::string encrypt_character;
} InvoiceInfo;
// using InvoiceInfo = std::map<std::string, std::string>;

InvoiceInfo ParseInvoice(std::string str) {
  size_t index1 = 0;
  size_t index2 = 0;
  std::vector<std::string> invoice_info{};
  while ((index2 = str.find(",", index1)) != std::string::npos) {
    std::string sub_str = str.substr(index1, index2 - index1);
    invoice_info.push_back(sub_str);
    index1 = index2 + 1;
  }

  return {
      invoice_info[0], invoice_info[1], invoice_info[2], invoice_info[3],
      invoice_info[4], invoice_info[5], invoice_info[6], invoice_info[7],
  };
}

void MainWindow::TestQrCode() {
  //  QImage imageToDecode(":/image/qr.png");
  QImage imageToDecode;
  bool ret = imageToDecode.load(":/image/fp.png");
  QZXing decoder;
  // mandatory settings
  decoder.setDecoder(QZXing::DecoderFormat_QR_CODE |
                     QZXing::DecoderFormat_EAN_13);

  // optional settings
  // decoder.setSourceFilterType(QZXing::SourceFilter_ImageNormal |
  // QZXing::SourceFilter_ImageInverted);
  decoder.setSourceFilterType(QZXing::SourceFilter_ImageNormal);
  decoder.setTryHarderBehaviour(QZXing::TryHarderBehaviour_ThoroughScanning |
                                QZXing::TryHarderBehaviour_Rotate);

  // trigger decode
  QString result = decoder.decodeImage(imageToDecode);
  qDebug() << result;
  InvoiceInfo invoice_info = ParseInvoice(result.toStdString());
  qDebug() << "check_code:" << QString::fromStdString(invoice_info.check_code);
}

MainWindow::~MainWindow() { delete ui; }
