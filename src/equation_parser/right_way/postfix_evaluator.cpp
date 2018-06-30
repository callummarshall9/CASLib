#include <stack>
#include <deque>
#include <string>
#include <math.h>
#include "utilities.cpp"

using namespace std;

int evaluate(string expression) {
  vector<string> tokens = split(expression, ' ');
  stack<int> postfix_stack;
  int result = 0;
  for(int i = 0; i < tokens.size(); i++) {
    const char* result_operand = tokens[i].c_str();
    if(is_operator(result_operand[0])) {
      int operand_two = postfix_stack.top();
      postfix_stack.pop();
      int operand_one = postfix_stack.top();
      postfix_stack.pop();
      if(tokens.at(i) == "+") {
        result = result + operand_one + operand_two;
      } else if(tokens.at(i) == "-") {
        result = result + operand_one - operand_two;
      } else if(tokens.at(i) == "*") {
        result = result + operand_one * operand_two;
      } else if (tokens.at(i) == "/") {
        result = result + operand_one / operand_two;
      } else if(tokens.at(i) == "^") {
        result = result + pow(operand_one, operand_two);
      }
    } else {
      postfix_stack.push(stoi(tokens.at(i)));
    }

  } return result;
}
