#ifndef PARSER_CPP_FILE
#define PARSER_CPP_FILE

#include <vector>
#include <iostream>
#include <string>

using namespace std;

enum class Term_Type { Trigometric, Exponential, Polynomial, Linear };
bool DEBUG_PARSER = true;

class Term {
public:
  Term(string string_raw_term) {
    raw_term = string_raw_term;
  }

  string get_raw_term() {
    return raw_term;
  }

  string differentiate() {
    Term_Type term_type = get_type();
    string raw_format = get_raw_term();
    if(term_type == Term_Type::Linear) {
      return replace(raw_format.begin(),raw_format.end(),"x","(1)");
    } else if(term_type == Term_Type::Polynomial) {
      return raw_format;
    }
    return raw_format;
  }

  Term_Type get_type() {
    if(get_raw_term().find("*") != -1) {
      if(DEBUG_PARSER) {
        std::cout << "CASLib error: Product of terms";
      }
    } else {
      if(get_raw_term().find("sin") != -1 || get_raw_term().find("cos") != -1) {
        return Term_Type::Trigometric;
      } else if(get_raw_term().find("exp") != -1) {
        return Term_Type::Exponential;
      } else if(get_raw_term().find("x^") != -1) {
        return Term_Type::Polynomial;
      }
    }
    return Term_Type::Linear;
  }


private:
  string raw_term;
};

class Equation {
public:
  vector<Term> LHS;
  vector<Term> RHS;
};

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
