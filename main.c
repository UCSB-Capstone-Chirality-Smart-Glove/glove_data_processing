#include <stdio.h>
#include <stdbool.h>

#include "testing/util_test.h"
// #include "hand.h"

int main() {

    //--- test utils ---//
    // test_multiply_vector_over_matrix();
    // test_fill_rotation_matrix();
    // test_fill_change_basis_matrix();
    vec3 prev_grav = {0, 0, -1};
    vec3 gravity_vector = {1, -1, -1};
    vec3 rotation_matrix[3];
    accel_rotation_from_gravity(prev_grav, gravity_vector, rotation_matrix);
    print_matrix(rotation_matrix);
    // test_average_matrices();
    // while(running) {
    //     // update fingers

    //     // update hand basis

    //     // send data
    // }

    return 0;
}