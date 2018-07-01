#include <stack>
#include <deque>
#include <string>
#include <math.h>
#include "utilities.cpp"

using namespace std;

int evaluate_numeric(vector<string> tokens) {
  stack<int> postfix_stack;
  int result_numeric = 0;
  for(int i = 0; i < tokens.size(); i++) {
    const char* result_operand = tokens[i].c_str();
    if(is_operator(result_operand[0])) {
      int operand_two = postfix_stack.top();
      postfix_stack.pop();
      int operand_one = postfix_stack.top();
      postfix_stack.pop();
      if(tokens.at(i) == "+") {
        result_numeric = operand_one + operand_two;
      } else if(tokens.at(i) == "-") {
        result_numeric = operand_one - operand_two;
      } else if(tokens.at(i) == "*") {
        result_numeric = operand_one * operand_two;
      } else if (tokens.at(i) == "/") {
        result_numeric = operand_one / operand_two;
      } else if(tokens.at(i) == "^") {
        result_numeric = pow(operand_one, operand_two);
      }
      postfix_stack.push(result_numeric);
    } else {
      postfix_stack.push(stoi(tokens.at(i)));
    }
  } return postfix_stack.top();
}

string evaluate_symbol(vector<string> tokens) {
  stack<string> postfix_stack;
  string result_symbolic = "";
  for(int i = 0; i < tokens.size(); i++) {
    const char* result_operand = tokens.at(i).c_str();
    if(is_operator(result_operand[0])) {
      string operand_two = postfix_stack.top();
      postfix_stack.pop();
      string operand_one = postfix_stack.top();
      postfix_stack.pop();
      if(tokens.at(i) == "+") {
        if(operand_one == operand_two) {
          result_symbolic = "2*" + operand_one;
        } else {
          result_symbolic = "(" + operand_one + "+" + operand_two + ")";
        }
      } else if(tokens.at(i) == "-") {
        if(operand_one == operand_two) {
          result_symbolic = "0";
        } else {
          result_symbolic = "(" + operand_one + "-" + operand_two + ")";
        }
      } else if(tokens.at(i) == "*") {
        if(operand_one == operand_two) {
          result_symbolic = operand_one + "^2";
        } else {
          if(is_numeric_expression(operand_one)) {
            result_symbolic = operand_one + "*" + operand_two;
          } else {
            result_symbolic =  operand_two + "*" + operand_one;
          }
        }
      } else if(tokens.at(i) == "/") {
        if(operand_one == operand_two) {
          result_symbolic = "1";
        } else {
          result_symbolic =  operand_one + "/" + operand_two;
        }
      } else if(tokens.at(i) == "^") {
        result_symbolic = operand_one + "^" + operand_two ;
      }
      postfix_stack.push(result_symbolic);
    } else {
      postfix_stack.push(tokens.at(i));
    }
  } return postfix_stack.top();
}

string evaluate(string expression) {
  vector<string> tokens = split(expression, ' ');
  if(is_numeric_expression(expression)) {
    int result = evaluate_numeric(tokens);
    return "Numeric result: " + to_string(result);
  } else {
    return "Symbolic expression: " + evaluate_symbol(tokens);
  }
  return "Hello world!";
}
