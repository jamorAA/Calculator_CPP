#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../Controller/controller.h"
#include "creditcalculator.h"
#include "depositcalculator.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
  Q_OBJECT

 public:
  MainWindow(s21::Controller *contr, QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui_;
  s21::Controller *controller_;
  CreditCalculator creditcalculator_;
  DepositCalculator depositcalculator_;

  int findLastOperatorsIndex();

 private slots:
  void digitsSlot();
  void operationsSlot();
  void bracketsSlot();
  void functionsSlot();
  void on_pushButton_del_clicked();
  void on_pushButton_backspace_clicked();
  void on_pushButton_dot_clicked();
  void on_pushButton_e_clicked();
  void on_pushButton_result_clicked();
  void on_pushButton_build_clicked();
  void on_pushButton_credit_clicked();
  void on_pushButton_deposit_clicked();
};

#endif  // MAINWINDOW_H
