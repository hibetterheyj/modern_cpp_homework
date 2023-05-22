// @file      test_convert_dataset.cpp
// @author    Ignacio Vizzo     [ivizzo@uni-bonn.de]
//
// Copyright (c) 2020 Ignacio Vizzo, all rights reserved

#include <experimental/filesystem>
#include <fstream>
#include <string>

#include <opencv2/core/mat.hpp>
#include <catch2/catch_all.hpp>
#include "convert_dataset.hpp"
#include "homework_5.h"

namespace fs = std::experimental::filesystem;
TEST_CASE("Compute SIFTS from dataset and serialize", "[convert_dataset]") {
  const std::string img_path = "../../tests/data/freiburg/images";
  const std::string bin_path = "../../tests/data/freiburg/bin";
  const std::string bin_path_ = "../../tests/data/freiburg/bin/";
  ipb::serialization::sifts::ConvertDataset(img_path);

  for (const auto& entry : fs::directory_iterator(img_path)) {
    const auto& stem = entry.path().stem().string();
    const auto& extension = entry.path().extension();
    if (extension == ".png") {
      const auto& descriptors_filename = bin_path_ + stem + ".bin";
      REQUIRE(fs::exists(descriptors_filename));
    }
  }
}

TEST_CASE("Deserialize SIFTS from binary dataset", "[convert_dataset]") {
  const std::string bin_path = "../../tests/data/freiburg/bin";
  auto descriptors = ipb::serialization::sifts::LoadDataset(bin_path);
  for (const auto& descriptor : descriptors) {
    REQUIRE(!descriptor.empty());
  }
  fs::remove_all(bin_path);
}

TEST_CASE("Check for consistency while r/w datasets", "[convert_dataset]") {
  const std::string dummy_path = "../../tests/data/freiburg/dummy";
  const std::string bin_path = "../../tests/data/freiburg/bin";

  SECTION("Converting a dummy dataset has no effect") {
    ipb::serialization::sifts::ConvertDataset(dummy_path);
    REQUIRE(fs::is_empty(bin_path));
    fs::remove_all(bin_path);
  }

  SECTION("Reading a dummy dataset has no effect") {
    auto descriptors = ipb::serialization::sifts::LoadDataset(dummy_path);
    REQUIRE(descriptors.empty());
  }
}