// @file      convert_dataset.hpp
// @author    Ignacio Vizzo     [ivizzo@uni-bonn.de]
// @author Bruno Santos
// Copyright (c) 2020 Ignacio Vizzo, all rights reserved
#ifndef CONVERT_DATASET_HPP_
#define CONVERT_DATASET_HPP_

#include "opencv2/core/types.hpp"
#include <experimental/filesystem>
#include <string>
#include <vector>
#include <iostream>
#include <serialize.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
using cv::SIFT;
namespace ipb::serialization::sifts {
/**
 * @brief This helper function reads all the png files from a given path,
 * compute the SIFT descriptors for each of them, and saves the results to a
 * binary file. You can see this function as a "dataset" converter, it basically
 * converts a set of png image files to a SIFT representation of the image and
 * save the descriptors to the filesystem. You MUST write the descriptors use
 * the same filename of each image, but instead of using a '.png' extension you
 * must use a '.bin' extension
 *
 * It MUST store the binary files on the same parent directory where the images
 * are located but inside a `bin/` subfolder. Basically, after calling this
 * function with "data/freiburg/images/" as input path the results should be
 * stored in "data/freiburg/bin/""
 *
 * @param img_path The path where the png image files are located.
 */
void ConvertDataset(const std::experimental::filesystem::path& img_path);

/**
 * @brief This helper function will allow you to read from a binary-like dataset
 * of SIFT descriptors and load the data into a container. This utility might be
 * used after creating this so called 'binary dataset' that basically holds all
 * the feature descriptors from a given dataset of images.
 *
 * @param bin_path Where the '.bin' files are located
 * @return std::vector<cv::Mat> Containing all the SIFT features from the input
 * binary dataset.
 */
std::vector<cv::Mat> LoadDataset(const std::experimental::filesystem::path& bin_path);



std::tuple<cv::Mat, std::vector<cv::KeyPoint>> ComputeSifts(const std::string& fileName);

}  // namespace ipb::serialization::sifts

#endif  // CONVERT_DATASET_HPP