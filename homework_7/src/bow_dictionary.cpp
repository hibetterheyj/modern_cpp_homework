#include "bow_dictionary.h"

namespace ipb {
void BowDictionary::set_descriptors(const std::vector<cv::Mat> &input) {
  std::vector<cv::Mat> output;
  output.reserve(input.size());
  for (const auto &in : input) {
    output.emplace_back(in);
  }
  descriptors_ = output;
}
void BowDictionary::set_params(int n_iter, int size,
                               const std::vector<cv::Mat> &descriptors) {
  set_descriptors(descriptors);
  set_size(size);
  set_max_iterations(n_iter);
  this->codebook_= kMeans(descriptors, size, n_iter); 
}

} // namespace ipb