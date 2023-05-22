// @file       test_init.cpp
// @author     Igor Bogoslavskyi [igor.bogoslavskyi@gmail.com]
// @maintainer Ignacio Vizzo     [ivizzo@uni-bonn.de]
//
// Copyright (c) 2019 Igor Bogoslavskyi , all rights reserved
#include <gtest/gtest.h>

#include "homework_8.h"

using igg::Image;

TEST(TestImage, InitEmpty) {
  const Image image;
  ASSERT_EQ(0, image.rows());
  ASSERT_EQ(0, image.cols());
}

TEST(TestImage, InitEqualSize) {
  int size = 10;
  const Image image(size, size);
  ASSERT_EQ(size, image.rows());
  ASSERT_EQ(size, image.cols());
  for (int r = 0; r < image.rows(); ++r) {
    for (int c = 0; c < image.cols(); ++c) {
      ASSERT_EQ(0, image.at(r, c).red) << r << " " << c;
      ASSERT_EQ(0, image.at(r, c).green) << r << " " << c;
      ASSERT_EQ(0, image.at(r, c).blue) << r << " " << c;
    }
  }
}

TEST(TestImage, InitDiffSize) {
  int rows = 10;
  int cols = 5;
  const Image image(rows, cols);
  ASSERT_EQ(rows, image.rows());
  ASSERT_EQ(cols, image.cols());
  for (int r = 0; r < image.rows(); ++r) {
    for (int c = 0; c < image.cols(); ++c) {
      ASSERT_EQ(0, image.at(r, c).red) << r << " " << c;
      ASSERT_EQ(0, image.at(r, c).green) << r << " " << c;
      ASSERT_EQ(0, image.at(r, c).blue) << r << " " << c;
    }
  }
}

TEST(TestImage, ChangeValueOfSingleColorForPixel) {
  int size = 10;
  Image image(size, size);
  ASSERT_EQ(size, image.rows());
  ASSERT_EQ(size, image.cols());
  image.at(5, 5).red = 10;
  for (int r = 0; r < image.rows(); ++r) {
    for (int c = 0; c < image.cols(); ++c) {
      if (r == 5 && c == 5) {
        ASSERT_EQ(10, image.at(r, c).red) << r << " " << c;
        ASSERT_EQ(0, image.at(r, c).green) << r << " " << c;
        ASSERT_EQ(0, image.at(r, c).blue) << r << " " << c;
      } else {
        ASSERT_EQ(0, image.at(r, c).red) << r << " " << c;
        ASSERT_EQ(0, image.at(r, c).green) << r << " " << c;
        ASSERT_EQ(0, image.at(r, c).blue) << r << " " << c;
      }
    }
  }
}

TEST(TestImage, ChangeValueOfPixel) {
  int size = 10;
  Image image(size, size);
  ASSERT_EQ(size, image.rows());
  ASSERT_EQ(size, image.cols());
  image.at(5, 5) = {10, 11, 12};
  for (int r = 0; r < image.rows(); ++r) {
    for (int c = 0; c < image.cols(); ++c) {
      if (r == 5 && c == 5) {
        ASSERT_EQ(10, image.at(r, c).red) << r << " " << c;
        ASSERT_EQ(11, image.at(r, c).green) << r << " " << c;
        ASSERT_EQ(12, image.at(r, c).blue) << r << " " << c;
      } else {
        ASSERT_EQ(0, image.at(r, c).red) << r << " " << c;
        ASSERT_EQ(0, image.at(r, c).green) << r << " " << c;
        ASSERT_EQ(0, image.at(r, c).blue) << r << " " << c;
      }
    }
  }
}

TEST(TestImage, FailReadWriteUninitializedStrategy) {
  Image image;
  ASSERT_EQ(0, image.rows());
  ASSERT_EQ(0, image.cols());
  EXPECT_DEATH((void)image.ReadFromDisk("not_relevant"), "");
  EXPECT_DEATH((void)image.WriteToDisk("not_relevant"), "");
}
