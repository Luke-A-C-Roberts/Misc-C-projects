#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// When manipulating 64 bit numbers, the constant 1 must be also of type uint64_t to avoid UB.
#define FILTER_BIT (uint64_t)1
#define TRY(something) if (something) {return EXIT_FAILURE;}

typedef struct {
    size_t   max_item_magnitude;
    size_t   num_uint64s       ;
    size_t   num_sets          ;
    uint64_t **data            ;
} UnionSet;

typedef enum {
    UnionSetSuccess        ,
    SetIndexNotFoundErr    ,
    NumExceedsMaxItemMagErr,
} UnionSetErrorCode;
  
UnionSet construct_union_set(size_t const max_item_magnitude, size_t const num_sets) {
    // create 2D array of 64 bit ints to work as bitmaps for each subset.
    uint64_t **data = malloc(sizeof(uint64_t*) * num_sets);
    size_t const num_uint64s = (max_item_magnitude / sizeof(uint64_t)) + 1;
    
    for (size_t i = 0; i < num_sets; ++i)
        data[i] = malloc(sizeof(uint64_t) * num_uint64s);

    return (UnionSet) {
        .max_item_magnitude = max_item_magnitude,
        .num_uint64s        = num_uint64s,
        .num_sets           = num_sets,
        .data               = data
    }; 
}

void disp_union_set(UnionSet const union_set) {
    for (size_t i = 0; i < union_set.num_sets; ++i) {
        printf("%ld = {", i);
        
        for (size_t j = 0; j < union_set.num_uint64s; ++j) {
            uint64_t bit_set = union_set.data[i][j];
            for (size_t k = 0; k < 64; ++k) {
                if (bit_set & FILTER_BIT) printf("%ld, ", j * 64 + k);
                bit_set >>= 1;
            }
        } 
        printf("}\n");
    }
}

void destroy_union_set(UnionSet union_set) {
    for (size_t i = 0; i < union_set.num_sets; ++i)
        free(union_set.data[i]);
    free(union_set.data);
}

void add_num_to_union_set(UnionSet union_set, size_t const subset_index, size_t const value) {
    // get the bitmap block index and index in block by divmod
    size_t const int64_index = value / 64;
    size_t const int64_sub_index = value % 64;

    // bit manipulate by or operation
    union_set.data[subset_index][int64_index] |= FILTER_BIT << int64_sub_index;
}

UnionSetErrorCode add_many_nums_to_union_set(
    UnionSet union_set,
    size_t const subset_index,
    size_t const num_values,
    size_t const values[num_values]
) {
    // check the subset exists and that the value is less than the maximum possible
    if (subset_index > union_set.num_sets) return SetIndexNotFoundErr;
    for (size_t i = 0; i < num_values; ++i) {
        if (values[i] > union_set.max_item_magnitude) return NumExceedsMaxItemMagErr;
    }

    for (size_t i = 0; i < num_values; ++i)
        add_num_to_union_set(union_set, subset_index, values[i]);
    
    return UnionSetSuccess;
}

int report_union_set_error_code(UnionSetErrorCode userr) {
    if (userr != UnionSetSuccess) {
        switch (userr) {
            case (SetIndexNotFoundErr)    : printf("An invalid set index was supplied.\n"); break;
            case (NumExceedsMaxItemMagErr): printf("An invalid set index was supplied.\n"); break;
            default                       : printf("Some UnionSetError has occured.\n")   ; break;
        }
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int main(void) {
    UnionSet us = construct_union_set(100, 3);

    TRY(report_union_set_error_code(add_many_nums_to_union_set(us, 0, 5, (size_t[5]){ 31, 16, 22, 4 , 20        })));
    TRY(report_union_set_error_code(add_many_nums_to_union_set(us, 1, 7, (size_t[7]){ 88, 43, 25, 31, 41, 16, 8 })));
    TRY(report_union_set_error_code(add_many_nums_to_union_set(us, 2, 6, (size_t[6]){ 90, 26, 43, 2 , 78, 10    })));

    disp_union_set(us);
    destroy_union_set(us);
    
    return EXIT_SUCCESS;
}
