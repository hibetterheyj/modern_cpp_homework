// @file      test_ipb_algorithm.cpp
// @author    Ignacio Vizzo     [ivizzo@uni-bonn.de]
//
// Copyright (c) 2020 Ignacio Vizzo, all rights reserved
#include <string>
#include <tuple>
#include <vector>

#include <boost/core/demangle.hpp>
#include <catch2/catch.hpp>

#include "homework_4.h"

TEMPLATE_TEST_CASE("ipb::named_vector can be initalized as an std::vector",
                   "[named_vector]", char, int, std::string, float, double,
                   (std::tuple<int, float>)) {
  const int kNumElements = 5;
  const std::string type_name = boost::core::demangle(typeid(TestType).name());
  const std::string empty_str;
  const std::vector<TestType> std_empty_vector{};
  const std::vector<TestType> std_vector(kNumElements);

  SECTION("Initialize empty") {
    ipb::named_vector<TestType> templated_vector;
    REQUIRE(templated_vector.empty());
    REQUIRE(templated_vector.name().empty());
    REQUIRE(templated_vector.vector().empty());
    REQUIRE(templated_vector.name() == empty_str);
    REQUIRE(templated_vector.vector() == std_empty_vector);
  }

  SECTION("Initialize with name only") {
    ipb::named_vector<TestType> templated_vector{type_name, {}};
    REQUIRE(templated_vector.empty());  // still considered to be empty
    REQUIRE(!templated_vector.name().empty());
    REQUIRE(templated_vector.vector().empty());
    REQUIRE(templated_vector.name() == type_name);
    REQUIRE(templated_vector.vector() == std_empty_vector);
  }

  SECTION("Full initialization") {
    ipb::named_vector<TestType> templated_vector{type_name, std_vector};
    REQUIRE(!templated_vector.empty());
    REQUIRE(!templated_vector.name().empty());
    REQUIRE(!templated_vector.vector().empty());
    REQUIRE(templated_vector.name() == type_name);
    REQUIRE(templated_vector.vector() == std_vector);
  }
}

TEMPLATE_TEST_CASE("ipb::named_vectors can be sized and resized",
                   "[named_vector]", char, int, std::string, float, double,
                   (std::tuple<int, float>)) {
  const int kNumElements = 5;
  const std::string name = "resizable_vector";
  const std::vector<TestType> std_vector(kNumElements);
  ipb::named_vector<TestType> v{name, std_vector};

  REQUIRE(v.size() == kNumElements + name.size());
  REQUIRE(v.capacity() >= kNumElements);

  SECTION("resizing bigger changes size and capacity") {
    v.resize(2 * kNumElements);
    REQUIRE(v.size() == 2 * kNumElements + name.size());
    REQUIRE(v.capacity() >= 2 * kNumElements);
  }
  SECTION("resizing smaller changes size but not capacity") {
    v.resize(0);
    REQUIRE(v.empty());
    REQUIRE(v.capacity() >= kNumElements);
  }
  SECTION("reserving bigger changes capacity but not size") {
    v.reserve(2 * kNumElements);
    REQUIRE(v.size() == kNumElements + name.size());
    REQUIRE(v.capacity() >= 2 * kNumElements);
  }
  SECTION("reserving smaller does not change size or capacity") {
    v.reserve(0);
    REQUIRE(v.size() == kNumElements + name.size());
    REQUIRE(v.capacity() >= kNumElements);
  }
}

SCENARIO("ipb::named_vector size is consistent", "[named_vector]") {
  GIVEN("No arguments") {
    ipb::named_vector<int> v;
    REQUIRE(v.size() == 0);
    REQUIRE(v.empty());
    WHEN("Members are initialized") {
      v = {"name", {1, 2, 3, 4}};
      THEN("The size increases") {
        REQUIRE(v.size() > 0);
        REQUIRE(!v.empty());
      }
    }
    WHEN("named_vector is constructed") {
      v = {"new_name", {1, 2, 3, 4}};
      THEN("The size increases") {
        REQUIRE(v.size() > 0);
        REQUIRE(!v.empty());
      }
    }
  }
  GIVEN("A completely initialized vector") {
    const std::string name{"Nacho"};
    const std::vector<int> std_vector{1, 2, 3, 4};
    ipb::named_vector<int> v{name, std_vector};
    REQUIRE(!v.empty());
    REQUIRE(v.size() == name.size() + std_vector.size());
  }

  GIVEN("A partially initialized vector") {
    const std::string name{"Nacho"};
    const std::vector<int> std_vector{1, 2, 3, 4};
    WHEN("No name is provided") {
      ipb::named_vector<int> v;
      v = {"", std_vector};
      THEN("The named_vector is considered incomplete, therefore, empty") {
        REQUIRE(v.empty());
      }
      THEN("The size() matches the std::vector::size()") {
        REQUIRE(v.size() == std_vector.size());
      }
    }
    WHEN("No vector is provided") {
      ipb::named_vector<int> v;
      v = {name, {}};
      THEN("The named_vector is considered incomplete, therefore, empty") {
        REQUIRE(v.empty());
      }
      THEN("The size() matches the std::string::size()") {
        REQUIRE(v.size() == name.size());
      }
    }
  }
}