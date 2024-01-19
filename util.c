#include "util.h"

vec3 multiply_vector_over_matrix(vec3 matrix[3], vec3 vector) {
    vec3 result = (vec3) {
        .x = (matrix[0].x*vector.x) + (matrix[1].x*vector.y) + (matrix[2].x*vector.z),
        .y = (matrix[0].y*vector.x) + (matrix[1].y*vector.y) + (matrix[2].y*vector.z),
        .z = (matrix[0].z*vector.x) + (matrix[1].z*vector.y) + (matrix[2].z*vector.z)
    };
    return result;
}

void fill_rotation_matrix(rotation_vec3 rotation, double frequency, vec3 matrix[3]) {
    int16_t roll = rotation.roll/frequency*ANGLE_RESOLUTION;
    int16_t pitch = rotation.pitch/frequency*ANGLE_RESOLUTION;
    int16_t yaw = rotation.yaw/frequency*ANGLE_RESOLUTION;

    matrix[0].x = cosine[yaw]*cosine[pitch];
    matrix[0].y = sine[yaw]*cosine[pitch];
    matrix[0].z = -sine[pitch];
    matrix[1].x = cosine[yaw]*sine[pitch]*sine[roll] - sine[yaw]*cosine[roll];
    matrix[1].y = sine[yaw]*sine[pitch]*sine[roll] + cosine[yaw]*cosine[roll];
    matrix[1].z = cosine[pitch]*sine[roll];
    matrix[2].x = cosine[yaw]*sine[pitch]*cosine[roll] + sine[yaw]*sine[roll];
    matrix[2].y = sine[yaw]*sine[pitch]*cosine[roll] - cosine[yaw]*sine[roll];
    matrix[2].z = cosine[pitch]*cosine[roll];
}

void fill_change_basis_matrix(vec3 old[3], vec3 new[3], vec3 matrix[3]) {
    // find inverse of old basis
    vec3 old_inverse[3] = {
        (vec3) {
            .x = old[1].y*old[2].z - old[1].z*old[2].y,
            .y = old[1].z*old[2].x - old[1].x*old[2].z,
            .z = old[1].x*old[2].y - old[1].y*old[2].x
        },
        (vec3) {
            .x = old[0].z*old[2].y - old[0].y*old[2].z,
            .y = old[0].x*old[2].z - old[0].z*old[2].x,
            .z = old[0].y*old[2].x - old[0].x*old[2].y
        }, 
        (vec3) {
            .x = old[0].y*old[1].z - old[0].z*old[1].y,
            .y = old[0].z*old[1].x - old[0].x*old[1].z,
            .z = old[0].x*old[1].y - old[0].y*old[1].x
        }
    };
    // multiply new basis by inverse of old basis
    matrix[0] = multiply_vector_over_matrix(old_inverse, new[0]);
    matrix[1] = multiply_vector_over_matrix(old_inverse, new[1]);
    matrix[2] = multiply_vector_over_matrix(old_inverse, new[2]);
}

void swap(double* a, double* b) {
    double swap = *a;
    *a = *b;
    *b = swap;
}

void transpose_matrix(vec3 matrix[3]) {
    swap(&matrix[0].y, &matrix[1].x);
    swap(&matrix[0].z, &matrix[2].x);
    swap(&matrix[1].z, &matrix[2].y);
}

float LSB_to_degrees = angular_rate_max / INT16_MAX;

int ANGLE_RESOLUTION = 1;
float sine[360] = {0,0.0174524,0.0348995,0.052336,0.0697565,0.0871557,0.104528,0.121869,0.139173,0.156434,0.173648,0.190809,0.207912,0.224951,0.241922,0.258819,0.275637,0.292372,0.309017,0.325568,0.34202,0.358368,0.374607,0.390731,0.406737,0.422618,0.438371,0.45399,0.469472,0.48481,0.5,0.515038,0.529919,0.544639,0.559193,0.573576,0.587785,0.601815,0.615661,0.62932,0.642788,0.656059,0.669131,0.681998,0.694658,0.707107,0.71934,0.731354,0.743145,0.75471,0.766044,0.777146,0.788011,0.798636,0.809017,0.819152,0.829038,0.838671,0.848048,0.857167,0.866025,0.87462,0.882948,0.891007,0.898794,0.906308,0.913545,0.920505,0.927184,0.93358,0.939693,0.945519,0.951057,0.956305,0.961262,0.965926,0.970296,0.97437,0.978148,0.981627,0.984808,0.987688,0.990268,0.992546,0.994522,0.996195,0.997564,0.99863,0.999391,0.999848,1,0.999848,0.999391,0.99863,0.997564,0.996195,0.994522,0.992546,0.990268,0.987688,0.984808,0.981627,0.978148,0.97437,0.970296,0.965926,0.961262,0.956305,0.951057,0.945519,0.939693,0.93358,0.927184,0.920505,0.913545,0.906308,0.898794,0.891007,0.882948,0.87462,0.866025,0.857167,0.848048,0.838671,0.829038,0.819152,0.809017,0.798636,0.788011,0.777146,0.766044,0.75471,0.743145,0.731354,0.71934,0.707107,0.694658,0.681998,0.669131,0.656059,0.642788,0.62932,0.615661,0.601815,0.587785,0.573576,0.559193,0.544639,0.529919,0.515038,0.5,0.48481,0.469472,0.453991,0.438371,0.422618,0.406737,0.390731,0.374607,0.358368,0.34202,0.325568,0.309017,0.292372,0.275637,0.258819,0.241922,0.224951,0.207912,0.190809,0.173648,0.156434,0.139173,0.121869,0.104528,0.0871557,0.0697565,0.052336,0.0348995,0.0174524,3.5898e-09,-0.0174524,-0.0348995,-0.052336,-0.0697565,-0.0871557,-0.104528,-0.121869,-0.139173,-0.156434,-0.173648,-0.190809,-0.207912,-0.224951,-0.241922,-0.258819,-0.275637,-0.292372,-0.309017,-0.325568,-0.34202,-0.358368,-0.374607,-0.390731,-0.406737,-0.422618,-0.438371,-0.45399,-0.469472,-0.48481,-0.5,-0.515038,-0.529919,-0.544639,-0.559193,-0.573576,-0.587785,-0.601815,-0.615661,-0.62932,-0.642788,-0.656059,-0.669131,-0.681998,-0.694658,-0.707107,-0.71934,-0.731354,-0.743145,-0.75471,-0.766044,-0.777146,-0.788011,-0.798636,-0.809017,-0.819152,-0.829038,-0.838671,-0.848048,-0.857167,-0.866025,-0.87462,-0.882948,-0.891007,-0.898794,-0.906308,-0.913545,-0.920505,-0.927184,-0.93358,-0.939693,-0.945519,-0.951057,-0.956305,-0.961262,-0.965926,-0.970296,-0.97437,-0.978148,-0.981627,-0.984808,-0.987688,-0.990268,-0.992546,-0.994522,-0.996195,-0.997564,-0.99863,-0.999391,-0.999848,-1,-0.999848,-0.999391,-0.99863,-0.997564,-0.996195,-0.994522,-0.992546,-0.990268,-0.987688,-0.984808,-0.981627,-0.978148,-0.97437,-0.970296,-0.965926,-0.961262,-0.956305,-0.951057,-0.945519,-0.939693,-0.93358,-0.927184,-0.920505,-0.913545,-0.906308,-0.898794,-0.891007,-0.882948,-0.87462,-0.866025,-0.857167,-0.848048,-0.838671,-0.829038,-0.819152,-0.809017,-0.798636,-0.788011,-0.777146,-0.766044,-0.75471,-0.743145,-0.731354,-0.71934,-0.707107,-0.694658,-0.681998,-0.669131,-0.656059,-0.642788,-0.62932,-0.615661,-0.601815,-0.587785,-0.573576,-0.559193,-0.544639,-0.529919,-0.515038,-0.5,-0.48481,-0.469472,-0.453991,-0.438371,-0.422618,-0.406737,-0.390731,-0.374607,-0.358368,-0.34202,-0.325568,-0.309017,-0.292372,-0.275637,-0.258819,-0.241922,-0.224951,-0.207912,-0.190809,-0.173648,-0.156434,-0.139173,-0.121869,-0.104528,-0.0871557,-0.0697565,-0.052336,-0.0348995,-0.0174524};
float cosine[360] = {1,0.999848,0.999391,0.99863,0.997564,0.996195,0.994522,0.992546,0.990268,0.987688,0.984808,0.981627,0.978148,0.97437,0.970296,0.965926,0.961262,0.956305,0.951057,0.945519,0.939693,0.93358,0.927184,0.920505,0.913545,0.906308,0.898794,0.891007,0.882948,0.87462,0.866025,0.857167,0.848048,0.838671,0.829038,0.819152,0.809017,0.798636,0.788011,0.777146,0.766044,0.75471,0.743145,0.731354,0.71934,0.707107,0.694658,0.681998,0.669131,0.656059,0.642788,0.62932,0.615661,0.601815,0.587785,0.573576,0.559193,0.544639,0.529919,0.515038,0.5,0.48481,0.469472,0.453991,0.438371,0.422618,0.406737,0.390731,0.374607,0.358368,0.34202,0.325568,0.309017,0.292372,0.275637,0.258819,0.241922,0.224951,0.207912,0.190809,0.173648,0.156434,0.139173,0.121869,0.104528,0.0871557,0.0697565,0.052336,0.0348995,0.0174524,1.7949e-09,-0.0174524,-0.0348995,-0.052336,-0.0697565,-0.0871557,-0.104528,-0.121869,-0.139173,-0.156434,-0.173648,-0.190809,-0.207912,-0.224951,-0.241922,-0.258819,-0.275637,-0.292372,-0.309017,-0.325568,-0.34202,-0.358368,-0.374607,-0.390731,-0.406737,-0.422618,-0.438371,-0.45399,-0.469472,-0.48481,-0.5,-0.515038,-0.529919,-0.544639,-0.559193,-0.573576,-0.587785,-0.601815,-0.615661,-0.62932,-0.642788,-0.656059,-0.669131,-0.681998,-0.694658,-0.707107,-0.71934,-0.731354,-0.743145,-0.75471,-0.766044,-0.777146,-0.788011,-0.798636,-0.809017,-0.819152,-0.829038,-0.838671,-0.848048,-0.857167,-0.866025,-0.87462,-0.882948,-0.891007,-0.898794,-0.906308,-0.913545,-0.920505,-0.927184,-0.93358,-0.939693,-0.945519,-0.951057,-0.956305,-0.961262,-0.965926,-0.970296,-0.97437,-0.978148,-0.981627,-0.984808,-0.987688,-0.990268,-0.992546,-0.994522,-0.996195,-0.997564,-0.99863,-0.999391,-0.999848,-1,-0.999848,-0.999391,-0.99863,-0.997564,-0.996195,-0.994522,-0.992546,-0.990268,-0.987688,-0.984808,-0.981627,-0.978148,-0.97437,-0.970296,-0.965926,-0.961262,-0.956305,-0.951057,-0.945519,-0.939693,-0.93358,-0.927184,-0.920505,-0.913545,-0.906308,-0.898794,-0.891007,-0.882948,-0.87462,-0.866025,-0.857167,-0.848048,-0.838671,-0.829038,-0.819152,-0.809017,-0.798636,-0.788011,-0.777146,-0.766044,-0.75471,-0.743145,-0.731354,-0.71934,-0.707107,-0.694658,-0.681998,-0.669131,-0.656059,-0.642788,-0.62932,-0.615661,-0.601815,-0.587785,-0.573576,-0.559193,-0.544639,-0.529919,-0.515038,-0.5,-0.48481,-0.469472,-0.453991,-0.438371,-0.422618,-0.406737,-0.390731,-0.374607,-0.358368,-0.34202,-0.325568,-0.309017,-0.292372,-0.275637,-0.258819,-0.241922,-0.224951,-0.207912,-0.190809,-0.173648,-0.156434,-0.139173,-0.121869,-0.104528,-0.0871557,-0.0697565,-0.052336,-0.0348995,-0.0174524,-5.3847e-09,0.0174524,0.0348995,0.052336,0.0697565,0.0871557,0.104528,0.121869,0.139173,0.156434,0.173648,0.190809,0.207912,0.224951,0.241922,0.258819,0.275637,0.292372,0.309017,0.325568,0.34202,0.358368,0.374607,0.390731,0.406737,0.422618,0.438371,0.45399,0.469472,0.48481,0.5,0.515038,0.529919,0.544639,0.559193,0.573576,0.587785,0.601815,0.615661,0.62932,0.642788,0.656059,0.669131,0.681998,0.694658,0.707107,0.71934,0.731354,0.743145,0.75471,0.766044,0.777146,0.788011,0.798636,0.809017,0.819152,0.829038,0.838671,0.848048,0.857167,0.866025,0.87462,0.882948,0.891007,0.898794,0.906308,0.913545,0.920505,0.927184,0.93358,0.939693,0.945519,0.951057,0.956305,0.961262,0.965926,0.970296,0.97437,0.978148,0.981627,0.984808,0.987688,0.990268,0.992546,0.994522,0.996195,0.997564,0.99863,0.999391,0.999848};
