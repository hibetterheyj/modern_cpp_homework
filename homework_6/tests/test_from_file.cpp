// Copyright Igor Bogoslavskyi, year 2018.
// In case of any problems with the code please contact me.
// Email: igor.bogoslavskyi@uni-bonn.de.

#include <gtest/gtest.h>

#include "homework_6.h"

using igg::Image;

TEST(TestImageIO, InitFromFileSize) {
  Image image;
  ASSERT_EQ(0, image.rows());
  ASSERT_EQ(0, image.cols());
  ASSERT_TRUE(image.FillFromPgm("../../tests/data/dummy_file.pgm"));
  ASSERT_EQ(10, image.rows());
  ASSERT_EQ(10, image.cols());
}

TEST(TestImageIO, InitFromFileContents) {
  Image image;
  ASSERT_EQ(0, image.rows());
  ASSERT_EQ(0, image.cols());
  ASSERT_TRUE(image.FillFromPgm("../../tests/data/dummy_file.pgm"));
  ASSERT_EQ(10, image.rows());
  ASSERT_EQ(10, image.cols());
  for (int r = 0; r < image.rows(); ++r) {
    for (int c = 0; c < image.cols(); ++c) {
      if (r == c) {
        ASSERT_EQ(0, image.at(r, c)) << r << " " << c;
      } else {
        ASSERT_EQ(255, image.at(r, c)) << r << " " << c;
      }
    }
  }
}
