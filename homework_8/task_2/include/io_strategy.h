#ifndef IOSTRATEGY_HPP_
#define IOSTRATEGY_HPP_
#include <vector>
#include <string>
namespace igg{
/// Dummy structure to store relevant image data.
struct ImageData {
  int rows;
  int cols;
  int max_val;
  /// Vector of vectors of color data, e.g. {red_vec, green_vec, blue_vec},
  /// where every component, e.g. red_vec is an array of rows * cols numbers and
  /// corresponds to all the values for the red channel.
  std::vector<std::vector<int>> data;
};

class IoStrategy{
public:
    virtual ImageData Read(const std::string &file) const=0;
    virtual bool Write(const std::string &file, const ImageData &img) const=0;
};
}
#endif