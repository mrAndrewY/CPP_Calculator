
#include "../test.h"
#include "../Controller.h"
#include "../Model.h"

TEST(notation, notation1) {
  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "35+489.99*23.7/86.00-5.34";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ("35 489.99 23.7 * 86.00 / + 5.34 -", controller.GetRpn());
}

TEST(notation, braces1) {

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "7+8*(36+4)/5-7";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ("7 8 36 4 + * 5 / + 7 -", controller.GetRpn());
}

TEST(notation, braces2) {

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "7+8*(36+4)";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ("7 8 36 4 + * +", controller.GetRpn());
}

TEST(notation, braces3) {
  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "7+8*(36+4)/5-7*99.7*(5+8*(7-2))^2";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ("7 8 36 4 + * 5 / + 7 99.7 * 5 8 7 2 - * + 2 ^ * -",
            controller.GetRpn());
}

TEST(notation, braces4) {

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "(36+4)";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ("36 4 +", controller.GetRpn());
}

TEST(notation, test_with_function1) {

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "6*cos4)+5";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ("6 4 c * 5 +", controller.GetRpn());
}

TEST(notation, test_with_function2) {

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "6*cos0)+5";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ("6 0 c * 5 +", controller.GetRpn());
}

TEST(notation, test_with_function_x1) {

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "6*cosx)+5";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ("6 x c * 5 +", controller.GetRpn());
}

TEST(notation, test_no_operations1) {

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "6";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ("6", controller.GetRpn());
}

TEST(notation, test_no_operations2) {

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "(6)";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ("6", controller.GetRpn());
}

TEST(notation, result_with_unary_mines) {

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "-3^2";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ("3 2 ^ ~", controller.GetRpn());
}

TEST(notation, exp) {

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "-3 E 10";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ("3E10 ~", controller.GetRpn());
}

TEST(notation, not_error) {

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = ".5+.5";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ(".5 .5 +", controller.GetRpn());
}

TEST(notation, not_error2) {

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "-(-(+(-5)))";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ("5 ~ # ~ ~", controller.GetRpn());
}

TEST(notation, not_error3) {

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "4+sinx) + 8";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ("4 x s + 8 +", controller.GetRpn());
}

TEST(notation, not_error4) {

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "sinx)+8";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ("x s 8 +", controller.GetRpn());
}

TEST(notation, not_error5) {

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "-2^2";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ("2 2 ^ ~", controller.GetRpn());
}
TEST(notation, not_error6) {

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "sin -x)";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ("x ~ s", controller.GetRpn());
}

TEST(notation, not_error7) {

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "6--6";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ("6 6 -", controller.GetRpn());
}

TEST(notation, not_error8) {

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = ".5 + .5";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ(".5 .5 +", controller.GetRpn());
}

TEST(notation, not_error9) {

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "(sin x))-5";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ("x s 5 -", controller.GetRpn());
}

TEST(notation, preparcer) {
  s21::Model mod;
  std::string test_s = "";
  EXPECT_EQ(mod.InsertSymbol(')'), false);
  EXPECT_EQ(mod.InsertSymbol('&'), false);
  EXPECT_EQ(mod.InsertSymbol('*'), false);
  EXPECT_EQ(mod.InsertSymbol('1'), true);
  EXPECT_EQ(mod.InsertSymbol('2'), true);
  EXPECT_EQ(mod.InsertSymbol('.'), true);
  EXPECT_EQ(mod.InsertSymbol('.'), false);
  EXPECT_EQ(mod.InsertSymbol('E'), true);
  EXPECT_EQ(mod.InsertSymbol('E'), false);
  EXPECT_EQ(mod.InsertSymbol('E'), false);
  EXPECT_EQ(mod.InsertSymbol('1'), true);
  EXPECT_EQ(mod.InsertSymbol('('), true);
  EXPECT_EQ(mod.InsertSymbol('+'), true);
  EXPECT_EQ(mod.InsertSymbol('*'), false);
  EXPECT_EQ(mod.InsertSymbol('E'), false);
  EXPECT_EQ(mod.InsertSymbol('c'), true);
  EXPECT_EQ(mod.InsertSymbol('3'), false);
  EXPECT_EQ(mod.InsertSymbol('o'), true);
  EXPECT_EQ(mod.InsertSymbol('*'), false);
  EXPECT_EQ(mod.InsertSymbol('s'), true);
  EXPECT_EQ(mod.InsertSymbol('5'), true);
  EXPECT_EQ(mod.InsertSymbol('+'), true);
  EXPECT_EQ(mod.InsertSymbol('1'), true);
  EXPECT_EQ(mod.InsertSymbol('E'), true);
  EXPECT_EQ(mod.InsertSymbol('+'), true);
  EXPECT_EQ(mod.InsertSymbol('.'), false);
  EXPECT_EQ(mod.InsertSymbol('1'), true);
  EXPECT_EQ(mod.InsertSymbol('+'), true);
  EXPECT_EQ(mod.InsertSymbol('.'), true);
  EXPECT_EQ(mod.InsertSymbol('*'), false);
  EXPECT_EQ(mod.InsertSymbol('1'), true);
  EXPECT_EQ(mod.InsertSymbol('+'), true);
  EXPECT_EQ(mod.InsertSymbol('9'), true);
  EXPECT_EQ(mod.InsertSymbol('.'), true);
  EXPECT_EQ(mod.InsertSymbol('('), true);
  EXPECT_EQ(mod.InsertSymbol('1'), true);
  EXPECT_EQ(mod.InsertSymbol('1'), true);
  EXPECT_EQ(mod.InsertSymbol('.'), true);
  EXPECT_EQ(mod.InsertSymbol('1'), true);
  EXPECT_EQ(mod.InsertSymbol('1'), true);
  EXPECT_EQ(mod.InsertSymbol('*'), true);
  EXPECT_EQ(mod.InsertSymbol('1'), true);
  EXPECT_EQ(mod.InsertSymbol('1'), true);
  EXPECT_EQ(mod.InsertSymbol('.'), true);
  EXPECT_EQ(mod.InsertSymbol('.'), false);
  EXPECT_EQ(mod.InsertSymbol('1'), true);
  EXPECT_EQ(mod.InsertSymbol('E'), true);
  EXPECT_EQ(mod.InsertSymbol('5'), true);
  EXPECT_EQ(mod.InsertSymbol('E'), false);
}

TEST(notation, error1) {

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "(sin x-))-5";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ(false, controller.GetRes(0).calc_succes_);
}

TEST(notation, error2) {

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "5-";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ(false, controller.GetRes(0).calc_succes_);
}

TEST(notation, error3) {
  //    std::string str_in = "(sin x";
  //    EXPECT_EQ(stack_work(str_in), "Error");

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "(sin x";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ(false, controller.GetRes(0).calc_succes_);
}

TEST(str, partclear) {
  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "13*sin x)";
  controller.InsertStringInMod(test_s);
  controller.ClearSymbol();
  controller.ClearSymbol();
  controller.ClearSymbol();
  controller.ClearSymbol();
  controller.ClearSymbol();
  controller.ClearSymbol();
  EXPECT_EQ(true, controller.GetString().empty());
}

//   TEST(notation, calculate_rpn1) {
// //    std::string str_in = "sin x)";
// //    EXPECT_EQ(stack_work(str_in), "Error");

//  s21::Model mod;
//   s21::Controller controller(&mod);
//   std::string test_s="35+489.99*23.7/86.00-5.34";
//   controller.InsertStringInMod(test_s);
//   EXPECT_EQ("35 489.99 23.7 * 86.00 / + 5.34 -", controller.GetRpn());

//   }

//  START_TEST(test_errors6) {
//   char i_str[255] = "x-";
//   char o_str[500];
//   o_str[0] = 0;
//   double result = 0;
//   stack_work(i_str, o_str);
//   processing_rpn(o_str, 0, &result);
//   ck_assert_int_eq(processing_rpn(o_str, 0, &result), 1);
//   printf("input str  : %s\n", i_str);
//   printf("output str : %s\n", o_str);
//   printf("\n_____________________\n");
//   //  printf ("\n%f\n", result );
// }
// END_TEST

// START_TEST(test_errors7) {
//   char i_str[255] = "-(-(+(-5))";
//   char o_str[500];
//   // char o_str_sample[500] = "6 x cos * 5 +";
//   o_str[0] = 0;
//   double result = 0;
//   ck_assert_int_eq(stack_work(i_str, o_str), 1);
//   processing_rpn(o_str, 0, &result);
//   ck_assert_int_eq(processing_rpn(o_str, 0, &result), 0);
//   printf("input str  : %s\n", i_str);
//   printf("output str : %s\n", o_str);
//   printf("\n_____________________\n");
//   printf("\n%f\n", result);
// }
// END_TEST

// START_TEST(test_errors8) {
//   char i_str[255] = "sin(-)";
//   char o_str[500];
//   // char o_str_sample[500] = "6 x cos * 5 +";
//   o_str[0] = 0;
//   double result = 0;
//   ck_assert_int_eq(stack_work(i_str, o_str), 0);
//   // processing_rpn(o_str, 0, &result);
//   ck_assert_int_eq(processing_rpn(o_str, 0, &result), 1);
//   printf("input str  : %s\n", i_str);
//   printf("output str : %s\n", o_str);
//   printf("\n_____________________\n");
//   printf("\n%f\n", result);
// }
// END_TEST

// START_TEST(test_errors9) {
//   char i_str[255] = "0)";
//   char o_str[500];
//   // char o_str_sample[500] = "6 x cos * 5 +";
//   o_str[0] = 0;
//   double result = 0;
//   ck_assert_int_eq(stack_work(i_str, o_str), 1);
//   printf("input str  : %s\n", i_str);
//   printf("output str : %s\n", o_str);
//   printf("\n_____________________\n");
//   printf("\n%f\n", result);
// }
// END_TEST

TEST(functions, test_mod) {

  s21::Model mod;
  s21::Controller controller(&mod);
  std::string test_s = "10%5";
  controller.InsertStringInMod(test_s);
  EXPECT_EQ("10 5 %", controller.GetRpn());
}

TEST(test_deposit, deposit) {
  s21::Model mod;
  s21::Controller controller(&mod);
  int months = 12;
  double deposit = 100000;
  double *income_list = nullptr;
  double *outcome_list = nullptr;
  income_list = new double[months]();
  outcome_list = new double[months]();
  double percent = 7;
  double tax = 0;
  double tax_sum = 0;
  double sum_persent = 0;
  double common_sum = 0;
  int periodicity_of_payments = 1;
  bool capitalisation = true;
  controller.DepositCalculation(
      deposit, months, percent, periodicity_of_payments, tax, capitalisation,
      income_list, outcome_list, &sum_persent, &tax_sum, &common_sum);
  EXPECT_NEAR(sum_persent, 7229.01, 0.01);
  if (income_list)
    delete[] income_list;
  if (outcome_list)
    delete[] outcome_list;
  income_list = nullptr;
  outcome_list = nullptr;

  months = 4;
  percent = 2;
  deposit = 11;
  capitalisation = true;
  sum_persent = 0;
  income_list = new double[months]();
  outcome_list = new double[months]();
  controller.DepositCalculation(
      deposit, months, percent, periodicity_of_payments, tax, capitalisation,
      income_list, outcome_list, &sum_persent, &tax_sum, &common_sum);
  EXPECT_NEAR(sum_persent, 0.07, 0.01);
  if (income_list)
    delete[] income_list;
  if (outcome_list)
    delete[] outcome_list;
  income_list = nullptr;
  outcome_list = nullptr;

  months = 123;
  percent = -22;
  deposit = -111;
  capitalisation = true;
  periodicity_of_payments = 2;
  sum_persent = 0;
  income_list = new double[months]();
  outcome_list = new double[months]();
  controller.DepositCalculation(
      deposit, months, percent, periodicity_of_payments, tax, capitalisation,
      income_list, outcome_list, &sum_persent, &tax_sum, &common_sum);
  EXPECT_DOUBLE_EQ(sum_persent, 0);
  if (income_list)
    delete[] income_list;
  if (outcome_list)
    delete[] outcome_list;
  income_list = nullptr;
  outcome_list = nullptr;

  months = 123;
  percent = 22;
  deposit = 111;
  capitalisation = true;
  periodicity_of_payments = 2;
  sum_persent = 1;
  income_list = new double[months]();
  outcome_list = new double[months]();
  controller.DepositCalculation(
      deposit, months, percent, periodicity_of_payments, tax, capitalisation,
      income_list, outcome_list, &sum_persent, &tax_sum, &common_sum);
  EXPECT_NEAR(sum_persent, 898.44, 1e-2);
  if (income_list)
    delete[] income_list;
  if (outcome_list)
    delete[] outcome_list;
  income_list = nullptr;
  outcome_list = nullptr;
}
// END_TEST

TEST(test_credit, credit) {
  s21::Model mod;
  s21::Controller controller(&mod);
  double credit_sum = 100000;
  double percent = 7;
  unsigned months = 12;
  double extra_pay = 0;
  double common_sum = 0;
  double *months_array = NULL;
  controller.CreditCalculation(credit_sum, percent, months, 0, &months_array,
                               &extra_pay, &common_sum);
  EXPECT_DOUBLE_EQ(extra_pay, 3791.6666666666674);
  delete[] months_array;
  months_array = nullptr;
  controller.CreditCalculation(credit_sum, percent, months, 1, &months_array,
                               &extra_pay, &common_sum);
  EXPECT_DOUBLE_EQ(extra_pay, 3836);
  delete[] months_array;
  months_array = nullptr;
}
// END_TEST

TEST(test_func, fulltest) {
  double x = 0.55;
  // double result =0;
  s21::Model mod;
  s21::Controller controller(&mod);

  std::string test_s1 = "cos x)";
  std::string test_s2 = "acos x)";
  std::string test_s3 = "sin x)";
  std::string test_s4 = "asin x)";
  std::string test_s5 = "tan x)";
  std::string test_s6 = "atan x)";
  std::string test_s7 = "sqrt x)";
  std::string test_s8 = "log x)";
  std::string test_s9 = "ln x)";
  controller.InsertStringInMod(test_s1);
  EXPECT_DOUBLE_EQ(std::cos(x), controller.GetRes(x).result_);
  controller.ClearAll();
  controller.InsertStringInMod(test_s2);
  EXPECT_DOUBLE_EQ(std::acos(x), controller.GetRes(x).result_);
  controller.ClearAll();
  controller.InsertStringInMod(test_s3);
  EXPECT_DOUBLE_EQ(std::sin(x), controller.GetRes(x).result_);
  controller.ClearAll();
  controller.InsertStringInMod(test_s4);
  EXPECT_DOUBLE_EQ(std::asin(x), controller.GetRes(x).result_);
  controller.ClearAll();
  controller.InsertStringInMod(test_s5);
  EXPECT_DOUBLE_EQ(std::tan(x), controller.GetRes(x).result_);
  controller.ClearAll();
  controller.InsertStringInMod(test_s6);
  EXPECT_DOUBLE_EQ(std::atan(x), controller.GetRes(x).result_);
  controller.ClearAll();
  controller.InsertStringInMod(test_s7);
  EXPECT_DOUBLE_EQ(std::sqrt(x), controller.GetRes(x).result_);
  controller.ClearAll();
  controller.InsertStringInMod(test_s8);
  EXPECT_DOUBLE_EQ(std::log10(x), controller.GetRes(x).result_);
  controller.ClearAll();
  controller.InsertStringInMod(test_s9);
  EXPECT_DOUBLE_EQ(std::log(x), controller.GetRes(x).result_);
}
// END_TEST

TEST(test_unary_binary, testt) {
  double x = 0.55;
  // double result =0;
  s21::Model mod;
  s21::Controller controller(&mod);

  std::string test_s1 = "+1";
  std::string test_s2 = "-1";
  std::string test_s3 = "1+1";
  std::string test_s4 = "1-2";
  std::string test_s5 = "1*2";
  std::string test_s6 = "1/2";
  std::string test_s7 = "5%2";
  std::string test_s8 = "2^2)";
  controller.InsertStringInMod(test_s1);
  EXPECT_DOUBLE_EQ(1, controller.GetRes(x).result_);
  controller.ClearAll();
  controller.InsertStringInMod(test_s2);
  EXPECT_DOUBLE_EQ(-1, controller.GetRes(x).result_);
  controller.ClearAll();
  controller.InsertStringInMod(test_s3);
  EXPECT_DOUBLE_EQ(2, controller.GetRes(x).result_);
  controller.ClearAll();
  controller.InsertStringInMod(test_s4);
  EXPECT_DOUBLE_EQ(-1, controller.GetRes(x).result_);
  controller.ClearAll();
  controller.InsertStringInMod(test_s5);
  EXPECT_DOUBLE_EQ(2, controller.GetRes(x).result_);
  controller.ClearAll();
  controller.InsertStringInMod(test_s6);
  EXPECT_DOUBLE_EQ((double)1 / 2, controller.GetRes(x).result_);
  controller.ClearAll();
  controller.InsertStringInMod(test_s7);
  EXPECT_DOUBLE_EQ(1, controller.GetRes(x).result_);
  controller.ClearAll();
  controller.InsertStringInMod(test_s8);
  EXPECT_DOUBLE_EQ(4, controller.GetRes(x).result_);
  controller.ClearAll();
}
// int main() {
//   int number_failed = 0;
//   Suite *s = suite_create("s21_calc");
//   TCase *tc_core = tcase_create("Core");
//   SRunner *sr = srunner_create(s);

//   tcase_add_test(tc_core, test_1_simple_pnotation);
//   tcase_add_test(tc_core, test_2_braces_simple_pnotation);
//   tcase_add_test(tc_core, test_2_braces_simple_pnotation1);
//   tcase_add_test(tc_core, test_3_braces_pnotation);
//   tcase_add_test(tc_core, test_4_braces_pnotation_wrong);
//   tcase_add_test(tc_core, test_5_with_functions);
//   tcase_add_test(tc_core, test_6_result_with_0);
//   tcase_add_test(tc_core, test_7_result_with_x);
//   tcase_add_test(tc_core, test_8_result_with_no_operation);
//   tcase_add_test(tc_core, test_9_result_with_no_operation);
//   tcase_add_test(tc_core, test_10_result_with_not_finished_op);
//   tcase_add_test(tc_core, test_11_result_with_unary_mines);
//   tcase_add_test(tc_core, test_not_error);
//   tcase_add_test(tc_core, test_not_error1);
//   tcase_add_test(tc_core, test_not_error2);
//   tcase_add_test(tc_core, test_errors1);
//   tcase_add_test(tc_core, test_errors2);
//   tcase_add_test(tc_core, test_errors3);
//   tcase_add_test(tc_core, test_errors4);
//   tcase_add_test(tc_core, test_errors5);
//   tcase_add_test(tc_core, test_errors6);
//   tcase_add_test(tc_core, test_errors7);
//   tcase_add_test(tc_core, test_errors8);
//   tcase_add_test(tc_core, test_errors9);
//   tcase_add_test(tc_core, test_mod);
//   tcase_add_test(tc_core, test_deposit);
//   tcase_add_test(tc_core, test_credit);
//   tcase_add_test(tc_core, test_func);
//   suite_add_tcase(s, tc_core);
//   srunner_run_all(sr, CK_NORMAL);
//   number_failed = srunner_ntests_failed(sr);
//   srunner_free(sr);
//   return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
// }
