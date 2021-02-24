#include <filesystem>
#include <iostream>
#include <string>
namespace fs = std::filesystem;

int main() {
  std::string s = "../src/test.cpp";
  fs::path aPath{s};

  // https://en.cppreference.com/w/cpp/filesystem
  std::cout << "exists() = " << fs::exists(aPath) << "\n"
            << "root_name() = " << aPath.root_name() << "\n"
            << "root_path() = " << aPath.root_path() << "\n"
            << "relative_path() = " << aPath.relative_path() << "\n"
            << "parent_path() = " << aPath.parent_path() << "\n"
            << "filename() = " << aPath.filename() << "\n"
            << "stem() = " << aPath.stem() << "\n"
            << "extension() =  " << aPath.extension() << "\n";

  return 0;
}