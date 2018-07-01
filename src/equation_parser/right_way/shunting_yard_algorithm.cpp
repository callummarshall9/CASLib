#include <queue>
#include <stack>
#include <iostream>
#include <map>
#include <string>
#include <deque>
#include <vector>
#include <sstream>
#include <iostream>
#include "utilities.cpp"

using namespace std;
char operators[5] = {'+', '-', '*', '/', '^'};
std::map<char,int> precedence = {{'^',4},{'*',3},{'/',3},{'+',2},{'-',2}};

bool is_operator(char infix_token) {
  for(int j = 0; j < sizeof(operators)/sizeof(operators[0]);j++) {
    if(operators[j] == infix_token) {
      return true;
    }
  } return false;
}

string reverse_polish(string infix_source) {
  stack<char> operator_stack;
  queue<string> output_queue;
  string buffer = "";
  for(int i = 0; i < infix_source.size(); i++) {
    if(is_operator(infix_source.at(i))) {
      output_queue.push(buffer);
      buffer = "";
      while(!operator_stack.empty() && (
        precedence[operator_stack.top()] > precedence[infix_source.at(i)] ||
        precedence[operator_stack.top()] == precedence[infix_source.at(i)] && infix_source.at(i) != '^'
      ) && operator_stack.top() != '(') {
        string token = convert_from_char_to_string(operator_stack.top());
        operator_stack.pop();
        output_queue.push(token);
      }
      operator_stack.push(infix_source.at(i));
    } else if(infix_source.at(i) == '(') {
      output_queue.push(buffer);
      buffer = "";
      operator_stack.push(infix_source.at(i));
    }
    else if(infix_source.at(i) == ')') {
      output_queue.push(buffer);
      buffer = "";
      while(!operator_stack.empty() && operator_stack.top() != '(') {
        string token = convert_from_char_to_string(operator_stack.top());
        operator_stack.pop();
        output_queue.push(token);
      }
      if(!operator_stack.empty()) {
        operator_stack.pop();
      }
    } else {
      buffer = buffer + infix_source.at(i);
    }
  }
  if(buffer != "") {
    output_queue.push(buffer);
  }
  while(!operator_stack.empty()) {
    string token = convert_from_char_to_string(operator_stack.top());
    operator_stack.pop();
    output_queue.push(token);
  }
  string output_reverse_polish = "";
  while(!output_queue.empty()) {
    output_reverse_polish = output_reverse_polish + " " + output_queue.front();
    output_queue.pop();
  } return output_reverse_polish;
}
