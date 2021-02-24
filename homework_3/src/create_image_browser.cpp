#include "homework_3.h"
#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace html_writer;
using namespace image_browser;

// using ScoredImage = std::tuple<std::string, float>;
// using ImageRow = std::array<ScoredImage, 3>;
auto CreateRows() {
  // generate random integer between 0.0 and 1.0
  std::vector<ImageRow> imgs_rows;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);

  std::string img_folder = "./web_app/data/";
  for (int i = 0; i < 3; i++) {
    std::vector<ScoredImage> imgs_vec;
    ImageRow imgs_row;

    for (int j = 0; j < 3; j++) {
      std::string img_filename =
          img_folder + "000" + std::to_string(i * 3 + j) + "00.png";
      float random_score = dis(gen);
      ScoredImage scored_img = std::make_tuple(img_filename, random_score);
      imgs_vec.push_back(scored_img);
    }
    // ugly way to convert std::vector to std::array
    std::move(imgs_vec.begin(), imgs_vec.begin() + imgs_vec.size(),
              imgs_row.begin());
    imgs_rows.emplace_back(imgs_row);
  }
  return imgs_rows;
}

int main() {
  auto imgs_rows = CreateRows();
  const std::string &title = "Image Browser";
  const std::string &stylesheet = "./web_app/style.css";
  CreateImageBrowser(title, stylesheet, imgs_rows);
  return 0;
}