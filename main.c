#include <stdio.h>
#include "vl_vector.h"

typedef struct {
    int id;
    double score;
} Student;

void print_int_vector(const VLVector* vec) {
    printf("Vector: [");
    for (size_t i = 0; i < vl_vector_size(vec); ++i) {
        int value = *(int*)vl_vector_at_const(vec, i);
        printf("%d", value);
        if (i < vl_vector_size(vec) - 1) printf(", ");
    }
    printf("] size=%zu cap=%zu dynamic=%s\n",
           vec->size, vec->capacity, vec->is_dynamic ? "yes" : "no");
}

void print_double_vector(const VLVector* vec) {
    printf("Double Vector: [");
    for (size_t i = 0; i < vl_vector_size(vec); ++i) {
        double value = *(double*) vl_vector_at_const(vec, i);
        printf("%.2f", value);
        if (i < vl_vector_size(vec) - 1) printf(", ");
    }
    printf("]\n");
}

void print_long_long_vector(const VLVector* vec) {
    printf("Long Long Vector: [");
    for (size_t i = 0; i < vl_vector_size(vec); ++i) {
        long long value = *(long long*) vl_vector_at_const(vec, i);
        printf("%lld", value);
        if (i < vl_vector_size(vec) - 1) printf(", ");
    }
    printf("]\n");
}

void print_student_vector(const VLVector* vec) {
    printf("Student Vector: [");
    for (size_t i = 0; i < vl_vector_size(vec); ++i) {
        const Student* s = (const Student*)vl_vector_at_const(vec, i);
        printf("{id: %d, score: %.1f}", s->id, s->score);
        if (i < vl_vector_size(vec) - 1) printf(", ");
    }
    printf("] size=%zu cap=%zu dynamic=%s\n",
           vec->size, vec->capacity, vec->is_dynamic ? "yes" : "no");
}

int main() {
    printf("   === INT TEST ===\n");
    VLVector int_vec;
    vl_vector_init(&int_vec, sizeof(int));
    for (int i = 0; i < 20; ++i) {
        vl_vector_push_back(&int_vec, &i);
    }
    printf("Int Vector size=%zu cap=%zu dynamic=%s\n",
           int_vec.size, int_vec.capacity, int_vec.is_dynamic ? "yes" : "no");
    vl_vector_free(&int_vec);


    printf("\n   === DOUBLE TEST ===\n");
    VLVector double_vec;
    vl_vector_init(&double_vec, sizeof(double));
    for (int i = 0; i < 20; ++i) {
        double d = i + 0.5;
        vl_vector_push_back(&double_vec, &d);
    }
    print_double_vector(&double_vec);
    printf("Double Vector size=%zu cap=%zu dynamic=%s\n",
           double_vec.size, double_vec.capacity, double_vec.is_dynamic ? "yes" : "no");
    vl_vector_free(&double_vec);


    printf("\n   === LONG LONG TEST ===\n");
    VLVector ll_vec;
    vl_vector_init(&ll_vec, sizeof(long long));
    for (int i = 0; i < 20; ++i) {
        long long val = 10000000000LL + i;
        vl_vector_push_back(&ll_vec, &val);
    }
    print_long_long_vector(&ll_vec);
    printf("Long Long Vector size=%zu cap=%zu dynamic=%s\n",
           ll_vec.size, ll_vec.capacity, ll_vec.is_dynamic ? "yes" : "no");
    vl_vector_free(&ll_vec);

    printf("\n=== STRUCT TEST ===\n");
    VLVector student_vec;
    vl_vector_init(&student_vec, sizeof(Student));

    for (int i = 0; i < 12; ++i) {
        Student s = {.id = i + 1, .score = 80.0 + i};
        vl_vector_push_back(&student_vec, &s);
    }

    print_student_vector(&student_vec);
    vl_vector_free(&student_vec);

    return 0;
}
