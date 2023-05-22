#include "codebook.h"
#include <opencv2/core/base.hpp>
namespace ipb {
  float euclideanDistance(const cv::Mat &a, const cv::Mat &b) {

    return cv::norm(a,b,cv::NORM_L2);
}
std::vector<cv::Mat> getInitialClusterCenters(const std::vector<cv::Mat> &descriptors, int k) {
 std::vector<cv::Mat> centroids;
    centroids.reserve(k);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, descriptors.size() - 1);

    for (int i = 0; i < k; i++) {
        int index = distribution(gen);
        centroids.push_back(descriptors[index].clone());
    }

    return centroids;
}

void assignToClusters(const std::vector<cv::Mat> &descriptors,
                      const std::vector<cv::Mat> &centroids,
                      std::map<int, std::vector<cv::Mat>> &clusters) {
  for (const auto &descriptor : descriptors) {
    float distance_min = std::numeric_limits<float>::max();
    int centroid_id =-1;
    // 1. Compute the distance from each point x to each cluster
    // centroid
    for (int j = 0; j < centroids.size(); j++) {
      auto centroid = centroids[j];
      float current_distance = euclideanDistance(centroid,descriptor);
      if (current_distance - distance_min< 0.01 ) {
        distance_min = current_distance;
        centroid_id = j;
      }
    }
    // 2. Assign each point to the centroid it is closest to
    clusters[centroid_id].push_back(descriptor);
  }
}

 std::vector<cv::Mat> recomputeCenters(int k,
                      const std::map<int, std::vector<cv::Mat>> &clusters, const std::vector<cv::Mat> &centroids, const std::vector<cv::Mat> &descriptors) {
 
  std::vector<cv::Mat> centroids_= getInitialClusterCenters(descriptors,  k);
    for (const auto& clusterPair : clusters) {
        int clusterId = clusterPair.first;
        const std::vector<cv::Mat>& cluster = clusterPair.second;
        cv::Mat centroid = cv::Mat::zeros(descriptors[0].rows, descriptors[0].cols, descriptors[0].type());
        int clusterSize = cluster.size();

        for (const auto& dataPoint : cluster) {
            centroid += dataPoint;
        }

        centroid /= static_cast<float>(clusterSize);
        centroids_[clusterId] =centroid;
    }


  return centroids_;
}
cv::Mat kMeans(const std::vector<cv::Mat> &descriptors, int k, int max_iter) {
  // 1. Given cluster centroids i initialized randomly
  std::vector<cv::Mat> descriptors_d;
  for (const auto &descriptor : descriptors) {
    cv::Mat desc;
    descriptor.convertTo(desc, CV_32FC1);
    descriptors_d.emplace_back(desc);
  }
 std::vector<cv::Mat> centroids;
 const auto centroids_init = getInitialClusterCenters(descriptors_d, k);
 centroids= centroids_init;
 std::map<int, std::vector<cv::Mat>> prev_clusters;
  // 2. For iteration t=1..T
  for (int i = 0; i < max_iter; i++) {
    // 2.1 assign clusters
    std::map<int, std::vector<cv::Mat>> clusters;
    assignToClusters(descriptors_d, centroids, clusters);
    // 3. Reassign centroids
    centroids= std::move(recomputeCenters(k, clusters, centroids,descriptors_d));
    prev_clusters= clusters;
  }
  // stack k centroids into one multidimensional cv::Mat
  cv::Mat out;
  for (const auto &centroid : centroids) {
    out.push_back(centroid);
  }
  return out;
}

}; // namespace ipb