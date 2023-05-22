#include "image.hpp"
#include <iostream>
#include <stdio.h>
namespace igg {

bool Image::ReadFromDisk(const std::string &filename) {
  if (io_strategy_ == nullptr) {
    exit(1);
  }
  ImageData img = io_strategy_->Read(filename);
  std::vector<Pixel> out_data;
  out_data.reserve(img.rows * img.cols);
  for (auto i = 0; i < img.data.size(); i++) {
    Pixel pix{img.data[i][0], img.data[i][1], img.data[i][2]};
    out_data.emplace_back(pix);
  }
  data_ = out_data;
  rows_=img.rows;
  cols_=img.cols;
  return true;
}

void Image::WriteToDisk(const std::string &filename) {
  if (io_strategy_ == nullptr) {
    exit(1);
  }
  std::vector<std::vector<int>> out_data;
  out_data.reserve(rows_ * cols_);
  for (auto i = 0; i < data_.size(); i++) {
    std::vector<int> pix{data_[i].red, data_[i].green, data_[i].blue};
    out_data.emplace_back(pix);
  }
  ImageData d;
  d.data = out_data;
  d.rows = rows_;
  d.cols = cols_;
  d.max_val = 255;
  if (io_strategy_->Write(filename, d)) {
    return;
  }
}
void Image::DownScale(int scale) {
  int rows_scaled = rows_ / scale;
  int cols_scaled = cols_ / scale;
  std::vector<Pixel> down_scaled_data;
  down_scaled_data.reserve(rows_scaled * cols_scaled);
  for (int i = 0; i < rows_; i += scale) {
    for (int j = 0; j < cols_; j += scale) {
      down_scaled_data.emplace_back(data_[i * cols_ + j]);
    }
  }
  data_ = down_scaled_data;
  rows_ = rows_scaled;
  cols_ = cols_scaled;
}

void Image::UpScale(int scale) {
  int rows_scaled = scale * rows_;
  int cols_scaled = scale * cols_;
  std::vector<Pixel> up_scaled_data(rows_scaled * cols_scaled, {0, 0, 0});

  // Iterate over the image
  for (int i = 0; i < rows_; i++) {
    int row_jump = i * scale;
    for (int j = 0; j < cols_; j++) {
      int col_jump = j * scale;
      // Fill values for upscaled image
      for (int u = 0; u < scale; u++) {
        for (int v = 0; v < scale; v++) {
          up_scaled_data[(row_jump + u) * cols_scaled + col_jump + v] =
              data_[i * cols_ + j];
        }
      }
    }
  }

  rows_ = rows_scaled;
  cols_ = cols_scaled;
  data_ = up_scaled_data;
}
} // namespace igg
