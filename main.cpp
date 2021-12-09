#include <QApplication>

#include "invoicetable.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  InvoiceTable table;
  table.show();

  return a.exec();
}
