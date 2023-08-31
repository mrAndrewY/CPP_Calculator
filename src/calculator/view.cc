#include "view.h"

#include "graphic.h"
#include "ui_view.h"
namespace s21 {
View::View(Controller *controller)
    : ui(new Ui::View), QMainWindow(nullptr), controller_(controller),
      graphic_(controller), d_form_(controller), c_form_(controller) {
  ui->setupUi(this);
  ui->Display->setText("0");
  ui->Display_result->setText("_");
  QPushButton *digitbuttons[10];
  for (int i = 0; i < 11; i++) {
    QString buttName = "pushButton_" + QString::number(i);
    digitbuttons[i] = View::findChild<QPushButton *>(buttName);
    connect(digitbuttons[i], SIGNAL(released()), this, SLOT(buttonPressed()));
    // std::cout<<"here";
  }
  QPushButton *binaryOps[6];
  for (int i = 0; i < 6; i++) {
    QString buttName = "pushButtonBin_" + QString::number(i);
    binaryOps[i] = View::findChild<QPushButton *>(buttName);
    connect(binaryOps[i], SIGNAL(released()), this, SLOT(buttonPressed()));
  }

  QPushButton *funcbuttons[9];
  for (int i = 1; i < 10; i++) {
    QString buttName = "pushButton_func_" + QString::number(i);
    funcbuttons[i] = View::findChild<QPushButton *>(buttName);
    connect(funcbuttons[i], SIGNAL(released()), this, SLOT(buttonPressed()));
  }

  connect(ui->pushButton_x, SIGNAL(released()), this, SLOT(buttonPressed()));
  connect(ui->pushButton_dot, SIGNAL(released()), this, SLOT(buttonPressed()));
  connect(ui->pushButton_Braces_open, SIGNAL(released()), this,
          SLOT(buttonPressed()));
  connect(ui->pushButton_Braces_close, SIGNAL(released()), this,
          SLOT(buttonPressed()));

  connect(ui->pushButton_result, SIGNAL(released()), this,
          SLOT(resultPressed()));
  connect(ui->pushButton_Clear, SIGNAL(released()), this, SLOT(clearPressed()));
  connect(ui->pushButton_backspace, SIGNAL(released()), this,
          SLOT(backspacePressed()));

  connect(ui->pushButton_graph, SIGNAL(released()), this, SLOT(graphPressed()));
  connect(ui->pushButton_credit, SIGNAL(released()), this,
          SLOT(creditPressed()));
  connect(ui->pushButton_deposit, SIGNAL(released()), this,
          SLOT(depositPressed()));
}

View::~View() { delete ui; }

void View::buttonPressed() {
  QPushButton *button = (QPushButton *)sender();
  QString btext = button->text();
  if (btext == "mod")
    btext = "%";
  if (btext == "exp")
    btext = "E";
  ui->Display->clear();
  std::string add_text = btext.toStdString();
  ui->Display->setText(
      QString::fromStdString(controller_->InsertStringInMod(add_text)));
}
void View::clearPressed() {
  controller_->ClearAll();
  ui->Display->setText(QString::fromStdString(controller_->GetString()) + "0");
}

void View::resultPressed() {
  calc_res res = controller_->GetRes(ui->x_box->value());
  if (res.calc_succes_) {
    ui->Display_result->setText(QString::number(res.result_, 'g', 9));
  } else {
    ui->Display_result->setText("Error");
  }
}

void View::backspacePressed() {
  ui->Display->clear();
  controller_->ClearSymbol();
  ui->Display->setText(QString::fromStdString(controller_->GetString()));
};

void View::graphPressed() {
  // graphic_;
  graphic_.getFormula(QString::fromStdString(controller_->GetString()));
  // graphic_.get_controller(controller_);
  graphic_.makeGraph();
  graphic_.exec();
}

void View::creditPressed() {
  // Credit_form credit;
  c_form_.exec();
}

void View::depositPressed() {
  // Deposit_form deposit;
  d_form_.exec();
}

} // namespace s21
//  if (ui->Display->text().size() > 0) {
//    QChar last_char = ui->Display->text().back();
//    if (last_char != ')') {
//      if ((last_char >= '0' && last_char <= '9' || last_char == '.')) {
//        ui->Display->setText(ui->Display->text() + button->
//        ui->Display->setText(ui->Display->text() + ' ' + button->text());
//      }
//    }
//  } else {
//    ui->Display->setText(ui->Display->text() + button->text());
//  }
//}

// void MainWindow::buttonPressed() {
//   QPushButton *button = (QPushButton *)sender();
//   delete_zero(ui->Display, button->text().back());
//   if (ui->Display->text().size() > 0) {
//     QChar last_char = ui->Display->text().back();
//     if (last_char != ')') {
//       if ((last_char >= '0' && last_char <= '9' || last_char == '.')) {
//         ui->Display->setText(ui->Display->text() + button->text());
//       } else {
//         ui->Display->setText(ui->Display->text() + ' ' + button->text());
//       }
//     }
//   } else {
//     ui->Display->setText(ui->Display->text() + button->text());
//   }
