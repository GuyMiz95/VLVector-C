#include "vl_vector.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static size_t compute_new_capacity(size_t current_size) {
    return (3 * current_size) / 2;
}

void vl_vector_init(VLVector* vec, size_t elem_size) {
    vec->size = 0;
    vec->capacity = VL_VECTOR_INIT_CAP;
    assert(elem_size <= MAX_ELEM_SIZE);
    vec->elem_size = elem_size;
    vec->dynamic_data = NULL;
    vec->is_dynamic = false;
}

void vl_vector_free(VLVector* vec) {
    if (vec->is_dynamic) {
        free(vec->dynamic_data);
    }
    vec->dynamic_data = NULL;
}

static void* get_storage(VLVector* vec) {
    return vec->is_dynamic ? vec->dynamic_data : vec->static_data;
}

static const void* get_storage_const(const VLVector* vec) {
    return vec->is_dynamic ? vec->dynamic_data : vec->static_data;
}

bool vl_vector_push_back(VLVector* vec, const void* value) {
    if (vec->size == vec->capacity) {
        size_t new_capacity = compute_new_capacity(vec->size + 1);
        void* new_data = malloc(new_capacity * vec->elem_size);
        if (!new_data) return false;

        memcpy(new_data, get_storage(vec), vec->size * vec->elem_size);
        if (vec->is_dynamic) free(vec->dynamic_data);
        vec->dynamic_data = new_data;
        vec->capacity = new_capacity;
        vec->is_dynamic = true;
    }

    void* dest = (char*)get_storage(vec) + vec->size * vec->elem_size;
    memcpy(dest, value, vec->elem_size);
    vec->size++;
    return true;
}

void vl_vector_pop_back(VLVector* vec) {
    if (vec->size == 0) return;
    vec->size--;

    if (vec->is_dynamic && vec->size <= VL_VECTOR_INIT_CAP) {
        memcpy(vec->static_data, vec->dynamic_data, vec->size * vec->elem_size);
        free(vec->dynamic_data);
        vec->dynamic_data = NULL;
        vec->capacity = VL_VECTOR_INIT_CAP;
        vec->is_dynamic = false;
    }
}

void* vl_vector_at(VLVector* vec, size_t index) {
    if (index >= vec->size) return NULL;
    return (char*)get_storage(vec) + index * vec->elem_size;
}

const void* vl_vector_at_const(const VLVector* vec, size_t index) {
    if (index >= vec->size) return NULL;
    return (const char*)get_storage_const(vec) + index * vec->elem_size;
}

void* vl_vector_data(VLVector* vec) {
    return get_storage(vec);
}

const void* vl_vector_data_const(const VLVector* vec) {
    return get_storage_const(vec);
}

size_t vl_vector_size(const VLVector* vec) {
    return vec->size;
}

size_t vl_vector_capacity(const VLVector* vec) {
    return vec->capacity;
}

void vl_vector_clear(VLVector* vec) {
    if (vec->is_dynamic) {
        free(vec->dynamic_data);
        vec->dynamic_data = NULL;
        vec->is_dynamic = false;
    }
    vec->size = 0;
    vec->capacity = VL_VECTOR_INIT_CAP;
}
