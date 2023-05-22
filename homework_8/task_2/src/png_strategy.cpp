#include "png_strategy.h"

namespace igg {
ImageData PngIoStrategy::Read(const std::string &file) const {
  png::image<png::rgb_pixel> image(file,
                                   png::require_color_space<png::rgb_pixel>());
  ImageData out;
  out.rows = image.get_height();
  out.cols = image.get_width();
  out.max_val= 255;
  for (png::uint_32 y = 0; y < image.get_height(); ++y) {
    for (png::uint_32 x = 0; x < image.get_width(); ++x) {
      std::vector<int> pix{image[y][x].red, image[y][x].green,
                           image[y][x].blue};
      out.data.emplace_back(pix);
    }
  }
  return out;
}

bool PngIoStrategy::Write(const std::string &file, const ImageData &img) const {
  png::image<png::rgb_pixel> image(img.rows, img.cols);
  for (png::uint_32 i = 0; i < img.rows; i++) {
    for (png::uint_32 j = 0; j < img.cols; j++) {
      std::vector<int> pix = img.data[i * img.cols + j];
      image[i][j] = png::rgb_pixel(pix[0], pix[1], pix[2]);
    }
  }
  image.write(file);
  return true;
}
} // namespace igg