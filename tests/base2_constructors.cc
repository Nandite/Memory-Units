// Copyright (c) 2024 Papa Libasse Sow.
// https://github.com/Nandite/Memory-Units
// Distributed under the MIT Software License (X11 license).
//
// SPDX-License-Identifier: MIT
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of
// the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <gtest/gtest.h>
#include "memory_units.hpp"

// Define the SIZE_INTEGRAL_UNIT_TYPE if it's not already defined in memory_size.h
using INTEGRAL_UNIT_TYPE = std::int64_t; // Example type

TEST(MemorySizeTest, BytesConstructor) {
    const mu::bytes b1(1000);
    EXPECT_EQ(b1.count(), 1000);

    const mu::bytes b2(0);
    EXPECT_EQ(b2.count(), 0);

    const mu::bytes b3(std::numeric_limits<INTEGRAL_UNIT_TYPE>::max());
    EXPECT_EQ(b3.count(), std::numeric_limits<INTEGRAL_UNIT_TYPE>::max());
}

TEST(MemorySizeTest, KibibytesConstructor) {
    const mu::kibibytes kb1(2);
    EXPECT_EQ(kb1.count(), 2);

    const mu::kibibytes kb2(0);
    EXPECT_EQ(kb2.count(), 0);

    const mu::kibibytes kb3(1000);
    EXPECT_EQ(kb3.count(), 1000);
}

TEST(MemorySizeTest, MebibytesConstructor) {
    const mu::mebibytes mb1(3);
    EXPECT_EQ(mb1.count(), 3);

    const mu::mebibytes mb2(0);
    EXPECT_EQ(mb2.count(), 0);

    const mu::mebibytes mb3(500);
    EXPECT_EQ(mb3.count(), 500);
}

TEST(MemorySizeTest, GibibytesConstructor) {
    const mu::gibibytes gb1(4);
    EXPECT_EQ(gb1.count(), 4);

    const mu::gibibytes gb2(0);
    EXPECT_EQ(gb2.count(), 0);

    const mu::gibibytes gb3(250);
    EXPECT_EQ(gb3.count(), 250);
}

TEST(MemorySizeTest, TebibytesConstructor) {
    const mu::tebibytes tb1(5);
    EXPECT_EQ(tb1.count(), 5);

    const mu::tebibytes tb2(0);
    EXPECT_EQ(tb2.count(), 0);

    const mu::tebibytes tb3(100);
    EXPECT_EQ(tb3.count(), 100);
}

TEST(MemorySizeTest, PebibytesConstructor) {
    const mu::pebibytes pb1(6);
    EXPECT_EQ(pb1.count(), 6);

    const mu::pebibytes pb2(0);
    EXPECT_EQ(pb2.count(), 0);

    const mu::pebibytes pb3(50);
    EXPECT_EQ(pb3.count(), 50);
}

TEST(MemorySizeTest, ExbibytesConstructor) {
    const mu::exbibytes eb1(7);
    EXPECT_EQ(eb1.count(), 7);

    const mu::exbibytes eb2(0);
    EXPECT_EQ(eb2.count(), 0);

    const mu::exbibytes eb3(25);
    EXPECT_EQ(eb3.count(), 25);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
