// @file       test_from_png.cpp
// @author     Igor Bogoslavskyi [igor.bogoslavskyi@gmail.com]
// @maintainer Ignacio Vizzo     [ivizzo@uni-bonn.de]
//
// Copyright (c) 2019 Igor Bogoslavskyi , all rights reserved
#include <gtest/gtest.h>

#include "homework_8.h"

using igg::Image;
using igg::PngIoStrategy;

TEST(TestImageFromPng, InitFromFileSize) {
  Image image;
  image.SetIoStrategy(std::make_shared<PngIoStrategy>());
  ASSERT_EQ(0, image.rows());
  ASSERT_EQ(0, image.cols());
  ASSERT_TRUE(image.ReadFromDisk("../../tests/data/dummy_file.png"));
  ASSERT_EQ(10, image.rows());
  ASSERT_EQ(10, image.cols());
}

TEST(TestImageFromPng, InitFromFileContents) {
  Image image;
  image.SetIoStrategy(std::make_shared<PngIoStrategy>());
  ASSERT_EQ(0, image.rows());
  ASSERT_EQ(0, image.cols());
  ASSERT_TRUE(image.ReadFromDisk("../../tests/data/dummy_file.png"));
  ASSERT_EQ(10, image.rows());
  ASSERT_EQ(10, image.cols());
  for (int r = 0; r < image.rows(); ++r) {
    for (int c = 0; c < image.cols(); ++c) {
      if (r == c) {
        ASSERT_EQ(255, image.at(r, c).red) << r << " " << c;
        ASSERT_EQ(255, image.at(r, c).green) << r << " " << c;
        ASSERT_EQ(255, image.at(r, c).blue) << r << " " << c;
      } else {
        ASSERT_EQ(0, image.at(r, c).red) << r << " " << c;
        ASSERT_EQ(0, image.at(r, c).green) << r << " " << c;
        ASSERT_EQ(0, image.at(r, c).blue) << r << " " << c;
      }
    }
  }
}
