// @file       test_histogram.cpp
// @author     Igor Bogoslavskyi [igor.bogoslavskyi@gmail.com]
// @maintainer Ignacio Vizzo     [ivizzo@uni-bonn.de]
//
// Copyright (c) 2019 Igor Bogoslavskyi , all rights reserved
#include <gtest/gtest.h>

#include <iostream>

#include "homework_6.h"

using igg::Image;

TEST(TestHistogram, OneBinHistogram) {
  Image image;
  ASSERT_EQ(0, image.rows());
  ASSERT_EQ(0, image.cols());
  ASSERT_TRUE(image.FillFromPgm("../../tests/data/dummy_file.pgm"));
  const auto& image_ref = image;
  auto histogram = image_ref.ComputeHistogram(1);
  ASSERT_EQ(1, histogram.size());
  float eps = 0.001f;
  ASSERT_NEAR(1.0f, histogram.front(), eps);
}

TEST(TestHistogram, WhiteImageBlackDiagonal) {
  Image image;
  ASSERT_EQ(0, image.rows());
  ASSERT_EQ(0, image.cols());
  ASSERT_TRUE(image.FillFromPgm("../../tests/data/dummy_file.pgm"));
  const auto& image_ref = image;
  int size = 10;
  auto histogram = image_ref.ComputeHistogram(size);
  ASSERT_EQ(size, histogram.size());
  float eps = 0.001f;
  ASSERT_NEAR(0.1f, histogram[0], eps);
  ASSERT_NEAR(0.9f, histogram[9], eps);
}
