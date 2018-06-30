#include <stdio.h>
#include <string>
#include "src/equation_parser/right_way/shunting_yard_algorithm.cpp"

int main(int argc, char** argv) {
  std::cout << "Enter infix expression: ";
  string expression;
  getline(cin,expression);
  std::cout << reverse_polish(expression);
  std::cout << '\n';
}
