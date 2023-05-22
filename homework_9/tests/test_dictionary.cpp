// @file      test_dictionary.cpp
// @author    Ignacio Vizzo     [ivizzo@uni-bonn.de]
//
// Copyright (c) 2020 Ignacio Vizzo, all rights reserved
#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <vector>

#include <opencv2/core/mat.hpp>

#include "homework_9.h"
#include "test_data.hpp"

namespace {
const int max_iter = 10;
const int dict_size = 5;  // using Get5Kmeans() dummy data;
auto& dictionary = ipb::BowDictionary::GetInstance();

template <typename Tp>
bool inline mat_are_equal(const cv::Mat& m1, const cv::Mat& m2) {
  return std::equal(m1.begin<Tp>(), m1.end<Tp>(), m2.begin<Tp>());
}
}  // namespace

TEST(BowDictionary, BuildDictionary) {
  const auto descriptors = GetDummyData();
  dictionary.build(max_iter, dict_size, descriptors);
  ASSERT_TRUE(!dictionary.empty());
  ASSERT_EQ(dictionary.size(), dict_size);

  const auto& gt_cluster = Get5Kmeans();
  const auto& centroids = dictionary.vocabulary();

  // Need to sort the output, otherwise the comparison will fail
  cv::sort(centroids, centroids, cv::SORT_EVERY_COLUMN + cv::SORT_ASCENDING);
  EXPECT_TRUE(mat_are_equal<float>(centroids, gt_cluster))
      << "gt_centroids:\n"
      << gt_cluster << "\ncomputed centroids:\n"
      << centroids;
}

TEST(BowDictionary, BuildDictionaryFromData) {
  dictionary.set_vocabulary(Get5Kmeans());
  ASSERT_TRUE(!dictionary.empty());
  ASSERT_EQ(dictionary.size(), dict_size);

  const auto& gt_cluster = Get5Kmeans();
  const auto& centroids = dictionary.vocabulary();

  // Need to sort the output, otherwise the comparison will fail
  cv::sort(centroids, centroids, cv::SORT_EVERY_COLUMN + cv::SORT_ASCENDING);
  EXPECT_TRUE(mat_are_equal<float>(centroids, gt_cluster))
      << "gt_centroids:\n"
      << gt_cluster << "\ncomputed centroids:\n"
      << centroids;
}
