#include "convert_dataset.hpp"
#include <opencv2/core/types.hpp>

namespace ipb::serialization::sifts {
std::tuple<cv::Mat, std::vector<cv::KeyPoint> > ComputeSifts(const std::string& fileName) {
  const cv::Mat kInput = cv::imread(fileName);

  // detect key points
  cv::Ptr<cv::Feature2D>  detector= cv::SIFT::create();
  std::vector<cv::KeyPoint> keypoints;
  detector->detect(kInput, keypoints);

  // extract the SIFT descriptors
  cv::Mat descriptors;
  cv::Ptr<cv::DescriptorExtractor> extractor = cv::SIFT::create();
  extractor->compute(kInput, keypoints, descriptors);

  return std::make_tuple(descriptors, keypoints);
}
void ConvertDataset(const std::experimental::filesystem::path &img_path) {
  std::experimental::filesystem::path bin_dir="bin";
  std::experimental::filesystem::create_directory(img_path.parent_path()/bin_dir);
  for (auto const &dir_entry : std::experimental::filesystem::directory_iterator{img_path}) {
        if(dir_entry.path().extension()==".png"){
            auto sifts= ComputeSifts(dir_entry.path());
            cv::Mat descriptors= std::get<0>(sifts);
            std::experimental::filesystem::path fileToCopy = dir_entry;
            fileToCopy.replace_extension(".bin"); 
            auto output_file= img_path.parent_path()/bin_dir/ fileToCopy.filename();
            Serialize(descriptors,output_file);
        }
  }
}

std::vector<cv::Mat> LoadDataset(const std::experimental::filesystem::path& bin_path){
    std::vector<cv::Mat> descriptors;
    for (auto const &dir_entry : std::experimental::filesystem::directory_iterator{bin_path}) {
        if(dir_entry.path().extension()==".bin"){
            cv::Mat descriptor= Deserialize(dir_entry.path());
            descriptors.push_back(descriptor);
        }
    }
    return descriptors;
}

} // namespace ipb::serialization::sifts
