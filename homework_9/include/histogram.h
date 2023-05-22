#ifndef HISTOGRAM_HPP_
#define HISTOGRAM_HPP_
#include "bow_dictionary.h"
#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/flann.hpp>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <vector>
namespace ipb {
class Histogram {
public:
  Histogram(){};
  Histogram(const std::vector<int> &data) { data_ = data; };
  Histogram(const cv::Mat &descriptors, BowDictionary &dictionary);
  // initiate all vector functionality
  int size() const { return data_.size(); }
  bool empty() const { return !(data_.size() > 0); }
  std::vector<int> data() const { return data_; }
  int operator[](int ind) const { return data_[ind]; }
  int &operator[](int ind) { return data_[ind]; }

  std::vector<int>::const_iterator begin() const { return data_.cbegin(); }
  std::vector<int>::const_iterator end() const { return data_.cend(); }

  std::vector<int>::const_iterator cbegin() const { return data_.cbegin(); }
  std::vector<int>::const_iterator cend() const { return data_.cend(); }

  // class io
  static Histogram ReadFromCSV(const std::string &file);
  void WriteToCSV(const std::string &file) const;
  std::ostream& operator<<(std::ostream &stream) const;
   friend std::ostream & operator <<( std::ostream& out, const Histogram& B) {
        for (int i = 0; i < B.size() - 1; i++) {
      out << B[i] << ", ";
    }
    out << B[B.size() - 1];
    return out;

    }

private:
  void histogram(const cv::Mat &descriptors, BowDictionary &dictionary);
  std::vector<int> data_;
};

} // namespace ipb

#endif