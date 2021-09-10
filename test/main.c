#include "stdio.h"
#include <vx_utils.h>
#define DO_UNIMPLEMENTED_CRASH_TEST 0

/*  Test Data   */
typedef struct {
    u32 foo;
    bool bar;
    f32 baz;
} TestStruct;

VX_CREATE_DEFAULT(TestStruct, 
    .foo = 10,
    .bar = true,
    .baz = 100.0f
);

VX_T(u32, vx_Option) option_func_test(bool value) {
    if (value) {
        return VX_T(u32, vx_option_some)(1);
    }

    return VX_T(u32, vx_option_none)();
}

#define _TEMPLATE_STRUCT_TEST_ELEM(T) typedef struct {  \
    T value;                                            \
    T* type_ptr;                                        \
    T type_vec[3];                                      \
} VX_TEMPLATE_NAME(T, template_struct_test);
#define _TEMPLATE_FUNC_TEST_PT(T) T VX_TEMPLATE_NAME(T, template_func_test)(T value);
#define _TEMPLATE_FUNC_TEST_BD(T) T VX_TEMPLATE_NAME(T, template_func_test)(T value) {\
    return value + 1;                                   \
}
VX_TEMPLATE_PROT(u32, _TEMPLATE_FUNC_TEST_PT)
VX_TEMPLATE_BODY(u32, _TEMPLATE_FUNC_TEST_BD)
VX_TEMPLATE_ELEM(u32, _TEMPLATE_STRUCT_TEST_ELEM)
VX_TEMPLATE_PROT(f32, _TEMPLATE_FUNC_TEST_PT)
VX_TEMPLATE_BODY(f32, _TEMPLATE_FUNC_TEST_BD)
VX_TEMPLATE_ELEM(f32, _TEMPLATE_STRUCT_TEST_ELEM)
VX_TEMPLATE_PROT(i32, _TEMPLATE_FUNC_TEST_PT)
VX_TEMPLATE_BODY(i32, _TEMPLATE_FUNC_TEST_BD)
VX_TEMPLATE_ELEM(i32, _TEMPLATE_STRUCT_TEST_ELEM)

/*  Test Functions  */
bool assert_tests() {
    VX_ASSERT("10 == 10", 10 == 10);
    VX_ASSERT_EXIT_OP("10 == 10, EXIT_OP", 10 == 10, printf("Test\n"));
    VX_CHECK(10 == 10, 0);
    VX_CHECK_EXIT_OP(10 == 10, 0, printf("Test\n"));

    VX_NULL_ASSERT(1);
    VX_NULL_CHECK(1);

    return 1;
}

bool mem_tests() {
    /*  As long as it doesn't crash should be fine...   */
    byte* ptr = vx_smalloc(100);
    ptr = vx_srealloc(ptr, 125);
    free(ptr);

    i32 array[5] = { 1, 2, 3, 4, 5 };
    VX_CHECK(VX_SIZE_OF_CVECTOR(array) == 5, 0);

    return 1;
}

bool default_tests() {
    f32 a = VX_DEFAULT(f32);
    VX_CHECK(a == 0.0f, 0);
    i32 b = VX_DEFAULT(i32);
    VX_CHECK(b == 0, 0);
    TestStruct c = VX_DEFAULT(TestStruct);
    VX_CHECK(c.foo == 10, 0);
    VX_CHECK(c.bar == true, 0);
    VX_CHECK(c.baz == 100.0f, 0);

    return 1;
}

bool template_tests() {
    VX_CHECK(VX_T(u32, template_func_test)(10) == 11, 0);
    VX_CHECK(VX_T(i32, template_func_test)(10) == 11, 0);
    VX_CHECK(VX_T(f32, template_func_test)(10.0f) == 11.0f, 0);

    /*  Should be fine as long as does not throw compiler errors... */
    VX_T(u32, template_struct_test) a = {
        .type_ptr = NULL,
        .type_vec = { 1, 2, 3 },
        .value = 4
    };
    VX_CHECK(a.value == 4, 0);
    VX_T(f32, template_struct_test) b = {
        .type_ptr = NULL,
        .type_vec = { 1.0f, 2.0f, 3.0f },
        .value = 4.0f
    };
    VX_CHECK(b.value == 4.0f, 0);

    return 1;
}

bool option_tests() {
    VX_T(u32, vx_Option) a = option_func_test(true);
    VX_T(u32, vx_Option) b = option_func_test(false);

    VX_CHECK(a.is_some, 0);
    VX_CHECK(a.data, 0);
    VX_CHECK(!b.is_some, 0);

    return 1;
}

bool vector_tests() { 
    VX_T(u32, vx_Vector) vec = VX_T(u32, vx_vector_new)();
    VX_CHECK(VX_T(u32, vx_vector_top)(&vec) == NULL, 0);
    VX_CHECK(!VX_T(u32, vx_vector_pop)(&vec).is_some, 0);

    VX_T(u32, vx_vector_push)(&vec, 0);
    VX_T(u32, vx_vector_push)(&vec, 1);
    VX_T(u32, vx_vector_push)(&vec, 2);
    VX_T(u32, vx_vector_push)(&vec, 3);
    VX_T(u32, vx_vector_push)(&vec, 4);

    VX_CHECK(vec.length == 5, 0);
    VX_VECTOR_FOREACH(u32, elem, &vec, 
        VX_CHECK(elem == I, 0);         /*  I is an hidden variable created by the foreach macro.   */
    )
    VX_CHECK(VX_T(u32, vx_vector_get)(&vec, 10) == NULL, 0);
    VX_CHECK(*VX_T(u32, vx_vector_get)(&vec, 4) == 4, 0);
    VX_CHECK(*VX_T(u32, vx_vector_top)(&vec) == 4, 0);

    VX_T(u32, vx_vector_insert)(&vec, -1, 0);
    VX_CHECK(VX_VD(&vec)[0] == -1, 0);
    VX_T(u32, vx_vector_insert)(&vec, -2, 3);
    VX_CHECK(VX_VD(&vec)[3] == -2, 0);
    VX_T(u32, vx_vector_remove)(&vec, 0);
    VX_CHECK(VX_VD(&vec)[0] == 0, 0);
    VX_T(u32, vx_vector_remove)(&vec, 3);
    VX_CHECK(VX_VD(&vec)[3] == 3, 0);

    VX_CHECK(VX_T(u32, vx_vector_pop)(&vec).is_some, 0);
    VX_CHECK(VX_T(u32, vx_vector_pop)(&vec).data == 3, 0);

    VX_T(u32, vx_vector_clear)(&vec);
    VX_CHECK(vec.length == 0, 0);
    VX_T(u32, vx_vector_free)(&vec);    /*  Check if free with data remaining works.    */

    VX_T(u32, vx_vector_new)();

    return 1;
}

bool hashmap_tests() {
    VX_T(u32, vx_HashMap) map = VX_T(u32, vx_hashmap_new)();

    VX_T(u32, vx_hashmap_insert)(&map, 0, 1);
    VX_CHECK(map.length == 1, 0);
    VX_T(u32, vx_hashmap_insert)(&map, 1, 0);
    VX_CHECK(map.length == 2, 0);
    VX_VECTOR_FOREACH(u32, elem, &map.hashes,
        VX_CHECK(elem == I, 0);
    )

    VX_CHECK(*VX_T(u32, vx_hashmap_get)(&map, 0), 0);
    VX_CHECK(VX_T(u32, vx_hashmap_get)(&map, 100) == NULL, 0);

    VX_T(u32, vx_hashmap_remove)(&map, 1);
    VX_CHECK(VX_VD(&map.values), 0);

    VX_CHECK(!VX_T(u32, vx_hashmap_remove)(&map, 100).is_some, 0);

    VX_T(u32, vx_hashmap_free)(&map);

    return 1;
}

void unimplemented_test() {
    VX_UNIMPLEMENTED();
}

/*  Main    */
int main() {
    printf("ASSERT TESTS: ");
    VX_ASSERT("Assert tests failed!",   assert_tests());
    printf(" OK\n");

    printf("MEM TESTS: ");
    VX_ASSERT("Mem tests failed!",      mem_tests());
    printf(" OK\n");

    printf("DEFAULT TESTS: ");
    VX_ASSERT("Default tests failed!",  default_tests());
    printf(" OK\n");

    printf("TEMPLATE TESTS: ");
    VX_ASSERT("Template tests failed!", template_tests());
    printf(" OK\n");

    printf("OPTION TESTS: ");
    VX_ASSERT("Option tests failed!",   option_tests());
    printf(" OK\n");

    printf("VECTOR TESTS: ");
    VX_ASSERT("Vector tests failed!",   vector_tests());
    printf(" OK\n");

    printf("HASHMAP TESTS: ");
    VX_ASSERT("HashMap tests failed!",  hashmap_tests());
    printf(" OK\n");

    #if DO_UNIMPLEMENTED_CRASH_TEST
        printf("UNIMPLEMENTED TEST: if the program crashes, then this system works. ");
        unimplemented_test();
    #endif
    /*  Not gonna bother with tostring tests: That code is bad. I should remove it.    */

    return 0;
}
