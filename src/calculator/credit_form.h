#ifndef CREDIT_FORM_H
#define CREDIT_FORM_H
#include <QDialog>

#include "../Controller.h"

namespace Ui {
class Credit_form;
}
namespace s21 {
class Credit_form : public QDialog {
  Q_OBJECT

public:
  explicit Credit_form(Controller *controller);
  ~Credit_form();

private slots:
  void rowPressed();

private:
  Ui::Credit_form *ui;
  Controller *controller_;
};
} // namespace s21
#endif // CREDIT_FORM_H
