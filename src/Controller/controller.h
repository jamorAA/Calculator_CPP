#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QString>

#include "../Model/model.h"

namespace s21 {

class Controller {
 public:
  Controller(Model* mod) : model_(mod) {}
  QString calculate(QString str, double x);
  double get_val(QString str, double x);

  void annuity(double total_loan_amount, double term, double interest_rate,
               QString& monthlyPaymentFirst, QString& loanOverpayment,
               QString& totalPayout);
  void differentiated(double total_loan_amount, double term,
                      double interest_rate, QString& monthlyPaymentFirst,
                      QString& monthlyPaymentLast, QString& loanOverpayment,
                      QString& totalPayout);

 private:
  Model* model_;
};

}  //  namespace s21

#endif  // CONTROLLER_H
