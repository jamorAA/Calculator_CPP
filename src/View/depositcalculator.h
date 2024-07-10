#ifndef DEPOSITCALCULATOR_H
#define DEPOSITCALCULATOR_H

#include <QWidget>

#include "../Controller/controller.h"

namespace Ui {
class DepositCalculator;
}

class DepositCalculator : public QWidget {
  Q_OBJECT

 public:
  explicit DepositCalculator(s21::Controller *contr, QWidget *parent = nullptr);
  ~DepositCalculator();

 private:
  Ui::DepositCalculator *ui_;
  s21::Controller *controller_;
};

#endif  // DEPOSITCALCULATOR_H
