#ifndef HAND
#define HAND

#include "finger.h"

// internal hand data
// fingers indexed 0-3 are the index, middle, ring and pinky fingers, respectively
typedef struct {
    Finger finger[4];
    Thumb thumb;
    vec3 basis[3];
} Hand;

// packaged hand data to send via bluetooth
typedef struct {
    FingerSendData finger[4];
    Thumb thumb;
    vec3 basis[3];
} HandSendData;

// set basis to unit vectors [1,0,0], [0,1,0], [0,0,1]
void calibrate_hand_basis(Hand* hand);

// use angular rate data from hand IMU to rotate basis vectors and update fingers
// - finger_data: an array of FingerSensorDatas of size 4, corresponding to each finger
void update_hand(Hand* hand, rotation_vec3 rotation, int16_t frequency, FingerSensorData* finger_data);

// set data up to send via bluetooth
HandSendData package_hand_data(Hand* hand);

#endif