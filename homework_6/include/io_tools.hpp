// @file       io_tools.hpp
// @author     Igor Bogoslavskyi [igor.bogoslavskyi@gmail.com]
// @maintainer Ignacio Vizzo     [ivizzo@uni-bonn.de]
//
// Copyright (c) 2019 Igor Bogoslavskyi , all rights reserved
#ifndef IGG_IMAGE_IO_TOOLS_HPP_
#define IGG_IMAGE_IO_TOOLS_HPP_

#include <cstddef>
#include <string>
#include <vector>

namespace igg::io_tools {

/// Dummy structure to store relevant image data.
struct ImageData {
  int rows;
  int cols;
  int max_val;
  std::vector<int> data;
};

/// Reads from a pgm image from ascii file. Returns empty ImageData if the path
/// is not found or any errors have occurred while reading.
ImageData ReadFromPgm(const std::string& file_name);

/// Write image data into an ascii pgm file. Return true if successful.
bool WriteToPgm(const ImageData& image_data, const std::string& file_name);

}  // namespace igg::io_tools

#endif  // IGG_IMAGE_IO_TOOLS_HPP_
