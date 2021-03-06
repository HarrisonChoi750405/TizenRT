/****************************************************************************
 *
 * Copyright 2018 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/
//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// Define a hexfloat literal emulator since we can't depend on being able to
//   for hexfloat literals

// 0x10.F5p-10 == hexfloat<double>(0x10, 0xF5, -10)

#ifndef HEXFLOAT_H
#define HEXFLOAT_H

#include <cmath>
#include <climits>

template <class T>
class hexfloat
{
    T value_;

    static int CountLeadingZeros(unsigned long long n) {
        const std::size_t Digits = sizeof(unsigned long long) * CHAR_BIT;
        const unsigned long long TopBit = 1ull << (Digits - 1);
        if (n == 0) return Digits;
        int LeadingZeros = 0;
        while ((n & TopBit) == 0) {
            ++LeadingZeros;
            n <<= 1;
        }
        return LeadingZeros;
    }

public:
    hexfloat(long long m1, unsigned long long m0, int exp)
    {
        const std::size_t Digits = sizeof(unsigned long long) * CHAR_BIT;
        int s = m1 < 0 ? -1 : 1;
        int exp2 = -static_cast<int>(Digits - CountLeadingZeros(m0)/4*4);
        value_ = std::ldexp(m1 + s * std::ldexp(T(m0), exp2), exp);
    }

    operator T() const {return value_;}
};

#endif
