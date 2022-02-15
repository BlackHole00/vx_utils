#include "vx_mem.h"

#include <stdio.h>
#include <malloc.h>
#include "vx_panic.h"

static u32 allocation_number = 0;
static u32 deallocation_number = 0;
static u32 reallocation_number = 0;
static u32 reallocation_calls = 0;

void* vx_smalloc(usize size) {
    void* ptr = malloc(size);
    VX_ASSERT("Could not allocate memory!", ptr != 0 || size == 0);

    allocation_number++;

    return ptr;
}

void* vx_srealloc(void* mem_adr, usize size) {
    void* ptr = realloc(mem_adr, size);
    VX_ASSERT("Could not reallocate memory!", ptr != 0 || size == 0);

    /* Free old memory. */
    if (ptr != mem_adr) {
        free(mem_adr);

        allocation_number++;
        deallocation_number++;
        reallocation_number++;
    }

    reallocation_calls++;

    return ptr;
}

void vx_free(void* ptr) {
    free(ptr);

    deallocation_number++;
}

void vx_memory_print_state() {
    printf("---[Memory state]---\n");
    printf("\tALLOCATIONS: %d;\n", allocation_number);
    printf("\tDEALLOCATIONS: %d\n", deallocation_number);
    printf("\tREALLOCATIONS: %d\n", reallocation_calls);
    printf("\tREAL REALLOCATIONS: %d\n", reallocation_number);
    printf("\tALLOCATIONS (w/o reallocations): %d;\n", allocation_number - reallocation_number);
    printf("\tDEALLOCATIONS (w/o reallocations): %d;\n", deallocation_number - reallocation_number);
    printf("\nThere are %d blocks to free!\n", allocation_number - deallocation_number);
    printf("--------------------\n");
}
