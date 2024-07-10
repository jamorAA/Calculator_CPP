#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(s21::Controller *contr, QWidget *parent)
    : controller_(contr),
      QMainWindow(parent),
      ui_(new Ui::MainWindow),
      creditcalculator_(contr),
      depositcalculator_(contr) {
  ui_->setupUi(this);

  connect(ui_->pushButton_0, SIGNAL(clicked()), this, SLOT(digitsSlot()));
  connect(ui_->pushButton_1, SIGNAL(clicked()), this, SLOT(digitsSlot()));
  connect(ui_->pushButton_2, SIGNAL(clicked()), this, SLOT(digitsSlot()));
  connect(ui_->pushButton_3, SIGNAL(clicked()), this, SLOT(digitsSlot()));
  connect(ui_->pushButton_4, SIGNAL(clicked()), this, SLOT(digitsSlot()));
  connect(ui_->pushButton_5, SIGNAL(clicked()), this, SLOT(digitsSlot()));
  connect(ui_->pushButton_6, SIGNAL(clicked()), this, SLOT(digitsSlot()));
  connect(ui_->pushButton_7, SIGNAL(clicked()), this, SLOT(digitsSlot()));
  connect(ui_->pushButton_8, SIGNAL(clicked()), this, SLOT(digitsSlot()));
  connect(ui_->pushButton_9, SIGNAL(clicked()), this, SLOT(digitsSlot()));

  connect(ui_->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(operationsSlot()));
  connect(ui_->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(operationsSlot()));
  connect(ui_->pushButton_mul, SIGNAL(clicked()), this, SLOT(operationsSlot()));
  connect(ui_->pushButton_dev, SIGNAL(clicked()), this, SLOT(operationsSlot()));
  connect(ui_->pushButton_mod, SIGNAL(clicked()), this, SLOT(operationsSlot()));
  connect(ui_->pushButton_pow, SIGNAL(clicked()), this, SLOT(operationsSlot()));

  connect(ui_->pushButton_leftbracket, SIGNAL(clicked()), this,
          SLOT(bracketsSlot()));
  connect(ui_->pushButton_rightbracket, SIGNAL(clicked()), this,
          SLOT(bracketsSlot()));

  connect(ui_->pushButton_sin, SIGNAL(clicked()), this, SLOT(functionsSlot()));
  connect(ui_->pushButton_cos, SIGNAL(clicked()), this, SLOT(functionsSlot()));
  connect(ui_->pushButton_tan, SIGNAL(clicked()), this, SLOT(functionsSlot()));
  connect(ui_->pushButton_asin, SIGNAL(clicked()), this, SLOT(functionsSlot()));
  connect(ui_->pushButton_acos, SIGNAL(clicked()), this, SLOT(functionsSlot()));
  connect(ui_->pushButton_atan, SIGNAL(clicked()), this, SLOT(functionsSlot()));
  connect(ui_->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(functionsSlot()));
  connect(ui_->pushButton_log, SIGNAL(clicked()), this, SLOT(functionsSlot()));
  connect(ui_->pushButton_ln, SIGNAL(clicked()), this, SLOT(functionsSlot()));
  connect(ui_->pushButton_x, SIGNAL(clicked()), this, SLOT(functionsSlot()));
}

MainWindow::~MainWindow() { delete ui_; }

int MainWindow::findLastOperatorsIndex() {
  const QString line = ui_->label_line->text();

  int lastIndex = -1;
  QString symbols = "+-*/^d(";

  for (int i = line.length() - 1; i >= 0; i--) {
    QChar ch = line.at(i);

    if (symbols.contains(ch)) {
      lastIndex = i;
      break;
    }
  }

  return lastIndex;
}

void MainWindow::digitsSlot() {
  QPushButton *button = (QPushButton *)sender();
  const QString line = ui_->label_line->text();
  const qsizetype len = line.length();
  const QString current_sym = button->text();
  const QChar last_sym = line.at(len - 1);
  const int lastIndex = findLastOperatorsIndex();

  const QString correct_prev_sym = "0123456789.e(*/+-^d";

  if ((len == 1 && last_sym == '0') || line == "Error")
    ui_->label_line->setText(current_sym);
  else if (correct_prev_sym.contains(last_sym) &&
           !(lastIndex == len - 2 && last_sym == '0' && current_sym == '0'))
    ui_->label_line->setText(line + current_sym);
}

void MainWindow::operationsSlot() {
  QPushButton *button = (QPushButton *)sender();
  const QString line = ui_->label_line->text();
  const QString current_sym = button->text();
  const QChar last_sym = line.at(line.length() - 1);

  const QString correct_prev_sym = "0123456789sntgx)";

  if (line == "Error" && (current_sym == '-' || current_sym == '+'))
    ui_->label_line->setText(current_sym);
  else if ((last_sym == '(' || last_sym == 'e') &&
           (current_sym == '-' || current_sym == '+'))
    ui_->label_line->setText(line + current_sym);
  else if (correct_prev_sym.contains(last_sym))
    ui_->label_line->setText(line + current_sym);
}

void MainWindow::bracketsSlot() {
  QPushButton *button = (QPushButton *)sender();
  const QString line = ui_->label_line->text();
  const QString current_sym = button->text();
  const QChar last_sym = line.at(line.length() - 1);
  const int open_count = line.count('(');
  const int close_count = line.count(')');

  const QString operators = "+-*/d^(";

  if (current_sym == '(' &&
      ((line.length() == 1 && last_sym == '0') || line == "Error"))
    ui_->label_line->setText(current_sym);
  else if (current_sym == '(' && operators.contains(last_sym))
    ui_->label_line->setText(line + current_sym);
  else if (current_sym == ')' && !operators.contains(last_sym) &&
           open_count > close_count && last_sym != '.')
    ui_->label_line->setText(line + current_sym);
}

void MainWindow::functionsSlot() {
  QPushButton *button = (QPushButton *)sender();
  QString line = ui_->label_line->text();
  const QString current_sym = button->text();
  const QChar last_sym = line.at(line.length() - 1);

  const QString operators = "+-*/d^(";

  if (line.length() == 1 && last_sym == '0') line = "";

  if (line == "" || operators.contains(last_sym)) {
    if (current_sym == "x")
      ui_->label_line->setText(line + current_sym);
    else
      ui_->label_line->setText(line + current_sym + '(');
  }
}

void MainWindow::on_pushButton_del_clicked() { ui_->label_line->setText("0"); }

void MainWindow::on_pushButton_backspace_clicked() {
  QString line = ui_->label_line->text();
  QChar last_sym = line.at(line.length() - 1);

  line = line.left(line.length() - 1);
  if (line != "" && last_sym != 'x') last_sym = line.at(line.length() - 1);
  while (line != "" && last_sym != 'e' && last_sym != 'x' &&
         last_sym.isLetter()) {
    line = line.left(line.length() - 1);
    if (line != "") last_sym = line.at(line.length() - 1);
  }

  if (line == "")
    ui_->label_line->setText("0");
  else
    ui_->label_line->setText(line);
}

void MainWindow::on_pushButton_dot_clicked() {
  const QString line = ui_->label_line->text();
  const QChar last_sym = line.at(line.length() - 1);
  const int lastIndex = findLastOperatorsIndex();

  const QString digits = "0123456789";

  if (!(line.mid(lastIndex + 1).contains('.')) &&
      !(line.mid(lastIndex + 1).contains('e')) && last_sym != ')' &&
      last_sym != 'x') {
    if (!digits.contains(last_sym))
      ui_->label_line->setText(line + "0.");
    else
      ui_->label_line->setText(line + ".");
  }
}

void MainWindow::on_pushButton_e_clicked() {
  const QString line = ui_->label_line->text();
  const QChar last_sym = line.at(line.length() - 1);
  const int lastIndex = findLastOperatorsIndex();

  const QString digits = "0123456789";

  if (!line.mid(lastIndex + 1).contains('e') && digits.contains(last_sym))
    ui_->label_line->setText(line + "e");
}

void MainWindow::on_pushButton_result_clicked() {
  const QString line = ui_->label_line->text();
  const QChar last_sym = line.at(line.length() - 1);

  const QString digits = "0123456789x";
  const int open_count = line.count('(');
  const int close_count = line.count(')');

  if (line == "Error")
    ui_->label_line->setText("0");
  else if ((last_sym == ')' || digits.contains(last_sym)) &&
           open_count == close_count) {
    QString result_str = controller_->calculate(line, ui_->x_value->value());
    ui_->label_line->setText(result_str);
  }
}

void MainWindow::on_pushButton_build_clicked() {
  const QString line = ui_->label_line->text();
  const QChar last_sym = line.at(line.length() - 1);

  const QString digits = "0123456789.x";
  const int open_count = line.count('(');
  const int close_count = line.count(')');
  if (line.length() >= 1 && line.count('x') >= 1 &&
      (last_sym == ')' || digits.contains(last_sym)) &&
      open_count == close_count) {
    const double x_min = ui_->x_min->value();
    const double x_max = ui_->x_max->value();
    const double y_min = ui_->y_min->value();
    const double y_max = ui_->y_max->value();

    const double h = 0.001;
    const double xBegin = x_min;
    const double xEnd = x_max + h;

    QVector<double> x, y;

    ui_->widget->removeGraph(0);
    ui_->widget->replot();

    ui_->widget->xAxis->setRange(x_min, x_max);
    ui_->widget->yAxis->setRange(y_min, y_max);

    for (double X = xBegin; X <= xEnd; X += h) {
      x.push_back(X);
      y.push_back(controller_->get_val(line, X));
    }

    ui_->widget->addGraph();
    ui_->widget->graph(0)->addData(x, y);
    ui_->widget->replot();
  }
}

void MainWindow::on_pushButton_credit_clicked() { creditcalculator_.show(); }

void MainWindow::on_pushButton_deposit_clicked() { depositcalculator_.show(); }
