#include "credit_form.h"

#include "ui_credit_form.h"
namespace s21 {
Credit_form::Credit_form(Controller *controller)
    : ui(new Ui::Credit_form), controller_(controller) {
  ui->setupUi(this);
  connect(ui->pushButton, SIGNAL(released()), this, SLOT(rowPressed()));
}

Credit_form::~Credit_form() { delete ui; }

void Credit_form ::rowPressed() {
  unsigned months = (unsigned)ui->spinBox->value();
  if (months > 0) {
    for (int i = ui->tableWidget->rowCount(); i >= 0; i--) {
      ui->tableWidget->removeRow(i);
    }
    double percent = ui->doubleSpinBox_2->value();
    double credit_sum = ui->doubleSpinBox_3->value();
    double *months_array = nullptr;
    double extra_pay = 0;
    double common_sum = 0;
    int annuitet = (ui->comboBox->currentIndex() == 1);
    controller_->CreditCalculation(credit_sum, percent, months, annuitet,
                                   &months_array, &extra_pay, &common_sum);

    for (int i = 0; i < months; i++) {
      ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    }

    for (int i = 0; i < months; i++) {
      ui->tableWidget->setItem(
          i, 0, new QTableWidgetItem(QString::number(months_array[i])));
    }
    ui->label_overpayment->setText(QString::number(extra_pay));
    ui->label_common_payment->setText(QString::number(common_sum));
    if (months_array) {
      free(months_array);
    }
  }
}
} // namespace s21
