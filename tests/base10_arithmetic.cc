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

TEST(ArithmeticTestBase10, Addition)
{
    const mu::bytes b(500); // 500 bytes
    const mu::kilobytes kb(1); // 1 KB
    const mu::megabytes mb(1); // 1 MB
    const mu::gigabytes gb(1); // 1 GB
    const mu::terabytes tb(1); // 1 TB
    const mu::petabytes pb(1); // 1 PB
    const mu::exabytes eb(1); // 1 EB

    EXPECT_EQ((b + mu::bytes(300)).count(), 800);
    EXPECT_EQ((kb + mu::kilobytes(2)).count(), 3);
    EXPECT_EQ((mb + mu::megabytes(2)).count(), 3);
    EXPECT_EQ((gb + mu::gigabytes(2)).count(), 3);
    EXPECT_EQ((tb + mu::terabytes(2)).count(), 3);
    EXPECT_EQ((pb + mu::petabytes(2)).count(), 3);
    EXPECT_EQ((eb + mu::exabytes(2)).count(), 3);

    EXPECT_EQ((b + kb).count(), 1500);
    EXPECT_EQ((kb + mb).count(), 1001);
    EXPECT_EQ((mb + gb).count(), 1001);
    EXPECT_EQ((gb + tb).count(), 1001);
    EXPECT_EQ((tb + pb).count(), 1001);
    EXPECT_EQ((pb + eb).count(), 1001);

    EXPECT_EQ((mu::bytes(111) + mu::bytes(592)).count(), 703);
    EXPECT_EQ((mu::bytes(220) + mu::bytes(386)).count(), 606);
    EXPECT_EQ((mu::bytes(79) + mu::bytes(701)).count(), 780);
    EXPECT_EQ((mu::bytes(417) + mu::bytes(326)).count(), 743);
    EXPECT_EQ((mu::bytes(957) + mu::bytes(593)).count(), 1550);

    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::petabytes(27) + mu::megabytes(54)).count(), 27000000054000000u);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::terabytes(50) + mu::gigabytes(88)).count(), 50088000000000);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::exabytes(6) + mu::petabytes(16)).count(), 6016000000000000000u);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::exabytes(3) + mu::petabytes(5)).count(), 3005000000000000000u);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::gigabytes(34) + mu::bytes(23)).count(), 34000000023);
}

TEST(ArithmeticTestBase10, Subtraction)
{
    const mu::bytes b(500); // 500 bytes
    const mu::kilobytes kb(1); // 1 KB
    const mu::megabytes mb(1); // 1 MB
    const mu::gigabytes gb(1); // 1 GB
    const mu::terabytes tb(1); // 1 TB
    const mu::petabytes pb(1); // 1 PB
    const mu::exabytes eb(1); // 1 EB

    EXPECT_EQ((b - mu::bytes(300)).count(), 200);
    EXPECT_EQ((kb - mu::kilobytes(1)).count(), 0);
    EXPECT_EQ((mb - mu::megabytes(1)).count(), 0);
    EXPECT_EQ((gb - mu::gigabytes(1)).count(), 0);
    EXPECT_EQ((tb - mu::terabytes(1)).count(), 0);
    EXPECT_EQ((pb - mu::petabytes(1)).count(), 0);
    EXPECT_EQ((eb - mu::exabytes(1)).count(), 0);

    EXPECT_EQ((kb - b).count(), 500);
    EXPECT_EQ((mb - kb).count(), 999);
    EXPECT_EQ((gb - mb).count(), 999);
    EXPECT_EQ((tb - gb).count(), 999);
    EXPECT_EQ((pb - tb).count(), 999);
    EXPECT_EQ((eb - pb).count(), 999);

    EXPECT_EQ((mu::bytes(703) - mu::bytes(111)).count(), 592);
    EXPECT_EQ((mu::bytes(606) - mu::bytes(220)).count(), 386);
    EXPECT_EQ((mu::bytes(780) - mu::bytes(79)).count(), 701);
    EXPECT_EQ((mu::bytes(743) - mu::bytes(417)).count(), 326);
    EXPECT_EQ((mu::bytes(1550) - mu::bytes(957)).count(), 593);

    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::petabytes(27) - mu::megabytes(54)).count(), 26999999946000000);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::terabytes(50) - mu::gigabytes(88)).count(), 49912000000000);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::exabytes(6) - mu::petabytes(16)).count(), 5984000000000000000u);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::exabytes(3) - mu::petabytes(5)).count(), 2995000000000000000u);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::gigabytes(34) - mu::bytes(23)).count(), 33999999977);
}

TEST(ArithmeticTestBase10, Multiplication)
{
    const mu::bytes b(500); // 500 bytes
    const mu::kilobytes kb(1); // 1 KB
    const mu::megabytes mb(1); // 1 MB
    const mu::gigabytes gb(1); // 1 GB
    const mu::terabytes tb(1); // 1 TB
    const mu::petabytes pb(1); // 1 PB
    const mu::exabytes eb(1); // 1 EB

    EXPECT_EQ((b * 2).count(), 1000);
    EXPECT_EQ((kb * 3).count(), 3);
    EXPECT_EQ((mb * 4).count(), 4);
    EXPECT_EQ((5 * gb).count(), 5);
    EXPECT_EQ((tb * 6).count(), 6);
    EXPECT_EQ((7 * pb).count(), 7);
    EXPECT_EQ((8 * eb).count(), 8);

    EXPECT_EQ((b * 10).count(), 5000);
    EXPECT_EQ((kb * 20).count(), 20);
    EXPECT_EQ((mb * 15).count(), 15);
    EXPECT_EQ((12 * gb).count(), 12);
    EXPECT_EQ((11 * tb).count(), 11);
    EXPECT_EQ((pb * 9).count(), 9);
    EXPECT_EQ((14 * eb).count(), 14);

    EXPECT_EQ((mu::bytes(10) * 7).count(), 70);
    EXPECT_EQ((mu::kilobytes(8) * 5).count(), 40);
    EXPECT_EQ((3 * mu::megabytes(6)).count(), 18);
    EXPECT_EQ((2 * mu::gigabytes(4)).count(), 8);
    EXPECT_EQ((mu::terabytes(3) * 4).count(), 12);

    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::petabytes(27) * 100).count(), 2700000000000000000u);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::terabytes(50) * 50).count(), 2500000000000000u);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(2 * mu::exabytes(6)).count(), 12000000000000000000u);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(5 * mu::exabytes(3)).count(), 15000000000000000000u);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::gigabytes(34) * 30).count(), 1020000000000u);
}

TEST(ArithmeticTestBase10, Division) {
    const mu::bytes b(2000); // 2 KB in bytes
    const mu::kilobytes kb(4); // 4 KB
    const mu::megabytes mb(4); // 4 MB
    const mu::gigabytes gb(4); // 4 GB
    const mu::terabytes tb(4); // 4 TB
    const mu::petabytes pb(4); // 4 PB
    const mu::exabytes eb(4); // 4 EB

    EXPECT_EQ((b / 2).count(), 1000);
    EXPECT_EQ((kb / 2).count(), 2);
    EXPECT_EQ((mb / 2).count(), 2);
    EXPECT_EQ((gb / 2).count(), 2);
    EXPECT_EQ((tb / 2).count(), 2);
    EXPECT_EQ((pb / 2).count(), 2);
    EXPECT_EQ((eb / 2).count(), 2);

    EXPECT_EQ(b / mu::bytes(1000), 2);
    EXPECT_EQ(kb / mu::kilobytes(2), 2);
    EXPECT_EQ(mb / mu::megabytes(2), 2);
    EXPECT_EQ(gb / mu::gigabytes(2), 2);
    EXPECT_EQ(tb / mu::terabytes(2), 2);
    EXPECT_EQ(pb / mu::petabytes(2), 2);
    EXPECT_EQ(eb / mu::exabytes(2), 2);

    // Division between different units
    EXPECT_EQ(mb / kb, 1000); // 4 MB / 4 KB = 1024
    EXPECT_EQ(gb / mb, 1000); // 4 GB / 4 MB = 1024
    EXPECT_EQ(tb / gb, 1000); // 4 TB / 4 GB = 1024
    EXPECT_EQ(pb / tb, 1000); // 4 PB / 4 TB = 1024
    EXPECT_EQ(eb / pb, 1000); // 4 EB / 4 PB = 1024
}

TEST(ArithmeticTestBase10, Modulo) {
    const mu::bytes b(1001); // Slightly over 1 KiB in bytes
    const mu::kilobytes kb(4); // 4 KiB
    const mu::megabytes mb(4); // 4 MiB
    const mu::gigabytes gb(4); // 4 GiB
    const mu::terabytes tb(4); // 4 TiB
    const mu::petabytes pb(4); // 4 PiB
    const mu::exabytes eb(4); // 4 EiB

    EXPECT_EQ((b % 499).count(), 3);
    EXPECT_EQ((kb % 3).count(), 1);
    EXPECT_EQ((mb % 3).count(), 1);
    EXPECT_EQ((gb % 3).count(), 1);
    EXPECT_EQ((tb % 3).count(), 1);
    EXPECT_EQ((pb % 3).count(), 1);
    EXPECT_EQ((eb % 3).count(), 1);

    EXPECT_EQ((b % mu::bytes(499)).count(), 3);
    EXPECT_EQ((kb % mu::kilobytes(1)).count(), 0);
    EXPECT_EQ((mb % mu::megabytes(1)).count(), 0);
    EXPECT_EQ((gb % mu::gigabytes(1)).count(), 0);
    EXPECT_EQ((tb % mu::terabytes(1)).count(), 0);
    EXPECT_EQ((pb % mu::petabytes(1)).count(), 0);
    EXPECT_EQ((eb % mu::exabytes(1)).count(), 0);

    EXPECT_EQ(mu::memory_size_cast<mu::kilobytes>(mb % kb).count(), 0); // 4 MB % 4 KB = 0 (MB > KB)
    EXPECT_EQ(mu::memory_size_cast<mu::megabytes>(gb % mb).count(), 0); // 4 GB % 4 MB = 0 (GB > MB)
    EXPECT_EQ(mu::memory_size_cast<mu::gigabytes>(tb % gb).count(), 0); // 4 TB % 4 GB = 0 (TB > GB)
    EXPECT_EQ(mu::memory_size_cast<mu::terabytes>(pb % tb).count(), 0); // 4 PB % 4 TB = 0 (PB > TB)
    EXPECT_EQ(mu::memory_size_cast<mu::petabytes>(eb % pb).count(), 0); // 4 EB % 4 PB = 0 (EB > PB)
}

TEST(ArithmeticTestBase10, IncrementDecrement) {
    mu::bytes b(10);
    mu::kilobytes kb(10);
    mu::megabytes mb(10);
    mu::gigabytes gb(10);
    mu::terabytes tb(10);
    mu::petabytes pb(10);
    mu::exabytes eb(10);

    EXPECT_EQ((++b).count(), 11);
    EXPECT_EQ((++kb).count(), 11);
    EXPECT_EQ((++mb).count(), 11);
    EXPECT_EQ((++gb).count(), 11);
    EXPECT_EQ((++tb).count(), 11);
    EXPECT_EQ((++pb).count(), 11);
    EXPECT_EQ((++eb).count(), 11);

    EXPECT_EQ((b++).count(), 11);
    EXPECT_EQ((kb++).count(), 11);
    EXPECT_EQ((mb++).count(), 11);
    EXPECT_EQ((gb++).count(), 11);
    EXPECT_EQ((tb++).count(), 11);
    EXPECT_EQ((pb++).count(), 11);
    EXPECT_EQ((eb++).count(), 11);

    EXPECT_EQ((--b).count(), 11);
    EXPECT_EQ((--kb).count(), 11);
    EXPECT_EQ((--mb).count(), 11);
    EXPECT_EQ((--gb).count(), 11);
    EXPECT_EQ((--tb).count(), 11);
    EXPECT_EQ((--pb).count(), 11);
    EXPECT_EQ((--eb).count(), 11);

    EXPECT_EQ((b--).count(), 11);
    EXPECT_EQ((kb--).count(), 11);
    EXPECT_EQ((mb--).count(), 11);
    EXPECT_EQ((gb--).count(), 11);
    EXPECT_EQ((tb--).count(), 11);
    EXPECT_EQ((pb--).count(), 11);
    EXPECT_EQ((eb--).count(), 11);
}

TEST(ArithmeticTestBase10, CompoundAssignment) {
    mu::bytes b(10);
    mu::kilobytes kb(10);
    mu::megabytes mb(10);
    mu::gigabytes gb(10);
    mu::terabytes tb(10);
    mu::petabytes pb(10);
    mu::exabytes eb(10);

    b += mu::bytes(5);
    kb += mu::kilobytes(5);
    mb += mu::megabytes(5);
    gb += mu::gigabytes(5);
    tb += mu::terabytes(5);
    pb += mu::petabytes(5);
    eb += mu::exabytes(5);
    EXPECT_EQ(b.count(), 15);
    EXPECT_EQ(kb.count(), 15);
    EXPECT_EQ(mb.count(), 15);
    EXPECT_EQ(gb.count(), 15);
    EXPECT_EQ(tb.count(), 15);
    EXPECT_EQ(pb.count(), 15);
    EXPECT_EQ(eb.count(), 15);

    b -= mu::bytes(3);
    kb -= mu::kilobytes(3);
    mb -= mu::megabytes(3);
    gb -= mu::gigabytes(3);
    tb -= mu::terabytes(3);
    pb -= mu::petabytes(3);
    eb -= mu::exabytes(3);
    EXPECT_EQ(b.count(), 12);
    EXPECT_EQ(kb.count(), 12);
    EXPECT_EQ(mb.count(), 12);
    EXPECT_EQ(gb.count(), 12);
    EXPECT_EQ(tb.count(), 12);
    EXPECT_EQ(pb.count(), 12);
    EXPECT_EQ(eb.count(), 12);

    b *= mu::bytes(2);
    kb *= mu::kilobytes(2);
    mb *= mu::megabytes(2);
    gb *= mu::gigabytes(2);
    tb *= mu::terabytes(2);
    pb *= mu::petabytes(2);
    eb *= mu::exabytes(2);
    EXPECT_EQ(b.count(), 24);
    EXPECT_EQ(kb.count(), 24);
    EXPECT_EQ(mb.count(), 24);
    EXPECT_EQ(gb.count(), 24);
    EXPECT_EQ(tb.count(), 24);
    EXPECT_EQ(pb.count(), 24);
    EXPECT_EQ(eb.count(), 24);

    b /= mu::bytes(2);
    kb /= mu::kilobytes(2);
    mb /= mu::megabytes(2);
    gb /= mu::gigabytes(2);
    tb /= mu::terabytes(2);
    pb /= mu::petabytes(2);
    eb /= mu::exabytes(2);
    EXPECT_EQ(b.count(), 12);
    EXPECT_EQ(kb.count(), 12);
    EXPECT_EQ(mb.count(), 12);
    EXPECT_EQ(gb.count(), 12);
    EXPECT_EQ(tb.count(), 12);
    EXPECT_EQ(pb.count(), 12);
    EXPECT_EQ(eb.count(), 12);
}

TEST(ArithmeticTestBase10, ModuloAssignment) {
    mu::bytes b(1001); // Slightly over 1 kB in bytes
    mu::kilobytes kb(1001); // Slightly over 1 MB in kilobytes
    mu::megabytes mb(1001); // Slightly over 1 GB in megabytes
    mu::gigabytes gb(1001); // Slightly over 1 TB in gigabytes
    mu::terabytes tb(1001); // Slightly over 1 PB in terrabytes
    mu::petabytes pb(1001); // Slightly over 1 EB in petabytes
    mu::exabytes eb(1001); // Slightly over 1 ZB in exabytes

    b %= 1000;
    kb %= 1000;
    mb %= 1000;
    gb %= 1000;
    tb %= 1000;
    pb %= 1000;
    eb %= 1000;
    EXPECT_EQ(b.count(), 1);
    EXPECT_EQ(kb.count(), 1);
    EXPECT_EQ(mb.count(), 1);
    EXPECT_EQ(gb.count(), 1);
    EXPECT_EQ(tb.count(), 1);
    EXPECT_EQ(pb.count(), 1);
    EXPECT_EQ(eb.count(), 1);

    // Resetting values for the next test
    b = mu::bytes(1001);
    kb = mu::kilobytes(1001);
    mb = mu::megabytes(1001);
    gb = mu::gigabytes(1001);
    tb = mu::terabytes(1001);
    pb = mu::petabytes(1001);
    eb = mu::exabytes(1001);

    b %= mu::bytes(1000);
    kb %= mu::kilobytes(1000);
    mb %= mu::megabytes(1000);
    gb %= mu::gigabytes(1000);
    tb %= mu::terabytes(1000);
    pb %= mu::petabytes(1000);
    eb %= mu::exabytes(1000);
    EXPECT_EQ(b.count(), 1);
    EXPECT_EQ(kb.count(), 1);
    EXPECT_EQ(mb.count(), 1);
    EXPECT_EQ(gb.count(), 1);
    EXPECT_EQ(tb.count(), 1);
    EXPECT_EQ(pb.count(), 1);
    EXPECT_EQ(eb.count(), 1);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
