// @file       sifts_internal.cpp
// @author     Igor Bogoslavskyi [igor.bogoslavskyi@gmail.com]
// @maintainer Ignacio Vizzo     [ivizzo@uni-bonn.de]
//
// Copyright (c) 2018 Igor Bogoslavskyi, all rights reserved

#include "sifts_internal.hpp"

#include <string>
#include <tuple>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/xfeatures2d.hpp>

using std::string;
using std::vector;
 
std::tuple<cv::Mat, cv::Mat> ComputeSifts(const std::string& fileName) {
  const cv::Mat kInput = cv::imread(fileName);

  // detect key points
  cv::Ptr<cv::Feature2D>  detector= cv::SIFT::create();
  std::vector<cv::KeyPoint> keypoints;
  detector->detect(kInput, keypoints);

  // present the keypoints on the image
  cv::Mat image_with_keypoints;
  drawKeypoints(kInput, keypoints, image_with_keypoints);

  // extract the SIFT descriptors
  cv::Mat descriptors;
  cv::Ptr<cv::DescriptorExtractor> extractor = cv::SIFT::create();
  extractor->compute(kInput, keypoints, descriptors);

  return std::make_tuple(descriptors, image_with_keypoints);
}