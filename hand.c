#include "hand.h"

void calibrate_hand_basis(Hand* hand) {
    hand->basis[0] = (vec3) {1, 0, 0};
    hand->basis[1] = (vec3) {0, 1, 0};
    hand->basis[2] = (vec3) {0, 0, 1};
}

void update_hand(Hand* hand, rotation_vec3 hand_rotation, int16_t frequency, FingerSensorData finger_data[4]) {
    vec3 rotation_matrix[3];
    fill_rotation_matrix(hand_rotation, frequency, rotation_matrix);

    //set up inverse hand rotation
    vec3 reverse_hand_rotation[3];
    fill_rotation_matrix(hand_rotation, frequency, reverse_hand_rotation);
    // inverse of rotation matrix is same as transpose
    transpose_matrix(reverse_hand_rotation);

    for (int i = 0; i < 4; i++) {
        // apply finger rotation to fingers
        update_finger(&(hand->finger[i]), &finger_data[i], frequency, hand->basis);

        // remove hand rotation from fingers
        for (int j = 0; j < 3; j++) {
            hand->finger[i].basis[j] = multiply_vector_over_matrix(reverse_hand_rotation, hand->finger[i].basis[j]);
        }
    }

    // TODO: update thumb

    // update hand basis
    for (int i=0; i<=2; i++) {
        hand->basis[i] = multiply_vector_over_matrix(rotation_matrix, hand->basis[i]);
    }
}
