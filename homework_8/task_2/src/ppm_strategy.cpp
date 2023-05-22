#include "ppm_strategy.h"

namespace igg {
ImageData PpmIoStrategy::Read(const std::string &file) const {
  std::ifstream in(file, std::ios_base::in);
  if (!in) {
    return {0, 0, 0, {}};
  }

  // Read integers, if we read chars, we get 1 digit instead of the whole number
  std::string type;
  int rows = 0;
  int cols = 0;
  int max_val = 0;
  std::vector<std::vector<int>> data;
  in >> type >> rows >> cols >> max_val;

  data.reserve(rows * cols);
  int red = 0, green= 0, blue=0;
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      in >> red >> green >> blue;
      std::vector<int> pix{red,green,blue};
      data.emplace_back(pix);
    }
  }
  return {rows, cols, max_val, data};
}

bool PpmIoStrategy::Write(const std::string &file, const ImageData &img) const {
  std::ofstream out(file);
  if (!out) {
    return false;
  }

  out << "P3" << std::endl;
  out << img.rows << " " << img.cols << std::endl;
  out << img.max_val << std::endl;
  for (int r = 0; r < img.rows; ++r) {
    for (int c = 0; c < img.cols; ++c) {
      out << img.data[r * img.cols + c][0] << " "
          << img.data[r * img.cols + c][1] << " "
          << img.data[r * img.cols + c][2];
    }
    out << std::endl;
  }
  return true;
}
} // namespace igg