#include "controller.h"

namespace s21 {
QString Controller::calculate(QString str, double x) {
  std::string s = str.toStdString();
  double result = model_->calculate(s, x);
  QString return_string = QString::number(result, 'f', 7);

  if (QString("nf").contains(return_string.at(return_string.length() - 1)))
    return QString("Error");

  return return_string;
}

double Controller::get_val(QString str, double x) {
  std::string s = str.toStdString();
  return model_->calculate(s, x);
}

void Controller::annuity(double total_loan_amount, double term,
                         double interest_rate, QString& monthlyPaymentFirst,
                         QString& loanOverpayment, QString& totalPayout) {
  double monthlyPaymentFirst_d;
  double loanOverpayment_d;
  double totalPayout_d;
  model_->annuity(total_loan_amount, term, interest_rate, monthlyPaymentFirst_d,
                  loanOverpayment_d, totalPayout_d);
  monthlyPaymentFirst = QString::number(monthlyPaymentFirst_d, 'f', 2);
  loanOverpayment = QString::number(loanOverpayment_d, 'f', 2);
  totalPayout = QString::number(totalPayout_d, 'f', 2);
}

void Controller::differentiated(double total_loan_amount, double term,
                                double interest_rate,
                                QString& monthlyPaymentFirst,
                                QString& monthlyPaymentLast,
                                QString& loanOverpayment,
                                QString& totalPayout) {
  double monthlyPaymentFirst_d;
  double monthlyPaymentLast_d;
  double loanOverpayment_d;
  double totalPayout_d;
  model_->differentiated(total_loan_amount, term, interest_rate,
                         monthlyPaymentFirst_d, monthlyPaymentLast_d,
                         loanOverpayment_d, totalPayout_d);
  monthlyPaymentFirst = QString::number(monthlyPaymentFirst_d, 'f', 2);
  monthlyPaymentLast = QString::number(monthlyPaymentLast_d, 'f', 2);
  loanOverpayment = QString::number(loanOverpayment_d, 'f', 2);
  totalPayout = QString::number(totalPayout_d, 'f', 2);
}
}  // namespace s21
