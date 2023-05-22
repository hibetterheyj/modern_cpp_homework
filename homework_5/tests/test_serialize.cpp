// @file      test_serialize.cpp
// @author    Ignacio Vizzo     [ivizzo@uni-bonn.de]
//
// Copyright (c) 2020 Ignacio Vizzo, all rights reserved
#include <experimental/filesystem>
#include <string>

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

#include "homework_5.h"
#include "sifts_internal.hpp"
#include "utils.hpp"
#include <catch2/catch_all.hpp>
namespace fs = std::experimental::filesystem;
SCENARIO("cv::Mat img serialization", "[serialization]") {
  const std::string lenna_path = "../../tests/data/lenna.png";
  const std::string lenna_bin_path = "../../tests/data/lenna.bin";

  GIVEN("The lenna img") {
    auto lenna = cv::imread(lenna_path, cv::IMREAD_GRAYSCALE);
    REQUIRE(!lenna.empty());

    WHEN("lenna is serialized") {
      ipb::serialization::Serialize(lenna, lenna_bin_path);
      THEN("The binary file is created") {
        REQUIRE(fs::exists(lenna_bin_path));
        fs::remove(lenna_bin_path);
      }
    }

    WHEN("lenna is deserialized") {
      ipb::serialization::Serialize(lenna, lenna_bin_path);
      auto lenna_bin = ipb::serialization::Deserialize(lenna_bin_path);
      fs::remove(lenna_bin_path);
      THEN("No information is being lost") {
        REQUIRE(!lenna_bin.empty());
        REQUIRE(lenna.size() == lenna_bin.size());
        REQUIRE(mat_are_equal<uchar>(lenna, lenna_bin));
      }
    }
  }
}

SCENARIO("cv::Mat SIFT serialization", "[serialization]") {
  const std::string lenna_path = "../../tests/data/lenna.png";
  const std::string descriptors_bin_path = "../../tests/data/lenna_sifts.bin";

  GIVEN("SIFTS descriptors are computed on lenna") {
    const auto [descriptors, image_with_kp] = ComputeSifts(lenna_path);
    REQUIRE(!descriptors.empty());
    REQUIRE(!image_with_kp.empty());

    WHEN("SIFTS are serialized") {
      ipb::serialization::Serialize(descriptors, descriptors_bin_path);
      THEN("The binary file is created") {
        REQUIRE(fs::exists(descriptors_bin_path));
        fs::remove(descriptors_bin_path);
      }
    }

    WHEN("SIFTS are deserialized") {
      ipb::serialization::Serialize(descriptors, descriptors_bin_path);
      auto descriptors_bin =
          ipb::serialization::Deserialize(descriptors_bin_path);
      fs::remove(descriptors_bin_path);
      THEN("No information is being lost") {
        REQUIRE(!descriptors_bin.empty());
        REQUIRE(descriptors.size() == descriptors_bin.size());
        REQUIRE(mat_are_equal<uchar>(descriptors, descriptors_bin));
      }
    }
  }
}