#include "deposit_form.h"

#include "../Controller.h"
#include "ui_deposit_form.h"
namespace s21 {
Deposit_form::Deposit_form(Controller *controller)
    : ui(new Ui::Deposit_form), controller_(controller) {
  this->setWindowTitle("Deposits");
  ui->setupUi(this);
  connect(ui->pushButton_add_lists, SIGNAL(released()), this,
          SLOT(listsPressed()));
  connect(ui->pushButton_get_result, SIGNAL(released()), this,
          SLOT(resultPressed()));
}

Deposit_form::~Deposit_form() { delete ui; }

void Deposit_form::CreateListRow() {
  int row = ui->tableWidget_Replenishment->rowCount();
  ui->tableWidget_Replenishment->insertRow(
      ui->tableWidget_Replenishment->rowCount());
  ui->tableWidget_withdraw->insertRow(ui->tableWidget_withdraw->rowCount());
  QTableWidgetItem *Item = new QTableWidgetItem;
  Item->setData(Qt::EditRole, 0.00);

  ui->tableWidget_Replenishment->setItem(row, 0, Item);
  QTableWidgetItem *Item1 = new QTableWidgetItem;
  Item1->setData(Qt::EditRole, 0.00);
  ui->tableWidget_withdraw->setItem(row, 0, Item1);
}

void Deposit_form::DeleteRow(int row_num) {
  ui->tableWidget_Replenishment->removeRow(row_num);
  ui->tableWidget_withdraw->removeRow(row_num);
}

void Deposit_form::listsPressed() {
  int months = (unsigned)ui->spinBox_months->value();
  TableListFix(months);
}

void Deposit_form::TableListFix(int months) {
  if (ui->tableWidget_Replenishment->rowCount() != months) {
    int table_rows = ui->tableWidget_Replenishment->rowCount();
    if (ui->tableWidget_Replenishment->rowCount() < months) {
      for (int j = table_rows - 1; j != months - 1; j++) {
        CreateListRow();
      }
    } else if (ui->tableWidget_Replenishment->rowCount() > months) {
      for (int j = table_rows - 1; j >= months; j--) {
        DeleteRow(j);
      }
    }
  }
}

void Deposit_form::resultPressed() {
  int months = ui->spinBox_months->value();
  double deposit = ui->doubleSpinBox_deposit_sum->value();
  double *income_list = nullptr;
  double *outcome_list = nullptr;
  income_list = new double[months]();
  outcome_list = new double[months]();
  double percent = ui->doubleSpinBox_interest->value();
  double tax = ui->doubleSpinBox_taxrate->value();
  double tax_sum = 0;
  double sum_persent = 0;
  double common_sum = 0;
  if (ui->tableWidget_Replenishment->rowCount() &&
      (ui->tableWidget_Replenishment->rowCount() != months)) {
    TableListFix(months);
  }
  for (int i = 0; i < months && (ui->tableWidget_Replenishment->rowCount());
       i++) {
    income_list[i] = ui->tableWidget_Replenishment->item(i, 0)
                         ->data(Qt::EditRole)
                         .toDouble(); 
    outcome_list[i] =
        ui->tableWidget_withdraw->item(i, 0)->data(Qt::EditRole).toDouble();
  }

  int periodicity_of_payments = ui->spinBox_periodicity->value();
  bool capitalisation = ui->checkBox_capitalisation->checkState();
  controller_->DepositCalculation(
      deposit, months, percent, periodicity_of_payments, tax, capitalisation,
      income_list, outcome_list, sum_persent, tax_sum, common_sum);
  ui->label_common_payment->setText(QString::number(common_sum, 'f', 2));
  ui->label_common_tax_payment->setText(
      QString::number(tax_sum)); 
  ui->label_interest->setText(QString::number(sum_persent));
  if (income_list)
    delete[] income_list;
  if (outcome_list)
    delete[] outcome_list;
}

} // namespace s21
