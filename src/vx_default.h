#pragma once
#include "vx_template.h"
#include "vx_types.h"

#define VX_CREATE_DEFAULT(_TYPE, ...) static inline _TYPE VX_TEMPLATE_NAME(_TYPE, default)(void) { return (_TYPE){ __VA_ARGS__ }; }
#define VX_DEFAULT(_TYPE) VX_TEMPLATE_NAME(_TYPE, default)()

VX_CREATE_DEFAULT(u8,  0)
VX_CREATE_DEFAULT(u16, 0)
VX_CREATE_DEFAULT(u32, 0)
VX_CREATE_DEFAULT(u64, 0)
VX_CREATE_DEFAULT(i8,  0)
VX_CREATE_DEFAULT(i16, 0)
VX_CREATE_DEFAULT(i32, 0)
VX_CREATE_DEFAULT(i64, 0)
VX_CREATE_DEFAULT(f32, 0.0f)
VX_CREATE_DEFAULT(f64, 0.0f)
