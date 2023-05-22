#ifndef BOWDIC_HPP_
#define BOWDIC_HPP_
#include <algorithm>
#include <functional>
#include <map>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <random>
#include <set>
#include <string>
#include <vector>
#include "codebook.h"
namespace ipb {
class BowDictionary {
private:
  // constructor and destructor
  BowDictionary() = default;
  ~BowDictionary() = default;
  int n_iter_ = 0;
  int k_ = 0;
  std::vector<cv::Mat> descriptors_;
  cv::Mat codebook_;

public:
  // copy assignment operators
  BowDictionary(const BowDictionary &var) = delete;
  void operator=(const BowDictionary &var) = delete;
  BowDictionary(const BowDictionary &&var) = delete;
  void operator=(const BowDictionary &&var) = delete;
  // one time object instance
  static BowDictionary &GetInstance() {
    static BowDictionary instance;
    return instance;
  };

  // getter methods
  int max_iterations() const { return n_iter_; };
std::vector<cv::Mat> descriptors() const { return descriptors_; };
cv::Mat vocabulary() const { return codebook_; };
int total_features() const {
  int total=0;
  //TODO: (descriptors_.size()-1)*descriptors_[0].rows) the same than total? 
  for(const auto &descriptor: descriptors_)
    total+=descriptor.rows;
  return total;
}; // number of input features
// setter methods
void set_max_iterations(int iter_) { n_iter_ = iter_; }
void set_size(int n) {
    codebook_= cv::Mat::zeros(n, descriptors_[0].size().width, CV_64F);
 }
void set_descriptors(const std::vector<cv::Mat> &input);
void set_params(int n_iter, int size, const std::vector<cv::Mat> &descriptors);
int size() const {
  cv::Size s = this->codebook_.size();
  return s.height;
};
bool empty() const {
  cv::Size s = this->codebook_.size();
  return s.height == 0;
}
}; // namespace ipb
} // namespace ipb
#endif