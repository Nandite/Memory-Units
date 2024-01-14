// Copyright (c) 2020 Papa Libasse Sow.
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

using namespace mu::literals;


TEST(MemorySizeRelationalTest, Equality) {
    const mu::bytes b(1000); // 1000 bytes
    const mu::kilobytes kb(1); // 1 kilobyte (equivalent to 1000 bytes)
    const mu::megabytes mb(1); // 1 megabyte
    const mu::gigabytes gb(1); // 1 gigabyte
    const mu::terabytes tb(1); // 1 terabyte
    const mu::petabytes pb(1); // 1 petabyte
    const mu::exabytes eb(1); // 1 exabyte

    EXPECT_TRUE(b == kb); // 1000 bytes should be equal to 1 kilobyte
    EXPECT_FALSE(mb == gb); // 1 megabyte is not equal to 1 gigabyte
    EXPECT_FALSE(tb == pb); // 1 terabyte is not equal to 1 petabyte
    EXPECT_FALSE(eb == mb); // 1 exabyte is not equal to 1 megabyte

    const mu::bytes another_b(1000); // Another 1000 bytes
    EXPECT_TRUE(b == another_b); // Both are 1000 bytes

    const mu::megabytes large_mb(1000); // 1000 megabytes
    const mu::gigabytes one_gb(1); // 1 gigabyte
    EXPECT_TRUE(large_mb == one_gb); // 1000 MB should be equal to 1 GB
}

TEST(MemorySizeRelationalTest, LessThan) {
    const mu::bytes b(500); // 500 bytes
    const mu::kilobytes kb(1); // 1 kilobyte
    const mu::megabytes mb(1); // 1 megabyte
    const mu::gigabytes gb(1); // 1 gigabyte
    const mu::terabytes tb(1); // 1 terabyte
    const mu::petabytes pb(1); // 1 petabyte
    const mu::exabytes eb(1); // 1 exabyte

    EXPECT_TRUE(b < kb); // 500 bytes is less than 1 kilobyte
    EXPECT_FALSE(kb < b); // 1 kilobyte is not less than 500 bytes
    EXPECT_TRUE(mb < gb); // 1 megabyte is less than 1 gigabyte
    EXPECT_FALSE(gb < mb); // 1 gigabyte is not less than 1 megabyte
    EXPECT_TRUE(tb < pb); // 1 terabyte is less than 1 petabyte
    EXPECT_FALSE(pb < tb); // 1 petabyte is not less than 1 terabyte
    EXPECT_TRUE(pb < eb); // 1 exabyte is less than 1 petabyte
    EXPECT_FALSE(eb < pb); // 1 petabyte is not less than 1 exabyte

    const mu::bytes small_b(100); // 100 bytes
    EXPECT_TRUE(small_b < b); // 100 bytes is less than 500 bytes
    EXPECT_FALSE(b < small_b); // 500 bytes is not less than 100 bytes

    const mu::gigabytes large_gb(1000); // 1000 gigabytes
    EXPECT_TRUE(gb < large_gb); // 1 gigabyte is less than 1000 gigabytes
    EXPECT_FALSE(large_gb < gb); // 1000 gigabytes is not less than 1 gigabyte
}

TEST(MemorySizeRelationalTest, NotEqual) {
    const mu::bytes b(1000); // 1000 bytes
    const mu::kilobytes kb(1); // 1 kilobyte (equivalent to 1000 bytes)
    const mu::megabytes mb(1); // 1 megabyte
    const mu::gigabytes gb(1); // 1 gigabyte
    const mu::terabytes tb(1); // 1 terabyte
    const mu::petabytes pb(1); // 1 petabyte
    const mu::exabytes eb(1); // 1 exabyte

    EXPECT_FALSE(b != kb); // 1000 bytes should be equal to 1 kilobyte
    EXPECT_TRUE(mb != gb); // 1 megabyte is not equal to 1 gigabyte
    EXPECT_TRUE(tb != pb); // 1 terabyte is not equal to 1 petabyte
    EXPECT_TRUE(eb != mb); // 1 exabyte is not equal to 1 megabyte

    const mu::bytes another_b(1000); // Another 1000 bytes
    EXPECT_FALSE(b != another_b); // Both are 1000 bytes

    const mu::megabytes large_mb(1000); // 1000 megabytes
    const mu::gigabytes one_gb(1); // 1 gigabyte
    EXPECT_FALSE(large_mb != one_gb); // 1000 MB should be equal to 1 GB
}

TEST(MemorySizeRelationalTest, RelationalOperators) {
    const mu::bytes b(500); // 500 bytes
    const mu::kilobytes kb(1); // 1 kilobyte (1000 bytes)
    const mu::megabytes mb(1); // 1 megabyte
    const mu::gigabytes gb(1); // 1 gigabyte
    const mu::terabytes tb(1); // 1 terabyte
    const mu::petabytes pb(1); // 1 petabyte

    EXPECT_TRUE(b <= kb); // 500 bytes is less than or equal to 1 kilobyte
    EXPECT_TRUE(kb <= kb); // 1 kilobyte is equal to itself
    EXPECT_FALSE(gb <= mb); // 1 gigabyte is not less than or equal to 1 megabyte

    EXPECT_TRUE(gb > mb); // 1 gigabyte is greater than 1 megabyte
    EXPECT_FALSE(mb > gb); // 1 megabyte is not greater than 1 gigabyte
    EXPECT_FALSE(kb > kb); // 1 kilobyte is not greater than itself

    EXPECT_TRUE(gb >= mb); // 1 gigabyte is greater than or equal to 1 megabyte
    EXPECT_TRUE(tb >= gb); // 1 terabyte is greater than or equal to 1 gigabyte
    EXPECT_TRUE(pb >= pb); // 1 petabyte is equal to itself
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
