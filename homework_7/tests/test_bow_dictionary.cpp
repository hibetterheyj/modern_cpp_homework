// @file      test_bow_dictionary.cpp
// @author    Ignacio Vizzo     [ivizzo@uni-bonn.de]
//
// Copyright (c) 2020 Ignacio Vizzo, all rights reserved
#include <gtest/gtest.h>

#include <experimental/filesystem>
#include <filesystem>
#include <vector>

#include <opencv2/core/mat.hpp>

#include "homework_7.h"
#include "test_utils.hpp"

using ipb::serialization::sifts::ConvertDataset;
using ipb::serialization::sifts::LoadDataset;

namespace {
const int max_iter = 10;
const int dict_size = 1000;
auto &dictionary = ipb::BowDictionary::GetInstance();
} // namespace

TEST(BowDictionary, Serialization) {
  namespace fs = std::experimental::filesystem;
  const std::string img_path = "../../tests/data/freiburg";
  const std::string bin_path = "../../tests/data/freiburg/bin/";
  ipb::serialization::sifts::ConvertDataset(img_path);

  for (const auto &entry : fs::directory_iterator(img_path)) {
    const auto &stem = entry.path().stem().string();
    const auto &extension = entry.path().extension();
    if (extension == ".png") {
      const auto &descriptors_filename = bin_path + stem + ".bin";
      ASSERT_TRUE(fs::exists(descriptors_filename));
    }
  }
}

TEST(BowDictionary, SetDictionaryParams) {
  const auto descriptors = LoadDataset("../../tests/data/freiburg/bin/");
  std::vector<cv::Mat> descs;
  auto descriptor = descriptors[0];
  for (int row = 0; row < descriptor.rows; row++) {
    cv::Mat A = descriptor.row(row);
    descs.push_back(A);
  }
  dictionary.set_params(max_iter, dict_size, descs);
  ASSERT_TRUE(!dictionary.empty());
  ASSERT_EQ(dictionary.size(), dict_size);
}

// Cluster and dataset are identical
TEST(BowDictionary, TransparentCluster) {
  const auto descriptors = LoadDataset("../../tests/data/freiburg/bin");

  int total_features = 0;
  auto descriptor = descriptors[0];
  std::vector<cv::Mat> descs;
  for (int row = 0; row < descriptor.rows; row++) {
    cv::Mat A = descriptor.row(row);
    descs.push_back(A);
  }

  for (const auto &descriptor : descs) {
    total_features += descriptor.rows;
  }
  dictionary.set_params(max_iter, dict_size, descs);

  ASSERT_TRUE(!dictionary.empty());
  ASSERT_EQ(dictionary.total_features(), total_features);
}

TEST(BowDictionary, ChangeSizeDictionary) {
  const auto descriptors = LoadDataset("../../tests/data/freiburg/bin");
  auto descriptor = descriptors[0];
  std::vector<cv::Mat> descs;
  for (int row = 0; row < descriptor.rows; row++) {
    cv::Mat A = descriptor.row(row);
    descs.push_back(A);
  }

  dictionary.set_params(max_iter, dict_size, descs);
  const int kNewSize = 100;
  dictionary.set_size(kNewSize);
  ASSERT_TRUE(!dictionary.empty());
  ASSERT_EQ(dictionary.size(), kNewSize);
}

TEST(BowDictionary, ChangeMaxIterations) {

  const auto descriptors = LoadDataset("../../tests/data/freiburg/bin");
  auto descriptor = descriptors[0];
  std::vector<cv::Mat> descs;
  for (int row = 0; row < descriptor.rows; row++) {
    cv::Mat A = descriptor.row(row);
    descs.push_back(A);
  }
  dictionary.set_params(max_iter, dict_size, descs);
  const int kNewIterations = 100;
  dictionary.set_max_iterations(kNewIterations);
  ASSERT_EQ(dictionary.max_iterations(), kNewIterations);
  ASSERT_TRUE(!dictionary.empty());
  ASSERT_EQ(dictionary.size(), dict_size);
}

TEST(BowDictionary, ChangeInputDescriptors) {
  const auto descriptors = LoadDataset("../../tests/data/freiburg/bin");
  auto descriptor = descriptors[0];
  std::vector<cv::Mat> descs;
  for (int row = 0; row < descriptor.rows; row++) {
    cv::Mat A = descriptor.row(row);
    descs.push_back(A);
  }
  dictionary.set_params(max_iter, dict_size, descs);

  // copy the first half of the descs
  descriptor = descriptors[1];
  std::vector<cv::Mat> descs_;
  for (int row = 0; row < descriptor.rows; row++) {
    cv::Mat A = descriptor.row(row);
    descs_.push_back(A);
  }
  std::vector<cv::Mat> new_descriptors(descs_.size() / 2);
  new_descriptors.reserve(descs_.size() / 2);
  for (size_t i = 0; i < descriptors.size() / 2; i++) {
    new_descriptors[i] = descs_[i];
  }

  dictionary.set_descriptors(new_descriptors);
  ASSERT_NE(dictionary.descriptors().size(), descs_.size());
  ASSERT_EQ(dictionary.descriptors().size(), new_descriptors.size());
  ASSERT_TRUE(!dictionary.empty());

  for (size_t i = 0; i < descs_.size() / 2; i++) {
    ASSERT_TRUE(mat_are_equal<uint8_t>(new_descriptors[i],
                                       dictionary.descriptors()[i]));
  }
  
}
