#include "bow_dictionary.h"

namespace ipb{
void BowDictionary::build(const int &n_iter, const int &size, const std::vector<cv::Mat> &descriptors){
    this->codebook_=kMeans(descriptors, size, n_iter);
}
}