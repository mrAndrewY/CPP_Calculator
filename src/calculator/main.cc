#include <QApplication>

#include "../Controller.h"
#include "view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  s21::Controller controller(&model);
  s21::View w(&controller);
  w.show();
  return a.exec();
}
