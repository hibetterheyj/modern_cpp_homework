#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include "io_strategy.h"
#include <memory>
#include <string>
#include <vector>
namespace igg {
class Image {
public:
  struct Pixel {
    int red;
    int green;
    int blue;
  };
  // constructors
  Image() = default;
  Image(int rows, int cols) {
    rows_ = rows;
    cols_ = cols;
    std::vector<Pixel> d(rows * cols, {0, 0, 0});
    data_ = d;
  };
  Image(Image &&var) = default;
  Image(const Image &var) = default;
  Image &operator=(Image &&var) = default;
  Image &operator=(Image &var) = default;

  // getters
  const int &rows() const { return rows_; }
  const int &cols() const { return cols_; }
  // Get and set pixel values
  const Pixel &at(int row, int col) const { return data_[row * cols_ + col]; }
  Pixel &at(int row, int col) { return data_[row * cols_ + col]; }
  // Copied from
  // https://github.com/sbrhss/Modern-CPP-Bonn/blob/master/HW3/igg_image/src/igg_image/image.cpp
  void DownScale(int scale);

  // Copied from
  // https://github.com/sbrhss/Modern-CPP-Bonn/blob/master/HW3/igg_image/src/igg_image/image.cpp
  void UpScale(int scale);

  inline void SetIoStrategy(std::shared_ptr<IoStrategy> strategy_ptr) {
    io_strategy_ = strategy_ptr;
  }

  bool ReadFromDisk(const std::string &filename);

  void WriteToDisk(const std::string &filename);

private:
  int rows_ = 0;
  int cols_ = 0;
  std::vector<Pixel> data_;
  std::shared_ptr<IoStrategy> io_strategy_ = nullptr;
};
} // namespace igg
#endif