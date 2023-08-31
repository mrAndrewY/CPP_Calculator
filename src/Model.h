#ifndef _SRC_S21_MODEL_H
#define _SRC_S21_MODEL_H
#include <cmath>
#include <iostream>
#include <string>

enum stat_symb {
  EMPTY,
  FORBIDDEN,
  DIGIT,
  PLUS_MINES,
  OTHER_BINARY,
  CLOSE_BRACE,
  OPEN_BRACE,
  FIRST_FUN_SYMBOL,
  OTHER_FUN_SYMBOL,
  POINT,
  X,
  E
};
enum priority { EXTRALOW, LOW, MEDIUM, HIGH, EXTRAHIGH, ULTRA };
enum exp_status { E_CLOSED, E_NEED_DIGIT_OR_SIGN, E_NEED_DIGIT };

struct calc_res {
  bool calc_succes_;
  double result_;
};
namespace s21 {
class Model {
public:
  bool InsertSymbol(char symbol);
  calc_res GetCalcResult(double x_value = 0);
  std::string &GetString();
  void ClearStr();
  std::string GetRPN();
  void CreditCalc(double credit_sum, double percent, unsigned months,
                  int annuitet, double **months_array, double *extra_pay,
                  double *common_sum);
  void DepositPersent(double deposit, int months, double percent,
                      int periodicity_of_payments, double tax_percent,
                      bool capitalisation, double *income_list,
                      double *outcome_list, double *sum_percents,
                      double *tax_sum, double *common_sum);

  bool PartClear();
  // void GraphicProcessing();

private:
  std::string i_str_;

  struct doubles {
    double value_;
    struct doubles *next;
  };

  int StatusSymb_(char symbol);
  bool FuncParcer_(char symbol, bool &last_f_symbol);
  bool CheckNotRepeatInNumber_(char symbol);
  bool NotForbSymInBegin_(int curr_symb_status, int prev_symb_status);
  bool NotRepeating_(int curr_symb_status, int prev_symb_status, char symbol);
  bool BraceCounterOk_();
  bool PreParcer_(char symbol);
  int SymbolParcer_(int *symbol, size_t *iterator);
  std::string CrStackElem_(char symbol);
  std::string CreateRPN_();
  void PushStack_(doubles **p, double value);
  double PopStack_(doubles **p);
  double ArgProcessing_(int symbol, doubles **stack);
  double UnaryOperations_(int symbol, doubles **stack);
  int ProcessingRpn_(std::string i_str, double x_value, double &result);
  int StackElemCounter_(doubles *stack);
};

} // namespace s21

#endif //_SRC_S21_MODEL_H
