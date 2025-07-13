#include "vl_vector_int.h"
#include <stdlib.h>
#include <string.h>



static size_t compute_new_capacity(size_t current_size, size_t to_add) {
    return (3 * (current_size + to_add)) / 2;
}

void vl_vector_init(VLVectorInt* vec) {
    vec->size = 0;
    vec->capacity = VL_VECTOR_INIT_CAP;
    vec->dynamic_data = NULL;
    vec->is_dynamic = false;
}

void vl_vector_destroy(VLVectorInt* vec) {
    if (vec->is_dynamic) {
        free(vec->dynamic_data);
        vec->dynamic_data = NULL;
    }
}

static int* vl_vector_get_storage(VLVectorInt* vec) {
    return vec->is_dynamic ? vec->dynamic_data : vec->static_data;
}

bool vl_vector_push_back(VLVectorInt* vec, int value) {
    if (vec->size == vec->capacity) {
        size_t new_capacity = compute_new_capacity(vec->size, 1);
        int* new_data = (int*)malloc(new_capacity * sizeof(int));
        if (!new_data) return false;
        memcpy(new_data, vl_vector_get_storage(vec), vec->size * sizeof(int));

        if (vec->is_dynamic) free(vec->dynamic_data);
        vec->dynamic_data = new_data;
        vec->is_dynamic = true;
        vec->capacity = new_capacity;
    }

    vl_vector_get_storage(vec)[vec->size++] = value;
    return true;
}

void vl_vector_pop_back(VLVectorInt* vec) {
    if (vec->size == 0) return;
    vec->size--;

    if (vec->is_dynamic && vec->size <= VL_VECTOR_INIT_CAP) {
        memcpy(vec->static_data, vec->dynamic_data, vec->size * sizeof(int));
        free(vec->dynamic_data);
        vec->dynamic_data = NULL;
        vec->capacity = VL_VECTOR_INIT_CAP;
        vec->is_dynamic = false;
    }
}

int vl_vector_at(const VLVectorInt* vec, size_t index) {
    if (index >= vec->size) {
        return -1;
    }
    return vl_vector_get_storage((VLVectorInt*)vec)[index];
}

int* vl_vector_data(VLVectorInt* vec) {
    return vl_vector_get_storage(vec);
}

size_t vl_vector_size(const VLVectorInt* vec) {
    return vec->size;
}

size_t vl_vector_capacity(const VLVectorInt* vec) {
    return vec->capacity;
}

void vl_vector_clear(VLVectorInt* vec) {
    if (vec->is_dynamic) {
        free(vec->dynamic_data);
        vec->dynamic_data = NULL;
    }
    vec->size = 0;
    vec->capacity = VL_VECTOR_INIT_CAP;
    vec->is_dynamic = false;
}
