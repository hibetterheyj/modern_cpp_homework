// @file      image_browser.hpp
// @author    Ignacio Vizzo     [ivizzo@uni-bonn.de]
//
// Copyright (c) 2020 Ignacio Vizzo, all rights reserved
#ifndef IMAGE_BROWSER_HPP_
#define IMAGE_BROWSER_HPP_

#include <array>
#include <string>
#include <tuple>
#include <vector>

namespace image_browser {

/// Some Utility Name Types that will make the code more readable
using ScoredImage = std::tuple<std::string, float>;
using ImageRow = std::array<ScoredImage, 3>;

/**
 * @brief This function is in charge to add a full row in the web application, A
 * row consists always of 3 columns, each one contains one image with a given
 * score.
 *
 * @param row          A set with 3 images plus the score of each one.
 * @param first_row    If it's the very first row, the first image should be
 * highlighted.
 */
void AddFullRow(const ImageRow& row, bool first_row = false);

/**
 * @brief Create a Image Browser application, This function should be completely
 * self containded and should take all the necessary actions to create an image
 * web browser application.
 *
 * @param title      The title of the web application.
 * @param stylesheet The CSS style, if any.
 * @param rows       A set of ImageRow, with all the given images to show.
 */
void CreateImageBrowser(const std::string& title, const std::string& stylesheet,
                        const std::vector<ImageRow>& rows);

}  // namespace image_browser

#endif  // IMAGE_BROWSER_HPP_
