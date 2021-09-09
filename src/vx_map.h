#pragma once
#include "vx_types.h"
#include "vx_vector.h"

typedef u64 vx_HashMap_Hash;

#define _VX_HASHMAP_ELEM(T) typedef struct {                                                        \
    VX_VECTOR(T) values;                                                                            \
    VX_VECTOR(vx_HashMap_Hash) hashes;                                                              \
    u32 length;                                                                                     \
} VX_TEMPLATE_NAME(T, vx_HashMap);
#define _VX_HASHMAP_NEW_INL(T) static inline VX_TEMPLATE_NAME(T, vx_HashMap) VX_TEMPLATE_NAME(T, vx_hashmap_new)() {\
    VX_TEMPLATE_NAME(T, vx_HahsMap) map;                                                            \
    map.values = vx_vector_new();                                                                   \
    map.hashes = vx_vector_new();                                                                   \
    map.length = 0;                                                                                 \
    return map;                                                                                     \
}
#define _VX_HASHMAP_FREE_INL(T) static inline void VX_TEMPLATE_NAME(T, vx_hashmap_free)(VX_TEMPLATE_NAME(T, vx_HashMap)* map) {\
    vx_vector_free(&map->values);\
    vx_vector()\
}
