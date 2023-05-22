#include "image.hpp"
#include <iostream>
namespace igg {

bool Image::FillFromPgm(const std::string &file_name) {
  io_tools::ImageData img_data = io_tools::ReadFromPgm(file_name);
  if (img_data.data.empty()) {
    return false;
  }
  for (int i = 0; i < img_data.data.size(); i++) {
    data_.push_back(img_data.data.at(i));
  }
  rows_ = img_data.rows;
  cols_ = img_data.cols;
  return true;
}

void Image::WriteToPgm_(const std::string &file_name) {
  io_tools::ImageData image_data;
  image_data.rows = rows_;
  image_data.cols = cols_;
  image_data.data = data_;
  image_data.max_val = 255;
  if (image_data.data.empty())
    return;
  io_tools::WriteToPgm(image_data, file_name);
}
std::vector<float> Image::ComputeHistogram(int bins) const {
  float interval = 255. / bins;
  std::vector<float> histo(bins, 0.);
  for (const auto &pixel : data_) {
    float histo_val_prev = 0.;
    for (int i = 0; i < bins; i++) {
      float histo_val_current = (i + 1) * 1. * interval;
      if (pixel - histo_val_prev >= 0 && pixel - histo_val_current <= 0)
        histo[i] += 1. / data_.size();
      histo_val_prev = histo_val_current;
    }
  }
  return histo;
}
void Image::DownScale(int scale) {
  int rows_scaled = rows_ / scale;
  int cols_scaled = cols_ / scale;
  mat down_scaled_data;
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
  mat up_scaled_data(rows_scaled * cols_scaled,0);
  
	// Iterate over the image
	for (int i = 0; i < rows_; i++) {
		int row_jump = i * scale;
		for (int j = 0; j < cols_; j++) {
			int col_jump = j * scale;
			// Fill values for upscaled image
			for (int u = 0; u < scale; u++) {
				for (int v = 0; v < scale; v++) {
					up_scaled_data[(row_jump + u)*cols_scaled + col_jump + v] = data_[i * cols_ + j];
				}
			}
		}
	}

  rows_=rows_scaled;
  cols_=cols_scaled;
  data_=up_scaled_data;
}
} // namespace igg
