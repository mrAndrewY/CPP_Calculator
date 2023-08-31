#ifndef VIEW_H
#define VIEW_H
#include <QMainWindow>

#include "../Controller.h"
#include "credit_form.h"
#include "deposit_form.h"
#include "graphic.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {
class View : public QMainWindow {
  Q_OBJECT

public:
  View(Controller *controller = nullptr);
  ~View();

private:
  Ui::View *ui;
  Controller *controller_;
  graphic graphic_;
  Deposit_form d_form_;
  Credit_form c_form_;

private slots:
  void buttonPressed();
  void clearPressed();
  void resultPressed();
  void backspacePressed();
  void graphPressed();
  void depositPressed();
  void creditPressed();

signals:
  void newTextEntered(const QString &text);
};
} // namespace s21
#endif // VIEW_H
