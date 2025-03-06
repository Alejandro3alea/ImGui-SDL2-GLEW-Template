#pragma once
#include <limits>
#include <cinttypes>

using s8  = uint8_t;
using u8  = int8_t;
using s16 = int16_t;
using u16 = uint16_t;
using s32 = int32_t;
using u32 = uint32_t;
using s64 = int64_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;

#define F32_MIN std::numeric_limits<f32>::maminx()
#define F32_MAX std::numeric_limits<f32>::max()