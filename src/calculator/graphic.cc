#include "graphic.h"
#include <QMainWindow>

//#include "../Controller.h"

#include "ui_graphic.h"
namespace s21 {
graphic::graphic(Controller *controller)
    : ui(new Ui::graphic), controller_(controller) {
  ui->setupUi(this);
  // graphic::makeGraph(Controller * controller);
  connect(ui->pushButton_makePlot, SIGNAL(released()), this,
          SLOT(plotPressed()));
  connect(ui->checkBox_step, SIGNAL(released()), this,
          SLOT(checkBox_step_pressed()));
}

graphic::~graphic() { delete ui; }

void graphic::getFormula(QString str) { ui->Formula->setText(str); }

void graphic::plotPressed() { makeGraph(); }

void graphic::checkBox_step_pressed() {
  ui->stepSpinBox->setEnabled(ui->checkBox_step->checkState());
}

void graphic::makeGraph() {

  ui->label_warning->setText("");

  std::string o_str = controller_->GetString();
  double x_value_left = -10;
  double x_value_right = 10;
  double y_value_up = -10;
  double y_value_down = 10;
  bool correct_limits = (ui->left_x_box->value() < ui->right_x_box->value()) &&
                        (ui->left_y_box->value() < ui->right_y_box->value());
  if (correct_limits) {
    x_value_left = ui->left_x_box->value();
    x_value_right = ui->right_x_box->value();
    y_value_down = ui->left_y_box->value();
    y_value_up = ui->right_y_box->value();
    int x_value_l = (int)x_value_left;
    // int step = 1;
    //  generate some data:s
    double diff = x_value_right - x_value_left;
    double step = 1;
    if (diff > 1000000)
      step = 20;
    if (diff > 500000 && diff <= 1000000)
      step = 10;
    if (diff > 250000 && diff <= 500000)
      step = 5;
    if (diff > 100000 && diff <= 250000)
      step = 2;
    if (diff <= 100000 && diff > 20000)
      step = 1;
    if (diff <= 200000 && diff > 1000)
      step = 0.5;
    if (diff <= 1000 && diff > 100)
      step = 0.1;
    if (diff <= 100)
      step = 0.01;
    if (ui->checkBox_step->checkState() && ui->stepSpinBox->value() > 0)
      step = ui->stepSpinBox->value();
    int points_quantity = (int)diff / step;
    QVector<double> x(points_quantity), y(points_quantity);
    if (controller_->GetRes(0).calc_succes_) {
      for (int i = 0; i < points_quantity; ++i) {
        x[i] = x_value_left;
        x_value_left += step;
        y[i] = controller_->GetRes(x[i]).result_;
      }
    } else {
      ui->label_warning->setText("Please check the formula!");
    }

    ui->plot->addGraph();
    ui->plot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->plot->xAxis->setRange(x_value_l, x_value_right);
    ui->plot->yAxis->setRange(y_value_down, y_value_up);
    ui->plot->replot();
  } else {
    ui->label_warning->setText("Please check the limits!");
    ui->plot->graph(0)->data()->clear();
    ui->plot->replot();
    // give the axes some labels:
    ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("y");
  }
}
} // namespace s21
