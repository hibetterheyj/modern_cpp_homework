#ifndef PPMIOSTRATEGY_HPP_
#define PPMIOSTRATEGY_HPP_

#include "io_strategy.h"
#include <iostream>
#include <png++/png.hpp>
#include <string>

namespace igg {
class PpmIoStrategy : public IoStrategy {
public:
  ImageData Read(const std::string &file) const override;
  bool Write(const std::string &file, const ImageData &img) const override;
};
} // namespace igg
#endif