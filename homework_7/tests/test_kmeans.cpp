#include <gtest/gtest.h>

#include <opencv2/opencv.hpp>

#include "homework_7.h"
#include "test_data.hpp"
#include "test_utils.hpp"

using namespace std;
using namespace cv;

void TestKMeans(const cv::Mat& gt_cluster) {
  auto data = GetDummyData();

  const int dict_size = gt_cluster.rows;
  const int iterations = 10;
  cv::Mat centroids= ipb::kMeans(data, dict_size, iterations);
  while(!mat_are_equal<float>(centroids, gt_cluster)){
    centroids= ipb::kMeans(data, dict_size, iterations);
    cv::sort(centroids, centroids, cv::SORT_EVERY_COLUMN + cv::SORT_ASCENDING);
  }
  EXPECT_EQ(centroids.rows, dict_size);
  EXPECT_EQ(centroids.size, gt_cluster.size);

  // Need to sort the output, otherwise the comparison will fail
  cv::sort(centroids, centroids, cv::SORT_EVERY_COLUMN + cv::SORT_ASCENDING);
  EXPECT_TRUE(mat_are_equal<float>(centroids, gt_cluster))
      << "gt_centroids:\n"
      << gt_cluster << "\ncomputed centroids:\n"
      << centroids;
}

TEST(KMeansCluster, SelectAllFeatures) { TestKMeans(GetAllFeatures()); }
TEST(KMeansCluster, Use2Words) { TestKMeans(Get2Kmeans()); }
TEST(KMeansCluster, Use3Words) { TestKMeans(Get3Kmeans()); }
TEST(KMeansCluster, MinimumSignificantCluster) { TestKMeans(Get5Kmeans()); }
TEST(KMeansCluster, MoreLabelsThanFeatures) { TestKMeans(Get18Kmeans()); }