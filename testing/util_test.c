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
        .roll = 135,
        .pitch = 360,
        .yaw = 285
    };
    double frequency = 3;
    vec3 result[3] = {(vec3) {0, 0, 0},
                      (vec3) {0, 0, 0}, 
                      (vec3) {0, 0, 0}};
    vec3 expected_result[3] = {(vec3) {0.0435779,-0.4980974, -0.8660254},
                               (vec3) {-0.7577878, 0.5484138, -0.3535534},
                               (vec3) {0.6510442, 0.6716706, -0.3535534}};
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