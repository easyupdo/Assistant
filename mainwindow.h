#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QSpacerItem>
#include <QStackedWidget>
#include <QStandardItemModel>
#include <QTabWidget>
#include <QTableView>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QVideoWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql>

#include "QZXing"
#include "QZXing.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void TestCam();
  void TestQrCode();

  void TestSql();

 private:
  Ui::MainWindow *ui;
  QTableWidget *table_widget;
  QTabWidget *tab_widget;
  QStackedWidget *stacked_widget;

  // TODO test camera
  QWidget *cam_widget;
  QCamera *cam;
  QCameraImageCapture *cam_image_capture;
  QCameraViewfinder *cam_view_finder;
};
#endif  // MAINWINDOW_H
