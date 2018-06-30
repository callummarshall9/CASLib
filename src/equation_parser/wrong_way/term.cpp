#include <vector>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

enum class Term_Type { Trigometric, Exponential, Polynomial, Linear, Inverse };

class Term {
public:
  Term(string string_raw_term) {
    raw_term = string_raw_term;
  }

  string get_raw_term() {
    return raw_term;
  }

  string string_replace(string str, string from, string to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length();
    } return str;
  }

  string differentiate(char respect_to) {
    Term_Type term_type = get_type(respect_to);
    string raw_format = get_raw_term();
    if(term_type == Term_Type::Linear) {
      if(raw_format.find(convert_from_char_to_string(respect_to)) == -1) {
        return convert_from_char_to_string('0');
      } else {
        return string_replace(raw_format, "x","1");
      }
    } else if(term_type == Term_Type::Polynomial) {
      return raw_format;
    }
    return raw_format;
  }

  Term_Type get_type(char respect_to) {
    string raw_term = get_raw_term();
    if(raw_term.find("/") != -1) {
      int position = raw_term.find("/");
      for(int i = 0; i < position; i = i + 1) {
        if(raw_term.at(i) == respect_to) {
          return Term_Type::Linear;
        }
      } return Term_Type::Inverse;
    } else if(raw_term.find("sin") != -1 || raw_term.find("cos") != -1) {
      return Term_Type::Trigometric;
    } else if(raw_term.find("exp") != -1) {
      return Term_Type::Exponential;
    } else if(get_raw_term().find(convert_from_char_to_string(respect_to) + "^") != -1) {
      return Term_Type::Polynomial;
    }
    return Term_Type::Linear;
  }


private:
  string raw_term;
};
