#include <filesystem>
#include <iomanip>
#include <iostream>
#include <string>

int main() {
  // test print with precision
  // #include <iomanip>
  std::cout << std::setprecision(2) << std::fixed << 1.23456 << "\n";
  // test filename splitting with <filesystem>
  std::string s = "a/../data/000000.png";
  std::string delimiter = "/";
  std::string token = s;
  while (token.find(delimiter) != std::string::npos) {
    std::cout << "token = " << token << std::endl;
    token = token.substr(token.find(delimiter) + 1,
                         token.length()); // token is "scott"
    std::cout << "current token = " << token << std::endl;
  }
  std::cout << "final token = " << token << std::endl;
  // test with raw output
  std::cout << R"(<div class="column" style=" border: 5px solid green;">)"
            << std::endl;

  return 0;
}