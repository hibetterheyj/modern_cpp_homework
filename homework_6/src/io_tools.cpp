// @file       io_tools.cpp
// @author     Igor Bogoslavskyi [igor.bogoslavskyi@gmail.com]
// @maintainer Ignacio Vizzo     [ivizzo@uni-bonn.de]
//
// Copyright (c) 2019 Igor Bogoslavskyi , all rights reserved
#include "io_tools.hpp"

#include <bits/stdint-uintn.h>

#include <fstream>
#include <ios>
#include <iostream>
#include <string>

namespace igg::io_tools {

ImageData ReadFromPgm(const std::string& file_name) {
  std::ifstream in(file_name, std::ios_base::in);
  if (!in) {
    return {0, 0, 0, {}};
  }

  // Read integers, if we read chars, we get 1 digit instead of the whole number
  std::string type;
  int rows = 0;
  int cols = 0;
  int max_val = 0;
  std::vector<int> data;
  in >> type >> rows >> cols >> max_val;

  data.resize(rows * cols);
  int byte = 0;
  for (int r = 0; r < rows; ++r) {
    for (int c = 0; c < cols; ++c) {
      in >> byte;
      data[r * cols + c] = byte;
    }
  }
  return {rows, cols, max_val, data};
}

bool WriteToPgm(const ImageData& image_data, const std::string& file_name) {
  std::ofstream out(file_name);
  if (!out) {
    return false;
  }

  out << "P2" << std::endl;
  out<< image_data.rows << " " << image_data.cols << std::endl;
  out<< image_data.max_val << std::endl;
  for (int r = 0; r < image_data.rows; ++r) {
    for (int c = 0; c < image_data.cols; ++c) {
      out << image_data.data[r * image_data.cols + c] << " ";
    }
    out << std::endl;
  }
  return true;
}

}  // namespace igg::io_tools
