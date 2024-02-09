#include "util_test.h"

// returns 1 if true, 0 if false
int vectors_are_same(vec3 a, vec3 b) {
    return fabs(a.x - b.x) < 0.00001 && fabs(a.y - b.y) < 0.00001 && fabs(a.z - b.z) < 0.00001;
}

void print_vector(vec3 vec) {
    printf("[%f, %f, %f]\n", vec.x, vec.y, vec.z);
}

void print_matrix(vec3 matrix[3]) {
    printf("|%f, %f, %f|", matrix[0].x, matrix[1].x, matrix[2].x);
    printf("\n");
    printf("|%f, %f, %f|", matrix[0].y, matrix[1].y, matrix[2].y);
    printf("\n");
    printf("|%f, %f, %f|", matrix[0].z, matrix[1].z, matrix[2].z);
    printf("\n");
}

void test_multiply_vector_over_matrix() {
    printf("Testing multiply_vector_over_matrix...");
    vec3 matrix[3] = {(vec3) {0, 1, 2},
                      (vec3) {4, 5, 6}, 
                      (vec3) {7, 8, 9}};
    vec3 vector = (vec3) {10, 10, 10};
    vec3 expected_result = (vec3) {110, 140, 170};
    vec3 result = multiply_vector_over_matrix(matrix, vector);
    if (vectors_are_same(expected_result, result)) {
        printf("Success!\n");
    }
    else {
        printf("Failed:\n");
        printf("Expected:\n");
        print_vector(expected_result);
        printf("Actual:\n");
        print_vector(result);
    }
}

void test_fill_rotation_matrix() {
    printf("Testing fill_rotation_matrix...");
    rotation_vec3 rotation = (rotation_vec3) {
        .roll = 450,
        .pitch = 750,
        .yaw = 300
    };
    double frequency = 10;
    vec3 result[3] = {(vec3) {0, 0, 0},
                      (vec3) {0, 0, 0}, 
                      (vec3) {0, 0, 0}};
    vec3 expected_result[3] = {(vec3) {0.2241439,0.9450597, -0.2379530},
                               (vec3) {-0.1294095, 0.2708661, 0.9538788},
                               (vec3) {0.9659258, -0.1830127, 0.1830127 }};
    fill_rotation_matrix(rotation, frequency, result);
    if (vectors_are_same(expected_result[0], result[0]) &&
        vectors_are_same(expected_result[1], result[1]) &&
        vectors_are_same(expected_result[2], result[2])
    ) {
        printf("Success!\n");
    }
    else {
        printf("Failed:\n");
        printf("Expected:\n");
        print_matrix(expected_result);
        printf("Actual:\n");
        print_matrix(result);
    }
}

void test_fill_change_basis_matrix() {
    printf("Testing fill_change_basis_matrix...");
    vec3 old_basis[3] = {(vec3) {1, 0, 0}, 
                         (vec3) {0, 1, 0}, 
                         (vec3) {0, 0, 1}};
    vec3 new_basis[3] = {(vec3) {1, 2, 3}, 
                         (vec3) {2, 1, 4}, 
                         (vec3) {3, 1, 9}};
    vec3 change_basis_matrix[3] = {(vec3) {1, 0, 0}, 
                                   (vec3) {0, 1, 0}, 
                                   (vec3) {0, 0, 1}};
    fill_change_basis_matrix(old_basis, new_basis, change_basis_matrix);
    vec3 test_input = (vec3) {1, 2, 3};
    vec3 expected_output = (vec3) {1, 0, 0};
    vec3 output = multiply_vector_over_matrix(change_basis_matrix, test_input);

    if (vectors_are_same(expected_output, output)) {
        printf("Success!\n");
    }
    else {
        printf("Failed:\n");
        printf("Expected:\n");
        print_vector(expected_output);
        printf("Actual:\n");
        print_vector(output);
        printf("Matrix:\n");
        print_matrix(change_basis_matrix);
    }

}

void test_average_matrices() {
    printf("Testing average_matrices...");
    vec3 m1[3] = {
        (vec3) {1, 1, 1}, 
        (vec3) {3, 3, 3}, 
        (vec3) {7, 7, 7}
    };
    vec3 m2[3] = {
        (vec3) {2, 4, 6}, 
        (vec3) {2, 4, 6}, 
        (vec3) {2, 4, 6}
    };
    vec3 m3[3] = {
        (vec3) {5, 5, 5}, 
        (vec3) {5, 5, 5}, 
        (vec3) {5, 5, 5}, 
    };
    vec3 *matrices[3] = {m1, m2, m3};
    float weights[3] = {0.3, 0.5, 0.2};
    vec3 result[3];
    average_matrices(matrices, weights, 3, result);
    vec3 expected_result[3] = {
        (vec3) {2.3, 3.3, 4.3}, 
        (vec3) {2.9, 3.9, 4.9},
        (vec3) {4.1, 5.1, 6.1}
    };
    if (vectors_are_same(expected_result[0], result[0]) &&
        vectors_are_same(expected_result[1], result[1]) &&
        vectors_are_same(expected_result[2], result[2])
    ) {
        printf("Success!\n");
    }
    else {
        printf("Failed:\n");
        printf("Expected:\n");
        print_matrix(expected_result);
        printf("Actual:\n");
        print_matrix(result);
    }
}