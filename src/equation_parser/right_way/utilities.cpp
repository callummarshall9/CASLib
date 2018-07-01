#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

#ifndef UTILITIES_STRING
#define UTILITIES_STRING

char valid_characters[] = {'1','2','3','4','5','6','7','8','9','0','+','-','*','/','(',')','^', ' '};

bool is_numeric_expression(string expression) {
  for(int i = 0; i < expression.size(); i++) {
    bool flag = false;
    for(int j = 0; j < sizeof(valid_characters)/sizeof(valid_characters[0]); j++) {
      if(expression.at(i) == valid_characters[j]) {
        flag = true;
      }
    }
    if(flag == false) { return false; }
  } return true;
}

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
    if(source.at(i) == token) {
      if(buffer != "") {
        strings.push_back(buffer);
        buffer = "";
      }
    } else {
      buffer = buffer + source.at(i);
    }
  }
  if(buffer != "") {
    strings.push_back(buffer);
  } return strings;
}

#endif
