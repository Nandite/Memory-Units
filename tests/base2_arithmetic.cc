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

TEST(ArithmeticTestBase2, Addition)
{
    const mu::bytes b(500); // 1 KiB in bytes
    const mu::kibibytes kb(1); // 1 KiB
    const mu::mebibytes mb(1); // 1 MiB
    const mu::gibibytes gb(1); // 1 GiB
    const mu::tebibytes tb(1); // 1 TiB
    const mu::pebibytes pb(1); // 1 PiB
    const mu::exbibytes eb(1); // 1 EiB

    EXPECT_EQ((b + mu::bytes(300)).count(), 800);
    EXPECT_EQ((kb + mu::kibibytes(2)).count(), 3);
    EXPECT_EQ((mb + mu::mebibytes(2)).count(), 3);
    EXPECT_EQ((gb + mu::gibibytes(2)).count(), 3);
    EXPECT_EQ((tb + mu::tebibytes(2)).count(), 3);
    EXPECT_EQ((pb + mu::pebibytes(2)).count(), 3);
    EXPECT_EQ((eb + mu::exbibytes(2)).count(), 3);

    EXPECT_EQ((b + kb).count(), 1524);
    EXPECT_EQ((kb + mb).count(), 1025);
    EXPECT_EQ((mb + gb).count(), 1025);
    EXPECT_EQ((gb + tb).count(), 1025);
    EXPECT_EQ((tb + pb).count(), 1025);
    EXPECT_EQ((pb + eb).count(), 1025);

    EXPECT_EQ((mu::bytes(111) + mu::bytes(592)).count(), 703);
    EXPECT_EQ((mu::bytes(220) + mu::bytes(386)).count(), 606);
    EXPECT_EQ((mu::bytes(79) + mu::bytes(701)).count(), 780);
    EXPECT_EQ((mu::bytes(417) + mu::bytes(326)).count(), 743);
    EXPECT_EQ((mu::bytes(957) + mu::bytes(593)).count(), 1550);

    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::pebibytes(27) + mu::mebibytes(54)).count(), 30399297541373952);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::tebibytes(50) + mu::gibibytes(88)).count(), 55070070669312);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::exbibytes(6) + mu::pebibytes(16)).count(), 6935543426150563840u);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::exbibytes(3) + mu::pebibytes(5)).count(), 3464394013354754048u);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::gibibytes(34) + mu::bytes(23)).count(), 36507222039);
}

TEST(ArithmeticTestBase2, Subtraction)
{
    const mu::bytes b(500); // 1 KiB in bytes
    const mu::kibibytes kb(1); // 1 KiB
    const mu::mebibytes mb(1); // 1 MiB
    const mu::gibibytes gb(1); // 1 GiB
    const mu::tebibytes tb(1); // 1 TiB
    const mu::pebibytes pb(1); // 1 PiB
    const mu::exbibytes eb(1); // 1 EiB

    EXPECT_EQ((b - mu::bytes(300)).count(), 200);
    EXPECT_EQ((kb - mu::kibibytes(1)).count(), 0);
    EXPECT_EQ((mb - mu::mebibytes(1)).count(), 0);
    EXPECT_EQ((gb - mu::gibibytes(1)).count(), 0);
    EXPECT_EQ((tb - mu::tebibytes(1)).count(), 0);
    EXPECT_EQ((pb - mu::pebibytes(1)).count(), 0);
    EXPECT_EQ((eb - mu::exbibytes(1)).count(), 0);

    EXPECT_EQ((kb - b).count(), 524);
    EXPECT_EQ((mb - kb).count(), 1023);
    EXPECT_EQ((gb - mb).count(), 1023);
    EXPECT_EQ((tb - gb).count(), 1023);
    EXPECT_EQ((pb - tb).count(), 1023);
    EXPECT_EQ((eb - pb).count(), 1023);

    EXPECT_EQ((mu::bytes(703) - mu::bytes(111)).count(), 592);
    EXPECT_EQ((mu::bytes(606) - mu::bytes(220)).count(), 386);
    EXPECT_EQ((mu::bytes(780) - mu::bytes(79)).count(), 701);
    EXPECT_EQ((mu::bytes(743) - mu::bytes(417)).count(), 326);
    EXPECT_EQ((mu::bytes(1550) - mu::bytes(957)).count(), 593);

    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::pebibytes(27) - mu::mebibytes(54)).count(), 30399297428127744);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::tebibytes(50) - mu::gibibytes(88)).count(), 54881092108288);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::exbibytes(6) - mu::pebibytes(16)).count(), 6899514629131599872u);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::exbibytes(3) - mu::pebibytes(5)).count(), 3453135014286327808u);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::gibibytes(34) - mu::bytes(23)).count(), 36507221993);
}

TEST(ArithmeticTestBase2, Multiplication)
{
    const mu::bytes b(500); // 1 KiB in bytes
    const mu::kibibytes kb(1); // 1 KiB
    const mu::mebibytes mb(1); // 1 MiB
    const mu::gibibytes gb(1); // 1 GiB
    const mu::tebibytes tb(1); // 1 TiB
    const mu::pebibytes pb(1); // 1 PiB
    const mu::exbibytes eb(1); // 1 EiB

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
    EXPECT_EQ((mu::kibibytes(8) * 5).count(), 40);
    EXPECT_EQ((3 * mu::mebibytes(6)).count(), 18);
    EXPECT_EQ((2 * mu::gibibytes(4)).count(), 8);
    EXPECT_EQ((mu::tebibytes(3) * 4).count(), 12);

    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::pebibytes(27) * 100).count(), 3039929748475084800);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::tebibytes(50) * 50).count(), 2748779069440000);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(2 * mu::exbibytes(6)).count(), 13835058055282163712u);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(5 * mu::exbibytes(3)).count(), 17293822569102704640u);
    EXPECT_EQ(mu::memory_size_cast<mu::bytes>(mu::gibibytes(34) * 30).count(), 1095216660480);
}

TEST(ArithmeticTestBase2, Division) {
    const mu::bytes b(2048); // 2 KiB in bytes
    const mu::kibibytes kb(4); // 4 KiB
    const mu::mebibytes mb(4); // 4 MiB
    const mu::gibibytes gb(4); // 4 GiB
    const mu::tebibytes tb(4); // 4 TiB
    const mu::pebibytes pb(4); // 4 PiB
    const mu::exbibytes eb(4); // 4 EiB

    EXPECT_EQ((b / 2).count(), 1024);
    EXPECT_EQ((kb / 2).count(), 2);
    EXPECT_EQ((mb / 2).count(), 2);
    EXPECT_EQ((gb / 2).count(), 2);
    EXPECT_EQ((tb / 2).count(), 2);
    EXPECT_EQ((pb / 2).count(), 2);
    EXPECT_EQ((eb / 2).count(), 2);

    EXPECT_EQ(b / mu::bytes(1024), 2);
    EXPECT_EQ(kb / mu::kibibytes(2), 2);
    EXPECT_EQ(mb / mu::mebibytes(2), 2);
    EXPECT_EQ(gb / mu::gibibytes(2), 2);
    EXPECT_EQ(tb / mu::tebibytes(2), 2);
    EXPECT_EQ(pb / mu::pebibytes(2), 2);
    EXPECT_EQ(eb / mu::exbibytes(2), 2);

    // Division between different units
    EXPECT_EQ(mb / kb, 1024); // 4 MiB / 4 KiB = 1024
    EXPECT_EQ(gb / mb, 1024); // 4 GiB / 4 MiB = 1024
    EXPECT_EQ(tb / gb, 1024); // 4 TiB / 4 GiB = 1024
    EXPECT_EQ(pb / tb, 1024); // 4 PiB / 4 TiB = 1024
    EXPECT_EQ(eb / pb, 1024); // 4 EiB / 4 PiB = 1024
}

TEST(ArithmeticTestBase2, Modulo) {
    const mu::bytes b(1025); // Slightly over 1 KiB in bytes
    const mu::kibibytes kb(4); // 4 KiB
    const mu::mebibytes mb(4); // 4 MiB
    const mu::gibibytes gb(4); // 4 GiB
    const mu::tebibytes tb(4); // 4 TiB
    const mu::pebibytes pb(4); // 4 PiB
    const mu::exbibytes eb(4); // 4 EiB

    EXPECT_EQ((b % 512).count(), 1);
    EXPECT_EQ((kb % 3).count(), 1);
    EXPECT_EQ((mb % 3).count(), 1);
    EXPECT_EQ((gb % 3).count(), 1);
    EXPECT_EQ((tb % 3).count(), 1);
    EXPECT_EQ((pb % 3).count(), 1);
    EXPECT_EQ((eb % 3).count(), 1);

    EXPECT_EQ((b % mu::bytes(512)).count(), 1);
    EXPECT_EQ((kb % mu::kibibytes(1)).count(), 0);
    EXPECT_EQ((mb % mu::mebibytes(1)).count(), 0);
    EXPECT_EQ((gb % mu::gibibytes(1)).count(), 0);
    EXPECT_EQ((tb % mu::tebibytes(1)).count(), 0);
    EXPECT_EQ((pb % mu::pebibytes(1)).count(), 0);
    EXPECT_EQ((eb % mu::exbibytes(1)).count(), 0);

    EXPECT_EQ(mu::memory_size_cast<mu::kibibytes>(mb % kb).count(), 0); // 4 MiB % 4 KiB = 0 (MiB > KiB)
    EXPECT_EQ(mu::memory_size_cast<mu::mebibytes>(gb % mb).count(), 0); // 4 GiB % 4 MiB = 0 (GiB > MiB)
    EXPECT_EQ(mu::memory_size_cast<mu::gibibytes>(tb % gb).count(), 0); // 4 TiB % 4 GiB = 0 (TiB > GiB)
    EXPECT_EQ(mu::memory_size_cast<mu::tebibytes>(pb % tb).count(), 0); // 4 PiB % 4 TiB = 0 (PiB > TiB)
    EXPECT_EQ(mu::memory_size_cast<mu::pebibytes>(eb % pb).count(), 0); // 4 EiB % 4 PiB = 0 (EiB > PiB)
}

TEST(ArithmeticTestBase2, IncrementDecrement) {
    mu::bytes b(10);
    mu::kibibytes kb(10);
    mu::mebibytes mb(10);
    mu::gibibytes gb(10);
    mu::tebibytes tb(10);
    mu::pebibytes pb(10);
    mu::exbibytes eb(10);

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

TEST(ArithmeticTestBase2, CompoundAssignment) {
    mu::bytes b(10);
    mu::kibibytes kb(10);
    mu::mebibytes mb(10);
    mu::gibibytes gb(10);
    mu::tebibytes tb(10);
    mu::pebibytes pb(10);
    mu::exbibytes eb(10);

    // Compound Addition
    b += mu::bytes(5);
    kb += mu::kibibytes(5);
    mb += mu::mebibytes(5);
    gb += mu::gibibytes(5);
    tb += mu::tebibytes(5);
    pb += mu::pebibytes(5);
    eb += mu::exbibytes(5);
    EXPECT_EQ(b.count(), 15);
    EXPECT_EQ(kb.count(), 15);
    EXPECT_EQ(mb.count(), 15);
    EXPECT_EQ(gb.count(), 15);
    EXPECT_EQ(tb.count(), 15);
    EXPECT_EQ(pb.count(), 15);
    EXPECT_EQ(eb.count(), 15);

    // Compound Subtraction
    b -= mu::bytes(3);
    kb -= mu::kibibytes(3);
    mb -= mu::mebibytes(3);
    gb -= mu::gibibytes(3);
    tb -= mu::tebibytes(3);
    pb -= mu::pebibytes(3);
    eb -= mu::exbibytes(3);
    EXPECT_EQ(b.count(), 12);
    EXPECT_EQ(kb.count(), 12);
    EXPECT_EQ(mb.count(), 12);
    EXPECT_EQ(gb.count(), 12);
    EXPECT_EQ(tb.count(), 12);
    EXPECT_EQ(pb.count(), 12);
    EXPECT_EQ(eb.count(), 12);

    // Compound Multiplication
    b *= mu::bytes(2);
    kb *= mu::kibibytes(2);
    mb *= mu::mebibytes(2);
    gb *= mu::gibibytes(2);
    tb *= mu::tebibytes(2);
    pb *= mu::pebibytes(2);
    eb *= mu::exbibytes(2);
    EXPECT_EQ(b.count(), 24);
    EXPECT_EQ(kb.count(), 24);
    EXPECT_EQ(mb.count(), 24);
    EXPECT_EQ(gb.count(), 24);
    EXPECT_EQ(tb.count(), 24);
    EXPECT_EQ(pb.count(), 24);
    EXPECT_EQ(eb.count(), 24);

    // Compound Division
    b /= mu::bytes(2);
    kb /= mu::kibibytes(2);
    mb /= mu::mebibytes(2);
    gb /= mu::gibibytes(2);
    tb /= mu::tebibytes(2);
    pb /= mu::pebibytes(2);
    eb /= mu::exbibytes(2);
    EXPECT_EQ(b.count(), 12);
    EXPECT_EQ(kb.count(), 12);
    EXPECT_EQ(mb.count(), 12);
    EXPECT_EQ(gb.count(), 12);
    EXPECT_EQ(tb.count(), 12);
    EXPECT_EQ(pb.count(), 12);
    EXPECT_EQ(eb.count(), 12);
}

TEST(ArithmeticTestBase2, ModuloAssignment) {
    mu::bytes b(1025); // Slightly over 1 KiB in bytes
    mu::kibibytes kb(1025); // Slightly over 1 MiB in kibibytes
    mu::mebibytes mb(1025); // Slightly over 1 GiB in mebibytes
    mu::gibibytes gb(1025); // Slightly over 1 TiB in gibibytes
    mu::tebibytes tb(1025); // Slightly over 1 PiB in tebibytes
    mu::pebibytes pb(1025); // Slightly over 1 EiB in pebibytes
    mu::exbibytes eb(1025); // Slightly over 1 ZiB in exbibytes

    // Modulo assignment with scalar
    b %= 1024;
    kb %= 1024;
    mb %= 1024;
    gb %= 1024;
    tb %= 1024;
    pb %= 1024;
    eb %= 1024;
    EXPECT_EQ(b.count(), 1);
    EXPECT_EQ(kb.count(), 1);
    EXPECT_EQ(mb.count(), 1);
    EXPECT_EQ(gb.count(), 1);
    EXPECT_EQ(tb.count(), 1);
    EXPECT_EQ(pb.count(), 1);
    EXPECT_EQ(eb.count(), 1);

    // Resetting values for the next test
    b = mu::bytes(1025);
    kb = mu::kibibytes(1025);
    mb = mu::mebibytes(1025);
    gb = mu::gibibytes(1025);
    tb = mu::tebibytes(1025);
    pb = mu::pebibytes(1025);
    eb = mu::exbibytes(1025);

    // Modulo assignment with same unit
    b %= mu::bytes(1024);
    kb %= mu::kibibytes(1024);
    mb %= mu::mebibytes(1024);
    gb %= mu::gibibytes(1024);
    tb %= mu::tebibytes(1024);
    pb %= mu::pebibytes(1024);
    eb %= mu::exbibytes(1024);
    EXPECT_EQ(b.count(), 1);
    EXPECT_EQ(kb.count(), 1);
    EXPECT_EQ(mb.count(), 1);
    EXPECT_EQ(gb.count(), 1);
    EXPECT_EQ(tb.count(), 1);
    EXPECT_EQ(pb.count(), 1);
    EXPECT_EQ(eb.count(), 1);
}
