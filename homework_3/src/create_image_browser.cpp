#include "homework_3.h"
#include <iostream>
#include <random>
#include <string>
using namespace html_writer;
using namespace image_browser;

// using ScoredImage = std::tuple<std::string, float>;
// using ImageRow = std::array<ScoredImage, 3>;
auto CreateRows() {
  std::string img_folder = "./web_app/data/";
  std::random_device rd;
  std::mt19937 gen(rd());
  // generate random integer between 0 and 99
  std::uniform_real_distribution<> dis(0.0, 1.0);
  for (int i = 0; i < 10; i++) {
    std::string img_filename =
        img_folder + "000" + std::to_string(i) + "00.png";
    float random_score = dis(gen);
    ScoredImage scored_img = std::make_tuple(img_filename, random_score);
    std::cout << img_filename << " " << random_score << "\n";
  }
  return 0;
}

int main() {
  CreateRows();
  const std::string &title = "Image Browser";
  const std::string &stylesheet = "./web_app/style.css";
  // std::cout << title << "\n";
  OpenDocument();
  AddTitle(title);
  AddCSSStyle(stylesheet);
  OpenBody();
  OpenRow();
  CloseRow();
  CloseBody();
  CloseDocument();
  return 0;
}