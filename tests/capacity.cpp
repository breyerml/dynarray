/**
 * Copyright (C) 2021 - Marcel Breyer - All Rights Reserved
 * Licensed under the MIT License. See LICENSE.md file in the project root for full license information.
 *
 * Implements tests for the capacity member functions of the cpp_util::dynarray class.
 */

#include "dynarray.hpp"

#include "catch/catch.hpp"

#include <limits>  // std::numeric_limits::max

TEST_CASE("dynarray capacity member functions", "[capacity]") {
    const cpp_util::dynarray<int> default_arr{};
    const cpp_util::dynarray<int> arr = { 0, 1, 2, 3, 4, 5 };

    SECTION("empty() member function") {
        CHECK(default_arr.empty());
        CHECK_FALSE(arr.empty());
    }

    SECTION("size() member function") {
        CHECK(default_arr.size() == 0);
        CHECK(arr.size() == 6);
    }

    SECTION("max_size() member function") {
        CHECK(cpp_util::dynarray<int>::max_size() == (std::numeric_limits<std::ptrdiff_t>::max() / sizeof(int)));
    }
}
