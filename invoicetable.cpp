#include "invoicetable.h"

#include "ui_invoicetable.h"

InvoiceTable::InvoiceTable(QWidget *parent)
    : QWidget(parent), ui(new Ui::InvoiceTable) {
  ui->setupUi(this);
  TestTableView();
}

void InvoiceTable::TestTableView() {
  QStandardItemModel *model = new QStandardItemModel(this);
  ui->tableView->setModel(model);
  model->setHorizontalHeaderItem(0, new QStandardItem("id"));
  model->setHorizontalHeaderItem(1, new QStandardItem("type"));
  model->setHorizontalHeaderItem(2, new QStandardItem("code"));
  model->setHorizontalHeaderItem(3, new QStandardItem("number"));
  model->setHorizontalHeaderItem(4, new QStandardItem("price"));
  model->setHorizontalHeaderItem(5, new QStandardItem("date"));
  model->setHorizontalHeaderItem(6, new QStandardItem("check_code"));
  model->setHorizontalHeaderItem(7, new QStandardItem("encrypt_character"));
}

InvoiceTable::~InvoiceTable() { delete ui; }
