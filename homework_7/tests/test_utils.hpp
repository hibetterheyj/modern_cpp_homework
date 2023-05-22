// @file      test_utils.hpp
// @author    Ignacio Vizzo     [ivizzo@uni-bonn.de]
//
// Copyright (c) 2020 Ignacio Vizzo, all rights reserved
#ifndef TEST_UTILS_HPP_
#define TEST_UTILS_HPP_

#include <algorithm>

#include <opencv2/core/mat.hpp>

template <typename Tp>
bool inline mat_are_equal(const cv::Mat& m1, const cv::Mat& m2) {
  return std::equal(m1.begin<Tp>(), m1.end<Tp>(), m2.begin<Tp>());
}

#endif
