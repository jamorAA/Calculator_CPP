#ifndef MODEL_H
#define MODEL_H

#include <cmath>
#include <stack>
#include <string>
#include <vector>

namespace s21 {

class Model {
 public:
  Model() {}
  double calculate(std::string str, double x);
  void annuity(double totalLoanAmount, double term, double interestRate,
               double& monthlyPayment, double& loanOverpayment,
               double& totalPayout);
  void differentiated(double totalLoanAmount, double term, double interestRate,
                      double& monthlyPaymentFirst, double& monthlyPaymentLast,
                      double& loanOverpayment, double& totalPayout);

 private:
  std::vector<std::string> lexems_;

  int getPriority(char operation);
  double getRes(double operand1, double operand2, const std::string& operation);
  double getFunctionRes(double arg, const std::string& function);
  void parse(const std::string str);
  void dijkstraAlgorithm();
};

}  // namespace s21

#endif  // MODEL_H
