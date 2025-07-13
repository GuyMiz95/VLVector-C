#ifndef VL_VECTOR_INT_H
#define VL_VECTOR_INT_H

#include <stddef.h>
#include <stdbool.h>

#define VL_VECTOR_INIT_CAP 16

typedef struct {
    size_t size;
    size_t capacity;
    int* dynamic_data;
    int static_data[VL_VECTOR_INIT_CAP];
    bool is_dynamic;
} VLVectorInt;

void vl_vector_init(VLVectorInt* vec);
void vl_vector_destroy(VLVectorInt* vec);
bool vl_vector_push_back(VLVectorInt* vec, int value);
void vl_vector_pop_back(VLVectorInt* vec);
int vl_vector_at(const VLVectorInt* vec, size_t index);
int* vl_vector_data(VLVectorInt* vec);
size_t vl_vector_size(const VLVectorInt* vec);
size_t vl_vector_capacity(const VLVectorInt* vec);
void vl_vector_clear(VLVectorInt* vec);

#endif
