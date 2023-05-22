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
  cv::Mat vocabulary() const { return codebook_; };
  void set_vocabulary(const cv::Mat vocab){this->codebook_=vocab;};
  void build(const int &n_iter, const int &size, const std::vector<cv::Mat> &descriptors);
  bool empty(const std::vector<cv::Mat> &descriptors) const {  return !(descriptors.size() > 0); };
  int size() const { 
    cv::Size s = this->codebook_.size();
    return s.height; 
    };
  bool empty() const {
    cv::Size s = this->codebook_.size();
    return s.height==0; 
  }
  
};
} // namespace ipb
#endif