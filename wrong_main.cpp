#include <stdio.h>
#include "src/equation_parser/wrong_way/parser.cpp"

void output_terms(std::string title, vector<Term> terms) {
  std::cout << title;
  std::cout << ": ";
  std::cout << terms.size();
  std::cout << "\n";
  for(int i = 0; i < terms.size(); i = i + 1) {
    std::cout << terms[i].get_raw_term();
    Term_Type current_term_type = terms[i].get_type('x');
    if(current_term_type == Term_Type::Trigometric) {
      std::cout << " (Trig)";
    } else if(current_term_type == Term_Type::Linear) {
      std::cout << " (Linear) \n";
      std::cout << terms[i].differentiate('x');
      std::cout << " (Derivative)";
    } else if(current_term_type == Term_Type::Exponential) {
      std::cout << " (Exponential)";
    } else if(current_term_type == Term_Type::Polynomial) {
      std::cout << " (Polynomial)";
    } else if(current_term_type == Term_Type::Inverse) {
      std::cout << " (Inverse)";
    }
    std::cout << '\n';
  }
}

std::string get_equation() {
  char equation_input[100];
  std::cout << "Enter equation: ";
  std::cin.getline(equation_input, sizeof(equation_input));
  std::string equation_string = std::string(equation_input);
  if(equation_string == "Default") {
    return "5/(x+3)+3+x^2+3/(2*x^2)=0";
  } else {
    return equation_string;
  }
}

int main(int argc, char** argv) {
  Equation_Parser parser;
  std::string equation_input = get_equation();
  Equation equation = parser.parse_equation(equation_input);
  output_terms("LHS terms count", equation.LHS);
  output_terms("RHS terms count", equation.RHS);
}
