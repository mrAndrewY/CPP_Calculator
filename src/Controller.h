#ifndef _SRC_CONTROLLER_H
#define _SRC_CONTROLLER_H

#include "Model.h"
namespace s21 {
class Controller {
public:
  Controller(Model *model);

  std::string InsertStringInMod(std::string &str);

  std::string ClearSymbol();

  std::string GetString();

  std::string ClearAll();

  calc_res GetRes(double x_value);

  std::string GetRpn();

  void CreditCalculation(double credit_sum, double percent, unsigned months,
                         int annuitet, double **months_array, double *extra_pay,
                         double *common_sum);
  void DepositCalculation(double deposit, int months, double percent,
                          int periodicity_of_payments, double tax_percent,
                          bool capitalisation, double *income_list,
                          double *outcome_list, double *sum_percents,
                          double *tax_sum, double *common_sum);

private:
  Model *model_;
};
} // namespace s21

#endif //  _SRC_CONTROLLER_H
