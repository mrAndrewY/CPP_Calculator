#ifndef GRAPHIC_H
#define GRAPHIC_H
#include "../Controller.h"
#include <QDialog>

namespace Ui {
class graphic;
}
namespace s21 {
class graphic : public QDialog {
  Q_OBJECT

public:
  explicit graphic(Controller *controller_);
  ~graphic();
  // void get_controller(Controller * controller){ controller_=controller;}
public slots:
  void makeGraph();
  void getFormula(QString str);
  void plotPressed();
private slots:

  void checkBox_step_pressed();

private:
  Ui::graphic *ui;
  Controller *controller_;
};
} // namespace s21
#endif // GRAPHIC_H
