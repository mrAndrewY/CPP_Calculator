#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Model.h"

void s21::Model::CreditCalc(double credit_sum, double percent, unsigned months,
                            int annuitet, double **months_array,
                            double *extra_pay, double *common_sum) {
  double monthly_common_payment = 0;
  double t_credit_sum = credit_sum;
  if (!annuitet) {
    monthly_common_payment = t_credit_sum / months;
    *months_array = new double[months]();
    for (unsigned int i = 0; i < months; i++) {
      double extra_pay_month = (t_credit_sum * percent / 100) / months;
      (*months_array)[i] = (extra_pay_month + monthly_common_payment);
      t_credit_sum -= monthly_common_payment;
      *extra_pay += extra_pay_month;
    }
  } else {
    if (percent > 0) {
      double monthly_persent_state = percent / (100 * 12);
      *months_array = new double[months]();
      ;
      for (unsigned int i = 0; i < months; i++) {
        (*months_array)[i] =
            round((t_credit_sum * monthly_persent_state /
                   (1 - pow(1 + monthly_persent_state, -((int)months)))));
      }

      *extra_pay = (months * (*months_array)[0]) - credit_sum;
    }
  }

  *common_sum = *extra_pay + credit_sum;
}

void s21::Model::DepositPersent(double deposit, int months, double percent,
                                int periodicity_of_payments, double tax_percent,
                                bool capitalisation, double *income_list,
                                double *outcome_list, double *sum_percents,
                                double *tax_sum, double *common_sum) {
  bool mistake = (percent <= 0 || deposit <= 0 || months <= 0);
  if (!mistake) {
    if (periodicity_of_payments == 0)
      periodicity_of_payments = 1;
    int months_remainder = months % periodicity_of_payments;
    for (int i = 0; i < months; i++) {
      deposit += (income_list[i] - outcome_list[i]);
      if (!capitalisation ||
          (periodicity_of_payments > 1 && months_remainder != 0 &&
           i >= months - months_remainder)) {
        *sum_percents += (deposit * percent / (100 * 12));
      } else {
        if (((i + 1) % periodicity_of_payments == 0 &&
             i >= periodicity_of_payments - 1) ||
            periodicity_of_payments == 1) {
          *sum_percents += ((deposit + (*sum_percents)) *
                            (percent / (100 * 12)) * periodicity_of_payments);
        }
      }
    }
    *tax_sum = tax_percent * (*sum_percents / (100 * 12)) * months;

  } else {
    *common_sum = deposit;
    *sum_percents = 0;
  }
}
