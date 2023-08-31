#include "Controller.h"

s21::Controller::Controller(Model *model) : model_(model){};

std::string s21::Controller::InsertStringInMod(std::string &str) {
  for (size_t i = 0; i < str.size(); i++) {
    model_->InsertSymbol(str[i]);
  }
  return model_->GetString();
}

std::string s21::Controller::ClearSymbol() {
  model_->PartClear();
  return model_->GetString();
  ;
}

std::string s21::Controller::GetString() {
  return model_->GetString();
  ;
}

std::string s21::Controller::ClearAll() {
  model_->ClearStr();
  return model_->GetString();
}

std::string s21::Controller::GetRpn() { return model_->GetRPN(); }

calc_res s21::Controller::GetRes(double x_value) {
  return model_->GetCalcResult(x_value);
}

void s21::Controller::CreditCalculation(double credit_sum, double percent,
                                        unsigned months, int annuitet,
                                        double **months_array,
                                        double *extra_pay, double *common_sum) {
  model_->CreditCalc(credit_sum, percent, months, annuitet, months_array,
                     extra_pay, common_sum);
}
void s21::Controller::DepositCalculation(
    double deposit, int months, double percent, int periodicity_of_payments,
    double tax_percent, bool capitalisation, double *income_list,
    double *outcome_list, double *sum_percents, double *tax_sum,
    double *common_sum)

{
  model_->DepositPersent(deposit, months, percent, periodicity_of_payments,
                         tax_percent, capitalisation, income_list, outcome_list,
                         sum_percents, tax_sum, common_sum);
}
