#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

#ifndef UTILITIES_STRING
#define UTILITIES_STRING

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
