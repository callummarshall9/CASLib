#include <sstream>
#include <string>

using namespace std;

string convert_from_char_to_string(char c) {
  stringstream ss;
  ss << c;
  string output;
  ss >> output;
  return output;
}
