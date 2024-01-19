#include <math.h>
#include "finger.h"

int16_t get_bend(FingerSensorData finger_data, int16_t frequency) {
    return (finger_data.base.pitch - finger_data.tip.pitch)/frequency;
}

void calibrate_finger(Finger* finger) {
    finger->basis[0] = (vec3) {1, 0, 0};
    finger->basis[1] = (vec3) {0, 1, 0};
    finger->basis[2] = (vec3) {0, 0, 1};
}

void update_finger(Finger* finger, FingerSensorData finger_data, int16_t frequency, vec3* hand_basis) {
    // update direction
    vec3 rotation_matrix[3];
    fill_rotation_matrix(finger_data.base, frequency, rotation_matrix);
    // change rotation matrix basis from 
    vec3 imu_to_hand_basis[3];
    fill_change_basis_matrix(finger->basis, hand_basis, imu_to_hand_basis);
    for (int i = 0; i < 3; i++) {
        rotation_matrix[i] = multiply_vector_over_matrix(imu_to_hand_basis, rotation_matrix[i]);
    }
    for (int i = 0; i < 3; i++) {
        finger->basis[i] = multiply_vector_over_matrix(rotation_matrix, finger->basis[i]);
    }

    // update bend
    int16_t bend_change = get_bend(finger_data, frequency);
    finger->bend += bend_change;
}

void calibrate_thumb(Thumb* thumb) {
    calibrate_finger(&(thumb->finger));
    thumb->knuckle_rotation = 0;
}

void update_thumb(Thumb* thumb, FingerSensorData finger_data, int16_t knuckle_rotation_change, int16_t frequency, vec3* hand_basis) {
    // could probably do some sensor fusion here to make the finger data more accurate
    update_finger(&(thumb->finger), finger_data, frequency, hand_basis);
    thumb->knuckle_rotation += knuckle_rotation_change;
}
