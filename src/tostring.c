#include "tostring.h"
#include <stdio.h>

char _vx_tostring_buffer[_VX_TOSTRING_BUFFER_SIZE];

_VX_TOSTRING_CREATE_BODY_FOR_TYPE(u8,   sprintf (_vx_tostring_buffer, "%u", obj);   return _vx_tostring_buffer;)
_VX_TOSTRING_CREATE_BODY_FOR_TYPE(u16,  sprintf (_vx_tostring_buffer, "%u", obj);   return _vx_tostring_buffer;)
_VX_TOSTRING_CREATE_BODY_FOR_TYPE(u32,  sprintf (_vx_tostring_buffer, "%u", obj);   return _vx_tostring_buffer;)
_VX_TOSTRING_CREATE_BODY_FOR_TYPE(u64,  sprintf (_vx_tostring_buffer, "%lu", obj);  return _vx_tostring_buffer;)
_VX_TOSTRING_CREATE_BODY_FOR_TYPE(i8,   sprintf (_vx_tostring_buffer, "%d", obj);   return _vx_tostring_buffer;)
_VX_TOSTRING_CREATE_BODY_FOR_TYPE(i16,  sprintf (_vx_tostring_buffer, "%d", obj);   return _vx_tostring_buffer;)
_VX_TOSTRING_CREATE_BODY_FOR_TYPE(i32,  sprintf (_vx_tostring_buffer, "%d", obj);   return _vx_tostring_buffer;)
_VX_TOSTRING_CREATE_BODY_FOR_TYPE(i64,  sprintf (_vx_tostring_buffer, "%ld", obj);  return _vx_tostring_buffer;)
_VX_TOSTRING_CREATE_BODY_FOR_TYPE(f32,  sprintf (_vx_tostring_buffer, "%f", obj);   return _vx_tostring_buffer;)
_VX_TOSTRING_CREATE_BODY_FOR_TYPE(f64,  sprintf (_vx_tostring_buffer, "%lf", obj);  return _vx_tostring_buffer;)