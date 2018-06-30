#include <queue>
#include <stack>
#include <iostream>
#include <map>
#include <string>
#include <deque>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;
char operators[7] = {'+', '-', '*', '/', '^', '(', ')'};
std::map<char,int> precedence = {{'^',4},{'*',3},{'/',3},{'+',2},{'-',2}};

string convert_from_char_to_string(char c) {
  stringstream ss;
  ss << c;
  string output;
  ss >> output;
  return output;
}

vector<string> split(string source, char token) {
  vector<string> strings;
  string buffer = "";
  for(int i = 0; i < source.size();i++) {
    if(source[i] == token) {
      strings.push_back(buffer);
    } else {
      buffer = buffer + source.at(i);
    }
  }
  if(buffer != "") {
    strings.push_back(buffer);
  } return strings;
}

bool is_operator(char infix_token) {
  for(int j = 0; j < sizeof(operators)/sizeof(operators[0]);j++) {
    if(operators[j] == infix_token) {
      return true;
    }
  } return false;
}

void handle_operator(char operand, stack<char> *operator_stack, queue<string> *output_queue) {
  if(operand == ')') {
    while(!operator_stack->empty() && operator_stack->top() != '(') {
      string current_operator_token = convert_from_char_to_string(operator_stack->top());
      output_queue->push(current_operator_token);
      operator_stack->pop();
    }
    if(!operator_stack->empty()) {
      operator_stack->pop();
    }
  } else if(!operator_stack->empty() && operand != '(' &&
      (
      precedence[operand] < precedence[operator_stack->top()] ||
      (precedence[operand] == precedence[operator_stack->top()] && operand != '^')
      )) {
    string current_operator_token = convert_from_char_to_string(operator_stack->top());
    output_queue->push(current_operator_token);
    operator_stack->pop();
    operator_stack->push(operand);
  } else {
    operator_stack->push(operand);
  }
}

string reverse_polish(string infix_source) {
  queue<string> output_queue;
  stack<char> operator_stack;
  string buffer = "";
  for(int i = 0; i < infix_source.size(); i++) {
    if(is_operator(infix_source.at(i))) {
      output_queue.push(buffer);
      buffer = "";
      handle_operator(infix_source.at(i), &operator_stack, &output_queue);
    } else {
      buffer = buffer + infix_source.at(i);
    }
  }
  if(buffer != "") {
    output_queue.push(buffer);
  }
  /*for(int i = 0; i < infix.size(); i++) {
    if(is_operator(infix[i])) {
      output_queue.push(buffer);
      buffer = "";
      operator_stack.push(infix.at(i));
    } else {
      buffer = buffer + infix.at(i);
    }
  }*/
  string output_reverse_polish = "";
  while(!output_queue.empty()) {
    output_reverse_polish = output_reverse_polish + " " + output_queue.front();
    output_queue.pop();
  }
  while(!operator_stack.empty()) {
    output_reverse_polish = output_reverse_polish + " " + operator_stack.top();
    operator_stack.pop();
  }
  return output_reverse_polish;
}
