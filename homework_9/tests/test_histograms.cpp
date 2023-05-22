// @file      test_histograms.cpp
// @author    Ignacio Vizzo     [ivizzo@uni-bonn.de]
//
// Copyright (c) 2020 Ignacio Vizzo, all rights reserved
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include <opencv2/core/mat.hpp>

#include "homework_9.h"
#include "test_data.hpp"

namespace {
auto& dictionary = ipb::BowDictionary::GetInstance();
std::vector<int> gt_histogram_data{5, 5, 5, 5, 5};
}  // namespace

TEST(Histogram, EmptyDescriptors) {
  dictionary.set_vocabulary(Get5Kmeans());
  cv::Mat empty;
  auto histogram = ipb::Histogram(empty, dictionary);
  ASSERT_TRUE(histogram.empty());
  ASSERT_EQ(histogram.size(), 0);
}

TEST(Histogram, CreateFromDictionary) {
  dictionary.set_vocabulary(Get5Kmeans());
  const auto& descriptors = GetAllFeatures();
  auto histogram = ipb::Histogram(descriptors, dictionary);
  ASSERT_TRUE(!histogram.empty());
  ASSERT_GT(histogram.size(), 0);
  ASSERT_EQ(histogram.size(), dictionary.size())
      << "The numbers of bins in the histogram must match the number of words "
         "in the dictionary";

  ASSERT_EQ(gt_histogram_data, histogram.data());
}

TEST(Histogram, PrintToStdout) {
  dictionary.set_vocabulary(Get5Kmeans());
  auto histogram = ipb::Histogram(GetAllFeatures(), dictionary);
  ASSERT_TRUE(!histogram.empty());
  ASSERT_GT(histogram.size(), 0);

  testing::internal::CaptureStdout();
  std::cout << histogram;
  std::string cout = testing::internal::GetCapturedStdout();
  ASSERT_THAT(cout, testing::HasSubstr("5, 5, 5, 5, 5"));
}

TEST(Histogram, ReadWriteCSV) {
  dictionary.set_vocabulary(Get5Kmeans());
  auto histogram = ipb::Histogram(GetAllFeatures(), dictionary);
  ASSERT_TRUE(!histogram.empty());
  ASSERT_GT(histogram.size(), 0);

  std::string filename("/tmp/test_histogram.csv");
  ipb::Histogram csv_histogram;
  EXPECT_NO_THROW(histogram.WriteToCSV(filename));
  EXPECT_NO_THROW(csv_histogram = ipb::Histogram::ReadFromCSV(filename));
  ASSERT_EQ(histogram.data(), csv_histogram.data());
}

TEST(Histogram, Iterators) {
  dictionary.set_vocabulary(Get5Kmeans());
  const auto& descriptors = GetAllFeatures();
  auto histogram = ipb::Histogram(descriptors, dictionary);
  ASSERT_TRUE(!histogram.empty());
  ASSERT_GT(histogram.size(), 0);

  for (const auto& bin : histogram) {
    // Do nothing,if this works, then the iterators also work!
    (void)bin;
  }

  // Accumulate all bins in histogram
  int sum = std::accumulate(histogram.begin(), histogram.end(), 0);
  ASSERT_EQ(sum, descriptors.rows)
      << "The number of the input descriptors must match the sum of all the "
         "bins in the histogram, check the homework diagram";
}

TEST(Histogram, ConstIterators) {
  dictionary.set_vocabulary(Get5Kmeans());
  const auto& descriptors = GetAllFeatures();
  const auto histogram = ipb::Histogram(descriptors, dictionary);
  ASSERT_TRUE(!histogram.empty());
  ASSERT_GT(histogram.size(), 0);

  for (const auto& bin : histogram) {
    // Do nothing,if this works, then the iterators also work!
    (void)bin;
  }

  std::string gt_hist{"5, 5, 5, 5, 5"};
  std::stringstream ss;
  ss << "bins = [";
  std::copy(histogram.cbegin(), histogram.cend(),
            std::ostream_iterator<int>(ss, ", "));
  ss << "\b\b]";
  testing::internal::CaptureStdout();
  std::cout << ss.str();
  std::string cout = testing::internal::GetCapturedStdout();
  ASSERT_THAT(cout, testing::HasSubstr(gt_hist)) << ss.str();
}

TEST(Histogram, AccessOperators) {
  dictionary.set_vocabulary(Get5Kmeans());
  const auto& descriptors = GetAllFeatures();
  auto histogram = ipb::Histogram(descriptors, dictionary);
  ASSERT_TRUE(!histogram.empty());
  ASSERT_GT(histogram.size(), 0);

  for (size_t i = 0; i < histogram.size(); i++) {
    histogram[i]++;
    gt_histogram_data[i]++;
  }
  ASSERT_EQ(gt_histogram_data, histogram.data());

  const auto& const_hist = histogram;
  for (size_t i = 0; i < histogram.size(); i++) {
    (void)const_hist[i];
  }
}

TEST(Histogram, NonTrivialExample) {
  dictionary.set_vocabulary(Get5Kmeans());
  const auto& descriptors = Get3Features();
  auto histogram = ipb::Histogram(descriptors, dictionary);
  ASSERT_TRUE(!histogram.empty());
  ASSERT_GT(histogram.size(), 0);
  ASSERT_EQ(histogram.size(), dictionary.size())
      << "The numbers of bins in the histogram must match the number of words "
         "in the dictionary";

  // we have:
  //  05,  05,  05,  05,  05,  05,  05,  05,  05 <--- closest cluster == 1 (00)
  //  15,  15,  15,  15,  15,  15,  15,  15,  15 <--- closest cluster == 2 (20)
  // 115, 115, 115, 115, 115, 115, 115, 115, 115 <--- closest cluster == 5 (80)
  // Therefore, the histogram must look like: bins [1, 1, 0, 0, 1]
  std::vector<int> res{1, 1, 0, 0, 1};
  ASSERT_EQ(res, histogram.data());
}
