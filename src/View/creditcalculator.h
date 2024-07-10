#ifndef CREDITCALCULATOR_H
#define CREDITCALCULATOR_H

#include <QWidget>

#include "../Controller/controller.h"

namespace Ui {
class CreditCalculator;
}

class CreditCalculator : public QWidget {
  Q_OBJECT

 public:
  explicit CreditCalculator(s21::Controller *contr, QWidget *parent = nullptr);
  ~CreditCalculator();

 private slots:
  void on_button_calculate_clicked();

 private:
  Ui::CreditCalculator *ui_;
  s21::Controller *controller_;
};

#endif  // CREDITCALCULATOR_H
