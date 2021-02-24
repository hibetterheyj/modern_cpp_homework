#include "homework_3.h"
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <sstream>
namespace fs = std::filesystem;

void html_writer::OpenDocument() {
  std::cout << "<!DOCTYPE html>" << std::endl;
  std::cout << "<html>" << std::endl;
}

void html_writer::CloseDocument() { std::cout << "</html>" << std::endl; }

void html_writer::AddCSSStyle(const std::string &stylesheet) {
  std::cout << "<head>" << std::endl;
  std::cout << R"(<link rel="stylesheet" type="text/css" href=")" << stylesheet
            << R"(" />)" << std::endl;
  std::cout << "</head>" << std::endl;
  return;
}

void html_writer::AddTitle(const std::string &title) {
  //<title>Image Browser</title>
  std::cout << "<title>" << title << "</title>" << std::endl;
}

void html_writer::OpenBody() { std::cout << "<body>" << std::endl; }

void html_writer::CloseBody() { std::cout << "</body>" << std::endl; }

void html_writer::OpenRow() {
  std::cout << R"(<div class="row">)" << std::endl;
}

void html_writer::CloseRow() { std::cout << "</div>" << std::endl; }

void html_writer::AddImage(const std::string &img_path, float score,
                           bool highlight) {
  // split the img file name
  fs::path fs_img_path{img_path};
  if (!fs::exists(fs_img_path)) {
    std::cerr << "[ERROR] : Image does not exist\n";
    exit(EXIT_FAILURE);
  }
  std::string img_filename = fs_img_path.filename();

  // determine the file format
  if (img_filename.find("jpg") == std::string::npos &&
      img_filename.find("png") == std::string::npos) {
    std::cerr << "[ERROR] : Unsupported image format\n";
  }

  // print HTML line by line
  if (highlight == true) {
    std::cout << R"(<div class="column" style=" border: 5px solid green;">)"
              << std::endl;
  } else {
    std::cout << R"(<div class="column">)" << std::endl;
  }
  std::cout << "<h2>" << img_filename << "</h2>" << std::endl;
  std::cout << R"(<img src=")" << img_path << R"("/>)" << std::endl;
  std::cout << "<p>score = " << std::setprecision(2) << std::fixed << score
            << "</p>" << std::endl;
  std::cout << "</div>" << std::endl;
}