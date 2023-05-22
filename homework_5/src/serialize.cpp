#include "serialize.hpp"

namespace ipb::serialization {

void Serialize(const cv::Mat& m, const std::string& filename){
    std::ofstream f_out(filename,std::ios_base::out| std::ios_base::binary);
    int rows= m.rows;
    int cols= m.cols;
    int type = m.type();
    int channels = m.channels();
    f_out.write(reinterpret_cast<char*>(&rows),sizeof(rows));
    f_out.write(reinterpret_cast<char*>(&cols),sizeof(cols));
    f_out.write(reinterpret_cast<char*>(&type),sizeof(type));
    f_out.write(reinterpret_cast<char*>(&channels),sizeof(channels));
    f_out.write(reinterpret_cast<char*>(m.data),rows*cols*CV_ELEM_SIZE(type));
}

cv::Mat Deserialize(const std::string& filename){
    std::ifstream input(filename,std::ios_base::in|std::ios_base::binary);
    int r=0,c=0;
    int type, channels;
    input.read(reinterpret_cast<char*>(&r),sizeof(int));
    input.read(reinterpret_cast<char*>(&c),sizeof(int));
    input.read(reinterpret_cast<char*>(&type),sizeof(int));
    input.read(reinterpret_cast<char*>(&channels),sizeof(int));
    cv::Mat img = cv::Mat::zeros(r,c,type);
    input.read(reinterpret_cast<char*>(img.data),r*c*CV_ELEM_SIZE(type));
    return img;
}


}