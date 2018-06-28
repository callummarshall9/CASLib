#ifndef PARSER_CPP_FILE
#define PARSER_CPP_FILE

#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include "utility.cpp"
#include "term.cpp"

using namespace std;

class Equation_Parser {
public:
  Equation parse_equation(string str) {
    vector<Term> LHS = parse_terms(str.substr(0,str.find("=")));
    vector<Term> RHS = parse_terms(str.substr(str.find("=")));
    Equation new_equation;
    new_equation.LHS = LHS;
    new_equation.RHS = RHS;
    return new_equation;
  }

  vector<Term> parse_terms(string str) {
    bool divider = false;
    bool brackets = false;
    bool LHS = true;
    string buffer = "";
    vector<Term> terms;
    for(std::string::iterator it=str.begin(); it!=str.end(); ++it) {
      char current_char = *it;
      if(current_char == '/') {
        divider = true;
      } else if(current_char == '(') {
        brackets = true;
      } else if(current_char == ')') {
        brackets = false;
      } else if(current_char == '+' && divider && !brackets) {
        divider = false;
        Term new_term(buffer);
        terms.push_back(new_term);
        buffer = "";
      } else if(current_char == '+' && !divider && !brackets) {
        Term new_term(buffer);
        terms.push_back(new_term);
        buffer = "";
      } else if(current_char == '=') {
        divider = false;
        brackets = false;
        if(buffer != "") {
          Term new_term(buffer);
          terms.push_back(new_term);
          buffer = "";
          LHS = false;
        }
      }
      if (((current_char == '+' || current_char == '=') && !divider && !brackets) == false) {
        buffer = buffer + current_char;
      }
    }
    Term new_term(buffer);
    terms.push_back(new_term);
    return terms;
  }
};

#endif
