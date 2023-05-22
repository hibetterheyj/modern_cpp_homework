// Copyright Igor Bogoslavskyi, year 2018.
// In case of any problems with the code please contact me.
// Email: igor.bogoslavskyi@uni-bonn.de.

#include <gtest/gtest.h>

#include "homework_6.h"

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
      ASSERT_EQ(0, image.at(r, c)) << r << " " << c;
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
      ASSERT_EQ(0, image.at(r, c)) << r << " " << c;
    }
  }
}

TEST(TestImage, SimpleChange) {
  int size = 10;
  Image image(size, size);
  ASSERT_EQ(size, image.rows());
  ASSERT_EQ(size, image.cols());
  image.at(5, 5) = 10;
  for (int r = 0; r < image.rows(); ++r) {
    for (int c = 0; c < image.cols(); ++c) {
      if (r == 5 && c == 5) {
        ASSERT_EQ(10, image.at(r, c)) << r << " " << c;
      } else {
        ASSERT_EQ(0, image.at(r, c)) << r << " " << c;
      }
    }
  }
}
