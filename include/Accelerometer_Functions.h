#ifndef ACCELEROMETER_FUNCTIONS_H
#define ACCELEROMETER_FUNCTIONS_H

#include "Adafruit_MPU6050.h"
#include "Adafruit_Sensor.h"
#include <Wire.h>

extern Adafruit_MPU6050 mpu;

void mpu_setup(uint32_t accel_range, uint32_t gyro_range, uint32_t filter_band);
// Initializes and configures MPU6050 on startup
// Accel Settings: 2, 4, 8, 16 [G]
// Gyro Settings: 250, 500, 1000, 2000 [deg/s]
// Filter Settings: 5, 10, 21, 44, 94, 184, 260 [Hz]

void mpu_debug();
float mpu_fetch_a_y();
float mpu_fetch_a_xz_quad();
int8_t mpu_map_a_y(const float min_in, const float max_in, const float min_out,
                   const float max_out);

#endif