#ifndef INVOICETABLE_H
#define INVOICETABLE_H

#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QTableView>
#include <QWidget>

namespace Ui {
class InvoiceTable;
}

class InvoiceTable : public QWidget {
  Q_OBJECT

 public:
  explicit InvoiceTable(QWidget *parent = nullptr);
  ~InvoiceTable();

  void TestTableView();

 private:
  Ui::InvoiceTable *ui;
};

#endif  // INVOICETABLE_H
