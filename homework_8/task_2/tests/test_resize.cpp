// @file       test_resize.cpp
// @author     Igor Bogoslavskyi [igor.bogoslavskyi@gmail.com]
// @maintainer Ignacio Vizzo     [ivizzo@uni-bonn.de]
//
// Copyright (c) 2019 Igor Bogoslavskyi , all rights reserved
#include <gtest/gtest.h>

#include "homework_8.h"

using igg::Image;

namespace {
void FillDiagonalForTesting(Image* image) {
  for (int r = 0; r < image->rows(); ++r) {
    for (int c = 0; c < image->cols(); ++c) {
      if (r == c) {
        image->at(r, c) = {0, 0, 0};
      } else {
        image->at(r, c) = {255, 255, 255};
      }
    }
  }
}
}  // namespace

TEST(TestResize, DownScaleTrivial) {
  int size = 10;
  Image image(size, size);
  ASSERT_EQ(size, image.rows());
  ASSERT_EQ(size, image.cols());
  FillDiagonalForTesting(&image);
  image.DownScale(1);
  ASSERT_EQ(size, image.rows());
  ASSERT_EQ(size, image.cols());
  for (int r = 0; r < image.rows(); ++r) {
    for (int c = 0; c < image.cols(); ++c) {
      if (r == c) {
        ASSERT_EQ(0, image.at(r, c).red) << r << " " << c;
        ASSERT_EQ(0, image.at(r, c).green) << r << " " << c;
        ASSERT_EQ(0, image.at(r, c).blue) << r << " " << c;
      } else {
        ASSERT_EQ(255, image.at(r, c).red) << r << " " << c;
        ASSERT_EQ(255, image.at(r, c).green) << r << " " << c;
        ASSERT_EQ(255, image.at(r, c).blue) << r << " " << c;
      }
    }
  }
}

TEST(TestResize, DownScale) {
  int size = 10;
  Image image(size, size);
  ASSERT_EQ(size, image.rows());
  ASSERT_EQ(size, image.cols());
  FillDiagonalForTesting(&image);
  int new_rows = image.rows() / 2;
  int new_cols = image.cols() / 2;
  image.DownScale(2);
  ASSERT_EQ(new_rows, image.rows());
  ASSERT_EQ(new_cols, image.cols());
  for (int r = 0; r < image.rows(); ++r) {
    for (int c = 0; c < image.cols(); ++c) {
      if (r == c) {
        ASSERT_EQ(0, image.at(r, c).red) << r << " " << c;
        ASSERT_EQ(0, image.at(r, c).green) << r << " " << c;
        ASSERT_EQ(0, image.at(r, c).blue) << r << " " << c;
      } else {
        ASSERT_EQ(255, image.at(r, c).red) << r << " " << c;
        ASSERT_EQ(255, image.at(r, c).green) << r << " " << c;
        ASSERT_EQ(255, image.at(r, c).blue) << r << " " << c;
      }
    }
  }
}

TEST(TestResize, UpScaleTrivial) {
  int size = 10;
  Image image(size, size);
  ASSERT_EQ(size, image.rows());
  ASSERT_EQ(size, image.cols());
  FillDiagonalForTesting(&image);
  image.UpScale(1);
  ASSERT_EQ(10, image.rows());
  ASSERT_EQ(10, image.cols());
  for (int r = 0; r < image.rows(); ++r) {
    for (int c = 0; c < image.cols(); ++c) {
      if (r == c) {
        ASSERT_EQ(0, image.at(r, c).red) << r << " " << c;
        ASSERT_EQ(0, image.at(r, c).green) << r << " " << c;
        ASSERT_EQ(0, image.at(r, c).blue) << r << " " << c;
      } else {
        ASSERT_EQ(255, image.at(r, c).red) << r << " " << c;
        ASSERT_EQ(255, image.at(r, c).green) << r << " " << c;
        ASSERT_EQ(255, image.at(r, c).blue) << r << " " << c;
      }
    }
  }
}

TEST(TestResize, UpScale) {
  int size = 10;
  Image image(size, size);
  ASSERT_EQ(size, image.rows());
  ASSERT_EQ(size, image.cols());
  FillDiagonalForTesting(&image);
  int scale = 2;
  int new_rows = image.rows() * scale;
  int new_cols = image.cols() * scale;
  image.UpScale(scale);
  ASSERT_EQ(new_rows, image.rows());
  ASSERT_EQ(new_cols, image.cols());
  for (int r = 0; r < image.rows(); ++r) {
    for (int c = 0; c < image.cols(); ++c) {
      if (r == c) {
        ASSERT_EQ(0, image.at(r, c).red) << r << " " << c;
        ASSERT_EQ(0, image.at(r, c).green) << r << " " << c;
        ASSERT_EQ(0, image.at(r, c).blue) << r << " " << c;
      } else if (abs(r - c) > scale) {
        ASSERT_EQ(255, image.at(r, c).red) << r << " " << c;
        ASSERT_EQ(255, image.at(r, c).green) << r << " " << c;
        ASSERT_EQ(255, image.at(r, c).blue) << r << " " << c;
      }
    }
  }
}
