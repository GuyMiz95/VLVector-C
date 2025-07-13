#ifndef VL_VECTOR_H
#define VL_VECTOR_H

#include <stddef.h>
#include <stdbool.h>

#define VL_VECTOR_INIT_CAP 16
#define MAX_ELEM_SIZE 16 // 16 allows double long long and a simple 2 field struct
/**
 * Generic Variable Length Vector data structure that provides storage for elements of various types, capable of
 * changing it's size through runtime
 */
typedef struct {
    // pointer to memory located at heap
    void* dynamic_data;
    // pointer to memory located at stack
    char static_data[VL_VECTOR_INIT_CAP * MAX_ELEM_SIZE]; // allow larger data types and confine their available size
    // amount of elements
    size_t size;
    // vector current capacity
    size_t capacity;
    // size of element (should not exceed MAX_ELEM_SIZE)
    size_t elem_size;
    // flag for dynamic mode (switching from static to heap based memory)
    bool is_dynamic;
} VLVector;

/**
 * Initializes a new VLVector with given element size.
 * @param vec Pointer to vector to initialize.
 * @param elem_size Size of a single element in Bytes.
 */
void vl_vector_init(VLVector* vec, size_t elem_size);

/**
 * Frees all dynamically allocated memory used by the vector.
 * @param vec Vector to be completely freed.
 */
void vl_vector_free(VLVector* vec);

/**
 * Appends a new element to the end of the vector
 * @param vec Vector to add element to.
 * @param value value to add to element.
 * @return true upon success, otherwise false.
 */
bool vl_vector_push_back(VLVector* vec, const void* value);

/**
 * Removes the last element from the vector.
 * @param vec Vector to remove element from.
 */
void vl_vector_pop_back(VLVector* vec);

/**
 * Returns a pointer to the element at given index.
 * @param vec Vector to extract pointer from
 * @param index Index of element to extract its pointer.
 * @return Pointer of element.
 */
void* vl_vector_at(VLVector* vec, size_t index);

/**
 * Read-only version of element
 * @param vec Vector to extract read-only version of pointer
 * @param index Index of element to extract its pointer (read only mode)
 * @return Pointer of element.
 */
const void* vl_vector_at_const(const VLVector* vec, size_t index);

/**
 * Returns a pointer to the underlying array used for storage
 * @param vec Vector to extract data from
 * @return Pointer to data (can be also cast to type* upon extraction)
 */
void* vl_vector_data(VLVector* vec);

/**
 * Read-only version of vl_vector_data.
 * @param vec Vector to extract data from.
 * @return Pointer to data.
 */
const void* vl_vector_data_const(const VLVector* vec);

/**
 * Returns the number of elements currently stored in the vector.
 * @param vec Vector to extract size from.
 * @return Size of vector.
 */
size_t vl_vector_size(const VLVector* vec);

/**
 * Returns the current capacity (num of elements)
 * @param vec Vector to retrieve its capacity
 * @return Capacity of vector
 */
size_t vl_vector_capacity(const VLVector* vec);

/**
 * Removes all elements from the vector (and resets it to static mode).
 * @param vec Vector to remove all elements from.
 */
void vl_vector_clear(VLVector* vec);

#endif
