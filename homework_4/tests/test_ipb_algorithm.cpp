// @file      test_ipb_algorithm.cpp
// @author    Ignacio Vizzo     [ivizzo@uni-bonn.de]
//
// Copyright (c) 2020 Ignacio Vizzo, all rights reserved
#include <cstdint>
#include <vector>

#include <catch2/catch.hpp>

#include "homework_4.h"

using vector = ipb::named_vector<int>;

TEST_CASE("ipb::accumulate", "[ipb_algorithm]") {
  vector v{"name", {1, 2, 3, 4}};
  REQUIRE(ipb::accumulate(v) == 10);
}

TEST_CASE("ipb::count", "[ipb_algorithm]") {
  vector v{"name", {1, 2, 3, 4}};
  REQUIRE(ipb::count(v, 1) == 1);
}

TEST_CASE("ipb::all_even", "[ipb_algorithm]") {
  vector even_v{"even_vector", {2, 4, 8, 14}};
  REQUIRE(ipb::all_even(even_v));
}

TEST_CASE("ipb::clamp", "[ipb_algorithm]") {
  vector v{"name", {1, 2, 3, 4}};
  const int kMin = 2;
  const int kMax = 3;
  ipb::clamp(v, kMin, kMax);
  REQUIRE(v.vector() == std::vector<int>{2, 2, 3, 3});
}

TEST_CASE("ipb::fill", "[ipb_algorithm]") {
  vector v{"name", {1, 2, 3, 4}};
  const int k = -100;
  ipb::fill(v, k);
  REQUIRE(v.vector() == std::vector<int>(v.vector().size(), k));
}

TEST_CASE("ipb::find", "[ipb_algorithm]") {
  vector even_v{"even_vector", {2, 4, 8, 14}};
  REQUIRE(ipb::find(even_v, 4));
}

TEST_CASE("ipb::print", "[ipb_algorithm]") {
  vector v{"name", {1, 2, 3, 4}};
  ipb::print(v);
}

TEST_CASE("ipb::toupper", "[ipb_algorithm]") {
  vector v{"name", {1, 2, 3, 4}};
  ipb::toupper(v);
  REQUIRE(v.name() == "NAME");
}

TEST_CASE("ipb::sort", "[ipb_algorithm]") {
  vector v_unsorted{"unsorted_vector", {12, 4, 0, 1}};
  ipb::sort(v_unsorted);
  REQUIRE(v_unsorted.vector() == std::vector<int>{0, 1, 4, 12});
}

TEST_CASE("ipb::rotate", "[ipb_algorithm]") {
  vector v{"name", {1, 2, 3, 4}};
  ipb::rotate(v, 2);
  REQUIRE(v.vector() == std::vector<int>{3, 4, 1, 2});
}

TEST_CASE("ipb::reverse", "[ipb_algorithm]") {
  vector v_unsorted{"unsorted_vector", {12, 4, 0, 1}};
  ipb::reverse(v_unsorted);
  REQUIRE(v_unsorted.vector() == std::vector<int>{1, 0, 4, 12});
}