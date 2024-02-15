#include <stdio.h>
#include <stdbool.h>

#include "testing/util_test.h"
// #include "hand.h"

int main() {
    printf("bruh\n");

    //--- test utils ---//
    // test_multiply_vector_over_matrix();
    // test_fill_rotation_matrix();
    // test_fill_change_basis_matrix();
    vec3 gravity_vector = {0, 0, -1};
    vec3* rot_matrix = rotation_from_gravity(gravity_vector);
    print_matrix(rot_matrix);
    test_average_matrices();
    // while(running) {
    //     // update fingers

    //     // update hand basis

    //     // send data
    // }

    return 0;
}