#include "depositcalculator.h"

#include "ui_depositcalculator.h"

DepositCalculator::DepositCalculator(s21::Controller *contr, QWidget *parent)
    : controller_(contr), QWidget(parent), ui_(new Ui::DepositCalculator) {
  ui_->setupUi(this);
}

DepositCalculator::~DepositCalculator() { delete ui_; }
