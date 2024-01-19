#include <stdio.h>
#include <math.h>
#include "../util.h"

// returns 1 if true, 0 if false
int vectors_are_same(vec3 a, vec3 b);

void print_vector(vec3 vec);

// prints internal vec3's as columns
void print_matrix(vec3 matrix[3]);

void test_multiply_vector_over_matrix();

void test_fill_rotation_matrix();

void test_fill_change_basis_matrix();