#include "tools.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char const *argv[]) {

  // print parameter number received
  if (argc != 3) {
    printf("[ERROR] : Only two arguments allowed\n");
    exit(EXIT_FAILURE);
  } else {
    int num_list[2];
    std::string ext_list[2];
    for (int i = 1; i < argc; ++i) {
      std::istringstream is(argv[i]);
      std::string ext;
      int num;
      is >> num >> ext;
      if (ext.compare(".txt") != 0 && ext.compare(".png") != 0) {
        std::cerr << "[ERROR] : Unsupported extension format\n ";
        exit(EXIT_FAILURE);
      } else {
        if (ext.compare(".txt") == 0) {
          num_list[i - 1] = (get_first(num) + get_last(num)) / 2;
          ext_list[i - 1] = "txt";
        } else if (ext.compare(".png") == 0) {
          num_list[i - 1] = get_first(num) + get_last(num);
          ext_list[i - 1] = "png";
        }
        std::cout << "Current extension: " << ext_list[i - 1]
                  << "; Output number: " << num_list[i - 1] << std::endl;
      }
      if (ext_list[0].compare("txt") == 0 && ext_list[1].compare("png") == 0) {
        std::cout << num_list[0] << " mod " << num_list[1] << " = "
                  << num_list[0] % num_list[1] << std::endl;
      }
    }
  }
  return 0;
}