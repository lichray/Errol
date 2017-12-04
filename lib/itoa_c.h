// Modified from
// https://github.com/miloyip/rapidjson/blob/master/include/rapidjson/internal/itoa.h
//
// Tencent is pleased to support the open source community by making RapidJSON available.
//
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip. All rights reserved.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#ifndef ITOA_C_H
#define ITOA_C_H

#include <stdint.h>

extern const char cDigitsLut[200];

inline char *u32toa(uint32_t value, char *buffer)
{
	if (value < 10000)
	{
		const uint32_t d1 = (value / 100) << 1;
		const uint32_t d2 = (value % 100) << 1;

		if (value >= 1000)
			*buffer++ = cDigitsLut[d1];
		if (value >= 100)
			*buffer++ = cDigitsLut[d1 + 1];
		if (value >= 10)
			*buffer++ = cDigitsLut[d2];
		*buffer++ = cDigitsLut[d2 + 1];
	}
	else if (value < 100000000)
	{
		// value = bbbbcccc
		const uint32_t b = value / 10000;
		const uint32_t c = value % 10000;

		const uint32_t d1 = (b / 100) << 1;
		const uint32_t d2 = (b % 100) << 1;

		const uint32_t d3 = (c / 100) << 1;
		const uint32_t d4 = (c % 100) << 1;

		if (value >= 10000000)
			*buffer++ = cDigitsLut[d1];
		if (value >= 1000000)
			*buffer++ = cDigitsLut[d1 + 1];
		if (value >= 100000)
			*buffer++ = cDigitsLut[d2];
		*buffer++ = cDigitsLut[d2 + 1];

		*buffer++ = cDigitsLut[d3];
		*buffer++ = cDigitsLut[d3 + 1];
		*buffer++ = cDigitsLut[d4];
		*buffer++ = cDigitsLut[d4 + 1];
	}
	else
	{
		// value = aabbbbcccc in decimal

		const uint32_t a = value / 100000000;  // 1 to 42
		value %= 100000000;

		if (a >= 10)
		{
			const unsigned i = a << 1;
			*buffer++ = cDigitsLut[i];
			*buffer++ = cDigitsLut[i + 1];
		}
		else
			*buffer++ = (char)('0' + (char)(a));

		const uint32_t b = value / 10000;  // 0 to 9999
		const uint32_t c = value % 10000;  // 0 to 9999

		const uint32_t d1 = (b / 100) << 1;
		const uint32_t d2 = (b % 100) << 1;

		const uint32_t d3 = (c / 100) << 1;
		const uint32_t d4 = (c % 100) << 1;

		*buffer++ = cDigitsLut[d1];
		*buffer++ = cDigitsLut[d1 + 1];
		*buffer++ = cDigitsLut[d2];
		*buffer++ = cDigitsLut[d2 + 1];
		*buffer++ = cDigitsLut[d3];
		*buffer++ = cDigitsLut[d3 + 1];
		*buffer++ = cDigitsLut[d4];
		*buffer++ = cDigitsLut[d4 + 1];
	}
	return buffer;
}

inline char *u64toa(uint64_t value, char *buffer)
{
	const uint64_t kTen8 = 100000000;
	const uint64_t kTen9 = kTen8 * 10;
	const uint64_t kTen10 = kTen8 * 100;
	const uint64_t kTen11 = kTen8 * 1000;
	const uint64_t kTen12 = kTen8 * 10000;
	const uint64_t kTen13 = kTen8 * 100000;
	const uint64_t kTen14 = kTen8 * 1000000;
	const uint64_t kTen15 = kTen8 * 10000000;
	const uint64_t kTen16 = kTen8 * kTen8;

	if (value < kTen8)
	{
		uint32_t v = (uint32_t)(value);
		if (v < 10000)
		{
			const uint32_t d1 = (v / 100) << 1;
			const uint32_t d2 = (v % 100) << 1;

			if (v >= 1000)
				*buffer++ = cDigitsLut[d1];
			if (v >= 100)
				*buffer++ = cDigitsLut[d1 + 1];
			if (v >= 10)
				*buffer++ = cDigitsLut[d2];
			*buffer++ = cDigitsLut[d2 + 1];
		}
		else
		{
			// value = bbbbcccc
			const uint32_t b = v / 10000;
			const uint32_t c = v % 10000;

			const uint32_t d1 = (b / 100) << 1;
			const uint32_t d2 = (b % 100) << 1;

			const uint32_t d3 = (c / 100) << 1;
			const uint32_t d4 = (c % 100) << 1;

			if (value >= 10000000)
				*buffer++ = cDigitsLut[d1];
			if (value >= 1000000)
				*buffer++ = cDigitsLut[d1 + 1];
			if (value >= 100000)
				*buffer++ = cDigitsLut[d2];
			*buffer++ = cDigitsLut[d2 + 1];

			*buffer++ = cDigitsLut[d3];
			*buffer++ = cDigitsLut[d3 + 1];
			*buffer++ = cDigitsLut[d4];
			*buffer++ = cDigitsLut[d4 + 1];
		}
	}
	else if (value < kTen16)
	{
		const uint32_t v0 = (uint32_t)(value / kTen8);
		const uint32_t v1 = (uint32_t)(value % kTen8);

		const uint32_t b0 = v0 / 10000;
		const uint32_t c0 = v0 % 10000;

		const uint32_t d1 = (b0 / 100) << 1;
		const uint32_t d2 = (b0 % 100) << 1;

		const uint32_t d3 = (c0 / 100) << 1;
		const uint32_t d4 = (c0 % 100) << 1;

		const uint32_t b1 = v1 / 10000;
		const uint32_t c1 = v1 % 10000;

		const uint32_t d5 = (b1 / 100) << 1;
		const uint32_t d6 = (b1 % 100) << 1;

		const uint32_t d7 = (c1 / 100) << 1;
		const uint32_t d8 = (c1 % 100) << 1;

		if (value >= kTen15)
			*buffer++ = cDigitsLut[d1];
		if (value >= kTen14)
			*buffer++ = cDigitsLut[d1 + 1];
		if (value >= kTen13)
			*buffer++ = cDigitsLut[d2];
		if (value >= kTen12)
			*buffer++ = cDigitsLut[d2 + 1];
		if (value >= kTen11)
			*buffer++ = cDigitsLut[d3];
		if (value >= kTen10)
			*buffer++ = cDigitsLut[d3 + 1];
		if (value >= kTen9)
			*buffer++ = cDigitsLut[d4];
		if (value >= kTen8)
			*buffer++ = cDigitsLut[d4 + 1];

		*buffer++ = cDigitsLut[d5];
		*buffer++ = cDigitsLut[d5 + 1];
		*buffer++ = cDigitsLut[d6];
		*buffer++ = cDigitsLut[d6 + 1];
		*buffer++ = cDigitsLut[d7];
		*buffer++ = cDigitsLut[d7 + 1];
		*buffer++ = cDigitsLut[d8];
		*buffer++ = cDigitsLut[d8 + 1];
	}
	else
	{
		const uint32_t a = (uint32_t)(value / kTen16);  // 1 to 1844
		value %= kTen16;

		if (a < 10)
			*buffer++ = (char)('0' + (char)(a));
		else if (a < 100)
		{
			const uint32_t i = a << 1;
			*buffer++ = cDigitsLut[i];
			*buffer++ = cDigitsLut[i + 1];
		}
		else if (a < 1000)
		{
			*buffer++ = (char)('0' + (char)(a / 100));

			const uint32_t i = (a % 100) << 1;
			*buffer++ = cDigitsLut[i];
			*buffer++ = cDigitsLut[i + 1];
		}
		else
		{
			const uint32_t i = (a / 100) << 1;
			const uint32_t j = (a % 100) << 1;
			*buffer++ = cDigitsLut[i];
			*buffer++ = cDigitsLut[i + 1];
			*buffer++ = cDigitsLut[j];
			*buffer++ = cDigitsLut[j + 1];
		}

		const uint32_t v0 = (uint32_t)(value / kTen8);
		const uint32_t v1 = (uint32_t)(value % kTen8);

		const uint32_t b0 = v0 / 10000;
		const uint32_t c0 = v0 % 10000;

		const uint32_t d1 = (b0 / 100) << 1;
		const uint32_t d2 = (b0 % 100) << 1;

		const uint32_t d3 = (c0 / 100) << 1;
		const uint32_t d4 = (c0 % 100) << 1;

		const uint32_t b1 = v1 / 10000;
		const uint32_t c1 = v1 % 10000;

		const uint32_t d5 = (b1 / 100) << 1;
		const uint32_t d6 = (b1 % 100) << 1;

		const uint32_t d7 = (c1 / 100) << 1;
		const uint32_t d8 = (c1 % 100) << 1;

		*buffer++ = cDigitsLut[d1];
		*buffer++ = cDigitsLut[d1 + 1];
		*buffer++ = cDigitsLut[d2];
		*buffer++ = cDigitsLut[d2 + 1];
		*buffer++ = cDigitsLut[d3];
		*buffer++ = cDigitsLut[d3 + 1];
		*buffer++ = cDigitsLut[d4];
		*buffer++ = cDigitsLut[d4 + 1];
		*buffer++ = cDigitsLut[d5];
		*buffer++ = cDigitsLut[d5 + 1];
		*buffer++ = cDigitsLut[d6];
		*buffer++ = cDigitsLut[d6 + 1];
		*buffer++ = cDigitsLut[d7];
		*buffer++ = cDigitsLut[d7 + 1];
		*buffer++ = cDigitsLut[d8];
		*buffer++ = cDigitsLut[d8 + 1];
	}

	return buffer;
}

#endif
