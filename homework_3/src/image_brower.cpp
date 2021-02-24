#include "homework_3.h"
#include <iostream>

using namespace html_writer;
using namespace image_browser;

// using ScoredImage = std::tuple<std::string, float>;
// using ImageRow = std::array<ScoredImage, 3>;

void image_browser::AddFullRow(const ImageRow &row, bool first_row) {
  bool highlight = false;
  if (first_row == true) {
    highlight = true;
  }
  OpenRow();
  for (const auto &scored_image_tuple : row) {
    auto [img_path, score] = scored_image_tuple;
    // std::cout << "value of text: " << scored_image_tuple << std::endl;
    AddImage(img_path, score, highlight);
  }
  CloseRow();
}

void image_browser::CreateImageBrowser(const std::string &title,
                                       const std::string &stylesheet,
                                       const std::vector<ImageRow> &rows) {
  OpenDocument();
  AddTitle(title);
  AddCSSStyle(stylesheet);
  OpenBody();
  int counter = 0;
  for (const auto &row : rows) {
    counter++;
    if (counter == 1) {
      image_browser::AddFullRow(row, true);
    } else {
      image_browser::AddFullRow(row);
    }
  }
  CloseBody();
  CloseDocument();
}