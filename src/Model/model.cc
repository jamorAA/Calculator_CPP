#include "model.h"

namespace s21 {

int Model::getPriority(char operation) {
  int return_value = 0;
  if (operation == '+' || operation == '-')
    return_value = 1;
  else if (operation == 'm')
    return_value = 2;
  else if (operation == '*' || operation == '/')
    return_value = 3;
  else if (operation == 'u')
    return_value = 4;
  else if (operation == '^')
    return_value = 5;
  return return_value;
}

double Model::getRes(double operand1, double operand2,
                     const std::string& operation) {
  double result = 0;
  if (operation == "+")
    result = operand1 + operand2;
  else if (operation == "-")
    result = operand1 - operand2;
  else if (operation == "*")
    result = operand1 * operand2;
  else if (operation == "/")
    result = operand1 / operand2;
  else if (operation == "^")
    result = pow(operand1, operand2);
  else if (operation == "mod")
    result = static_cast<int>(operand1) % static_cast<int>(operand2);
  return result;
}

double Model::getFunctionRes(double arg, const std::string& function) {
  double result = 0;
  if (function == "cos")
    result = cos(arg);
  else if (function == "sin")
    result = sin(arg);
  else if (function == "tan")
    result = tan(arg);
  else if (function == "acos")
    result = acos(arg);
  else if (function == "asin")
    result = asin(arg);
  else if (function == "atan")
    result = atan(arg);
  else if (function == "sqrt")
    result = sqrt(arg);
  else if (function == "ln")
    result = log(arg);
  else if (function == "log")
    result = log10(arg);
  return result;
}

void Model::parse(const std::string str) {
  std::string number = "";
  std::string function = "";
  for (std::string::const_iterator c = str.cbegin(); c != str.cend(); ++c) {
    if ((c == str.cbegin() || *(c - 1) == '(') && (*c == '+')) {
      continue;
    } else if ((c == str.cbegin() || *(c - 1) == '(') && (*c == '-')) {
      lexems_.push_back(std::string("u"));
    } else if (std::isdigit(*c) || *c == '.' || *c == 'e' ||
               ((*c == '-' || *c == '+') && number.back() == 'e')) {
      number += *c;
    } else {
      if (!number.empty()) {
        lexems_.push_back(number);
        number = "";
      }

      if (std::string("+-*/^()x").find(*c) != std::string::npos) {
        lexems_.push_back(std::string(1, *c));
      } else if (std::isalpha(*c)) {
        function += *c;
        if ((c + 1) == str.cend() || *(c + 1) == 'x' ||
            !std::isalpha(*(c + 1))) {
          lexems_.push_back(function);
          function = "";
        }
      }
    }
  }

  if (!number.empty()) lexems_.push_back(number);
}

void Model::dijkstraAlgorithm() {
  std::vector<std::string> out;
  std::stack<std::string> st;

  for (size_t i = 0; i < lexems_.size(); ++i) {
    if (std::isdigit(lexems_[i][0]) || lexems_[i][0] == 'x') {
      out.push_back(lexems_[i]);
    } else if (std::string("actsl(").find(lexems_[i][0]) != std::string::npos) {
      st.push(lexems_[i]);
    } else if (std::string("+-*/^mu").find(lexems_[i][0]) !=
               std::string::npos) {
      while (!st.empty() &&
             getPriority(st.top()[0]) >= getPriority(lexems_[i][0]) &&
             !(('^' == st.top()[0]) == lexems_[i][0])) {
        out.push_back(st.top());
        st.pop();
      }
      st.push(lexems_[i]);
    } else if (lexems_[i][0] == ')') {
      while (st.top()[0] != '(') {
        out.push_back(st.top());
        st.pop();
      }
      st.pop();
      if (!st.empty() &&
          std::string("actsl").find(st.top()[0]) != std::string::npos) {
        out.push_back(st.top());
        st.pop();
      }
    }
  }
  while (!st.empty()) {
    out.push_back(st.top());
    st.pop();
  }

  lexems_ = std::move(out);
}

double Model::calculate(std::string str, double x) {
  parse(str);
  dijkstraAlgorithm();

  std::stack<double> st;
  double op1 = 0, op2 = 0;
  double result = 0;
  for (size_t i = 0; i < lexems_.size(); ++i) {
    if (lexems_[i][0] == 'x') {
      st.push(x);
    } else if (std::string("0123456789").find(lexems_[i][0]) !=
               std::string::npos) {
      st.push(std::stod(lexems_[i]));
    } else if (std::string("+-*/^m").find(lexems_[i][0]) != std::string::npos) {
      op2 = st.top();
      st.pop();
      op1 = st.top();
      st.pop();
      st.push(getRes(op1, op2, lexems_[i]));
    } else if (lexems_[i] == "u") {
      st.top() *= -1;
    } else if (std::string("actsl").find(lexems_[i][0]) != std::string::npos) {
      st.top() = getFunctionRes(st.top(), lexems_[i]);
    }
  }
  result = st.top();
  lexems_.clear();

  return result;
}

void Model::annuity(double totalLoanAmount, double term, double interestRate,
                    double& monthlyPayment, double& loanOverpayment,
                    double& totalPayout) {
  interestRate /= 100;
  double interestRateForPeriod = interestRate / 12;
  monthlyPayment =
      totalLoanAmount *
      (interestRateForPeriod +
       interestRateForPeriod / (pow(1 + interestRateForPeriod, term) - 1));
  totalPayout = monthlyPayment * term;
  loanOverpayment = totalPayout - totalLoanAmount;
}

void Model::differentiated(double totalLoanAmount, double term,
                           double interestRate, double& monthlyPaymentFirst,
                           double& monthlyPaymentLast, double& loanOverpayment,
                           double& totalPayout) {
  loanOverpayment = 0;
  totalPayout = 0;
  double principalDept = totalLoanAmount / term;
  interestRate /= 100;
  for (int i = 0; i < term; i++) {
    loanOverpayment += totalLoanAmount * (interestRate / 12);
    totalPayout += totalLoanAmount * (interestRate / 12) + principalDept;
    if (i == 0)
      monthlyPaymentFirst =
          totalLoanAmount * (interestRate / 12) + principalDept;
    if (i == term - 1)
      monthlyPaymentLast =
          totalLoanAmount * (interestRate / 12) + principalDept;
    totalLoanAmount -= principalDept;
  }
}

}  // namespace s21
