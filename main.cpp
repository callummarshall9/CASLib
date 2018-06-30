#include <stdio.h>
#include <string>
#include "src/equation_parser/right_way/shunting_yard_algorithm.cpp"
#include "src/equation_parser/right_way/postfix_evaluator.cpp"

int main(int argc, char** argv) {
  std::cout << "Enter infix expression: ";
  string expression;
  getline(cin,expression);
  string postfix_expression = reverse_polish(expression);
  std::cout << reverse_polish(expression);
  std::cout << '\n';
  int result = evaluate(postfix_expression);
  std::cout << result;
  std::cout << '\n';
}
