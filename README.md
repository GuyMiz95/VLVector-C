# VLVector-C

A generic, hybrid vector implementation in C that uses stack memory for small arrays and switches to dynamic heap allocation for larger ones. Inspired by C++'s `std::vector`.

---

## Features

- Supports any data type (`int`, `double`, `long long`, `struct`, etc.)
- Stack buffer for small sizes (no heap allocation)
- Automatic transition to heap allocation when needed
- Safe insertions, deletions, and memory handling
- Fully generic using `void*` and `elem_size`

---

## Usage (with examples!)

### 1. Initialize a vector

```
VLVector vec;
vl_vector_init(&vec, sizeof(int));  // For integers
```

### 2. Push elements 
```
int val = 42;
vl_vector_push_back(&vec, &val);
```
#### Important!!: Under intention of using a more complicated data type\structure - MAX_ELEM_SIZE must be changed accordingly.

### 3. Access elements
``` 
int* val_ptr = (int*)vl_vector_at(&vec, 0);
printf("%d\n", *val_ptr);
```

### 4. Clean up
```
vl_vector_free(&vec);
```

### 5. Compiling
```
gcc -Wall -Wextra -std=c99 main.c vl_vector.c -o vlvector
./vlvector
```

## Tested Types:
int, double, long long, simple struct with 2 fields (int and double)
