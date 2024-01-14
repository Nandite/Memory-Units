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

using namespace mu::literals;

TEST(LiteralOperatorsBase2, LiteralConstruction) {
    auto kb = 1_kiB;
    auto mb = 1_MiB;
    auto gb = 1_GiB;
    auto tb = 1_TiB;
    auto pb = 1_PiB;
    auto eb = 1_EiB;

    EXPECT_EQ(kb.count(), 1);
    EXPECT_EQ(mb.count(), 1);
    EXPECT_EQ(gb.count(), 1);
    EXPECT_EQ(tb.count(), 1);
    EXPECT_EQ(pb.count(), 1);
    EXPECT_EQ(eb.count(), 1);

    auto kb_large = 1024_kiB;
    auto mb_large = 1024_MiB;
    auto gb_large = 1024_GiB;
    auto tb_large = 1024_TiB;
    auto pb_large = 1024_PiB;
    auto eb_large = 1024_EiB;

    EXPECT_EQ(kb_large.count(), 1024);
    EXPECT_EQ(mb_large.count(), 1024);
    EXPECT_EQ(gb_large.count(), 1024);
    EXPECT_EQ(tb_large.count(), 1024);
    EXPECT_EQ(pb_large.count(), 1024);
    EXPECT_EQ(eb_large.count(), 1024);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
