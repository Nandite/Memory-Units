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

TEST(MemoryCastTestBase10, Downcast) {
    const mu::kilobytes kb(1); // 1 kilobyte
    const mu::megabytes mb(1); // 1 megabyte
    const mu::gigabytes gb(1); // 1 gigabyte
    const mu::terabytes tb(1); // 1 terabyte
    const mu::petabytes pb(1); // 1 petabyte

    const auto kb_to_b = mu::memory_size_cast<mu::bytes>(kb); // Cast 1 kilobyte to bytes
    EXPECT_EQ(kb_to_b.count(), 1000);

    const auto mb_to_kb = mu::memory_size_cast<mu::kilobytes>(mb); // Cast 1 megabyte to kilobyte
    EXPECT_EQ(mb_to_kb.count(), 1000);

    const auto gb_to_mb = mu::memory_size_cast<mu::megabytes>(gb); // Cast 1 gigabyte to megabyte
    EXPECT_EQ(gb_to_mb.count(), 1000);

    const auto tb_to_gb = mu::memory_size_cast<mu::gigabytes>(tb); // Cast 1 terabyte to gigabyte
    EXPECT_EQ(tb_to_gb.count(), 1000);

    const auto pb_to_tb = mu::memory_size_cast<mu::terabytes>(pb); // Cast 1 petabyte to terabyte
    EXPECT_EQ(pb_to_tb.count(), 1000);


}

TEST(MemoryCastTestBase10, Upcast) {
    const mu::bytes b(1000); // 1000 kilobyte
    const mu::kilobytes kb(1000); // 1000 kilobyte
    const mu::megabytes mb(1000); // 1000 megabyte
    const mu::gigabytes gb(1000); // 1000 gigabyte
    const mu::terabytes tb(1000); // 1000 terabyte
    const mu::petabytes pb(1000); // 1000 petabyte

    const auto b_to_kb = mu::memory_size_cast<mu::kilobytes>(b); // Cast 1000 bytes to kilbytes
    EXPECT_EQ(b_to_kb.count(), 1);

    const auto kb_to_mb = mu::memory_size_cast<mu::megabytes>(kb); // Cast 1000 kilbytes to megabytes
    EXPECT_EQ(kb_to_mb.count(), 1);

    const auto mb_to_gb = mu::memory_size_cast<mu::gigabytes>(mb); // Cast 1000 megabytes to gigabytes
    EXPECT_EQ(mb_to_gb.count(), 1);

    const auto gb_to_tb = mu::memory_size_cast<mu::terabytes>(gb); // Cast 1000 gigabyte to terabytes
    EXPECT_EQ(gb_to_tb.count(), 1);

    const auto tb_to_pb = mu::memory_size_cast<mu::petabytes>(tb); // Cast 1000 terabytes to petabyte
    EXPECT_EQ(tb_to_pb.count(), 1);

    const auto pb_to_eb = mu::memory_size_cast<mu::exabytes>(pb); // Cast 1000 petabyte to exabytes
    EXPECT_EQ(pb_to_eb.count(), 1);
}