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

TEST(MemoryCastTestBase2, Downcast) {
    const mu::kibibytes kb(1); // 1 kibibyte
    const mu::mebibytes mb(1); // 1 mebibyte
    const mu::gibibytes gb(1); // 1 gibibyte
    const mu::tebibytes tb(1); // 1 tebibyte
    const mu::pebibytes pb(1); // 1 pebibyte

    const auto kb_to_b = mu::memory_size_cast<mu::bytes>(kb); // Cast 1 kibibyte to bytes
    EXPECT_EQ(kb_to_b.count(), 1024);

    const auto mb_to_kb = mu::memory_size_cast<mu::kibibytes>(mb); // Cast 1 mebibyte to kibibyte
    EXPECT_EQ(mb_to_kb.count(), 1024);

    const auto gb_to_mb = mu::memory_size_cast<mu::mebibytes>(gb); // Cast 1 gibibyte to mebibyte
    EXPECT_EQ(gb_to_mb.count(), 1024);

    const auto tb_to_gb = mu::memory_size_cast<mu::gibibytes>(tb); // Cast 1 tebibyte to gibibyte
    EXPECT_EQ(tb_to_gb.count(), 1024);

    const auto pb_to_tb = mu::memory_size_cast<mu::tebibytes>(pb); // Cast 1 pebibyte to tebibyte
    EXPECT_EQ(pb_to_tb.count(), 1024);


}

TEST(MemoryCastTestBase2, Upcast) {
    const mu::bytes b(1024); // 1024 kibibyte
    const mu::kibibytes kb(1024); // 1024 kibibyte
    const mu::mebibytes mb(1024); // 1024 mebibyte
    const mu::gibibytes gb(1024); // 1024 gibibyte
    const mu::tebibytes tb(1024); // 1024 tebibyte
    const mu::pebibytes pb(1024); // 1024 pebibyte

    const auto b_to_kb = mu::memory_size_cast<mu::kibibytes>(b); // Cast 1000 bytes to kilbytes
    EXPECT_EQ(b_to_kb.count(), 1);

    const auto kb_to_mb = mu::memory_size_cast<mu::mebibytes>(kb); // Cast 1000 kilbytes to mebibytes
    EXPECT_EQ(kb_to_mb.count(), 1);

    const auto mb_to_gb = mu::memory_size_cast<mu::gibibytes>(mb); // Cast 1000 mebibytes to gibibytes
    EXPECT_EQ(mb_to_gb.count(), 1);

    const auto gb_to_tb = mu::memory_size_cast<mu::tebibytes>(gb); // Cast 1000 gibibyte to tebibytes
    EXPECT_EQ(gb_to_tb.count(), 1);

    const auto tb_to_pb = mu::memory_size_cast<mu::pebibytes>(tb); // Cast 1000 tebibytes to pebibyte
    EXPECT_EQ(tb_to_pb.count(), 1);

    const auto pb_to_eb = mu::memory_size_cast<mu::exabytes>(pb); // Cast 1000 pebibyte to exabytes
    EXPECT_EQ(pb_to_eb.count(), 1);
}