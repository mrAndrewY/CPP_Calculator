#ifndef DEPOSIT_FORM_H
#define DEPOSIT_FORM_H
#include <QDialog>

#include "../Controller.h"

namespace Ui {
class Deposit_form;
}

namespace s21 {
class Deposit_form : public QDialog {
  Q_OBJECT

public:
  explicit Deposit_form(Controller *controller_);
  ~Deposit_form();

private slots:
  void listsPressed();
  void resultPressed();

private:
  Ui::Deposit_form *ui;
  Controller *controller_;

  void CreateListRow();
  void DeleteRow(int row_num);
  void TableListFix(int months);
};
} // namespace s21
#endif // DEPOSIT_FORM_H
