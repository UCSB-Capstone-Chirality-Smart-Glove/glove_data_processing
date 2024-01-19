#ifndef FINGER
#define FINGER

#include <stdint.h>
#include "util.h"

// describe a finger with its basis and bend
// basis[0] is the finger's direction and IMU's x-axis, basis[1/2] are orthonormal vectors corresponding to the IMU's y and z axes
typedef struct {
    vec3 basis[3];
    int bend;
} Finger;

// describe a finger with the direction it's pointing in (using cartesian vectors, with hand basis), and bend (in degrees)
typedef struct {
    vec3 direction;
    int bend;
} FingerSendData;

// incoming finger IMU data
typedef struct {
    rotation_vec3 base;
    rotation_vec3 tip;
} FingerSensorData;

// Returns change in bend in degrees
// - base: rotation_vec3 containing angular rate data
// - tip: rotation_vec3 with angular rate data
int16_t get_bend(FingerSensorData finger_data, int16_t frequency);

// Sets finger direction to vector [1, 0, 0] and bend to 0
// potentially recalibrate using accelerometer and gravity in the future
void calibrate_finger(Finger* finger);

// updates the direction and bend of the passed finger, using IMU data for the base and tip of the finger
void update_finger(Finger* finger, FingerSensorData finger_data, int16_t frequency, vec3* hand_basis);

typedef struct {
    Finger finger;
    int knuckle_rotation;
} Thumb;

// Sets finger direction to vector [1, 0, 0], bend to 0, knuckle rotation to 0
void calibrate_thumb(Thumb* thumb);

// updates thumb by updating the finger portion of thumb and knuckle rotation separately
void update_thumb(Thumb* thumb, FingerSensorData finger_data, int16_t knuckle_rotation_change, int16_t frequency, vec3* hand_basis);

// need bend-resistance graph to implement this
int16_t get_flex_angle(float voltage);

// set data up to send via bluetooth
FingerSendData package_finger_data(Finger* finger);

#endif