#include "creditcalculator.h"

#include "ui_creditcalculator.h"

CreditCalculator::CreditCalculator(s21::Controller *contr, QWidget *parent)
    : controller_(contr), QWidget(parent), ui_(new Ui::CreditCalculator) {
  ui_->setupUi(this);
}

CreditCalculator::~CreditCalculator() { delete ui_; }

void CreditCalculator::on_button_calculate_clicked() {
  if (ui_->radioButton_ann->isChecked() || ui_->radioButton_diff->isChecked()) {
    const double total_loan_amount = ui_->spinBoxTotalCreditSum->value();
    const double term = ui_->spinBoxTerm->value();
    const double interest_rate = ui_->spinBoxInterestRate->value();
    QString monthlyPaymentFirst, monthlyPaymentLast, loanOverpayment,
        totalPayout;

    if (ui_->radioButton_ann->isChecked()) {
      controller_->annuity(total_loan_amount, term, interest_rate,
                           monthlyPaymentFirst, loanOverpayment, totalPayout);
      ui_->label_monthly_payment->setText(monthlyPaymentFirst);
    } else {
      controller_->differentiated(total_loan_amount, term, interest_rate,
                                  monthlyPaymentFirst, monthlyPaymentLast,
                                  loanOverpayment, totalPayout);
      ui_->label_monthly_payment->setText(monthlyPaymentFirst + "..." +
                                          monthlyPaymentLast);
    }

    ui_->label_overpayment->setText(loanOverpayment);
    ui_->label_total_repayment->setText(totalPayout);
  }
}
