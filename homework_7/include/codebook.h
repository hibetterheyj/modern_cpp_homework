#ifndef CODEBOOK_HPP_
#define CODEBOOK_HPP_
#include <algorithm>
#include <functional>
#include <map>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <random>
#include <set>
#include <string>
#include <vector>
namespace ipb {

float euclideanDistance(const cv::Mat &a, const cv::Mat &b) ;
/**
 * @brief
 * 1. The first centroid to the location of a randomly selected data point
 * 2. Choosing the subsequent centroids from the remaining data points:
 * 1. based on a probability proportional to the squared distance away from a
 * given point's nearest existing centroid
 * @param descriptors The input SIFT descriptors to cluster.
 * @param k The size of the dictionary, ie, number of visual words.
 * @return intialized centroids
 */
std::vector<cv::Mat>
getInitialClusterCenters(const std::vector<cv::Mat> &descriptors, int k);

/**
 * @brief
 * 1.Compute the distance from each point x to each cluster centroid
 * 2.  Assign each point to the centroid it is closest to
 * @param descriptors The input SIFT descriptors to cluster.
 * @param k The size of the dictionary, ie, number of visual words.
 * @param clusters aggregate of points per centroid index
 * @param centroids initialized centroids
 */
void assignToClusters(const std::vector<cv::Mat> &descriptors,
                      const std::vector<cv::Mat> &centroids,
                      std::map<int, std::vector<cv::Mat>> &clusters);

/**
 * @brief
 * 1. Reassign centroids computing the average per cluster index
 * @param clusters aggregate of points per centroid index
 * @param centroids initialized centroids
 */
 std::vector<cv::Mat> recomputeCenters(int k,
                      const std::map<int, std::vector<cv::Mat>> &clusters, const std::vector<cv::Mat> &centroids,const std::vector<cv::Mat> &descriptors);

/**
 * @brief
 * 1. Given cluster centroids i initialized in some way,
 * 2. For iteration t=1..T:
 * 1. Compute the distance from each point x to each cluster centroid ,
 * 2. Assign each point to the centroid it is closest to,
 * 3. Recompute each centroid as the mean of all points assigned to it,
 *
 * @param descriptors The input SIFT descriptors to cluster.
 * @param k The size of the dictionary, ie, number of visual words.
 * @param max_iterations Maximum number of iterations before convergence.
 * @return cv::Mat One unique Matrix representing all the $k$-means(stacked).
 */
cv::Mat kMeans(const std::vector<cv::Mat> &descriptors, int k, int max_iter);


}; // namespace ipb
#endif