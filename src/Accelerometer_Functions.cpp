#include "Accelerometer_Functions.h"

// Accelerometer instantiation
Adafruit_MPU6050 mpu;

void mpu_setup(uint32_t accel_range, uint32_t gyro_range,
               uint32_t filter_band) {
  // Initializes and configures MPU6050 on startup
  // Accel Settings: 2, 4, 8, 16 [G]
  // Gyro Settings: 250, 500, 1000, 2000 [deg/s]
  // Filter Settings: 5, 10, 21, 44, 94, 184, 260 [Hz]

  if (mpu.begin()) {
    Serial.println("MPU6050 Initialized");

    // configure device settings
    switch (accel_range) {
    case 2:
      mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
      break;
    case 4:
      mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
      break;
    case 8:
      mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
      break;
    case 16:
      mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
      break;
    }
    switch (gyro_range) {
    case 250:
      mpu.setGyroRange(MPU6050_RANGE_250_DEG);
      break;
    case 500:
      mpu.setGyroRange(MPU6050_RANGE_500_DEG);
      break;
    case 1000:
      mpu.setGyroRange(MPU6050_RANGE_1000_DEG);
      break;
    case 2000:
      mpu.setGyroRange(MPU6050_RANGE_2000_DEG);
      break;
    }
    switch (filter_band) {
    case 5:
      mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
      break;
    case 10:
      mpu.setFilterBandwidth(MPU6050_BAND_10_HZ);
      break;
    case 21:
      mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
      break;
    case 44:
      mpu.setFilterBandwidth(MPU6050_BAND_44_HZ);
      break;
    case 94:
      mpu.setFilterBandwidth(MPU6050_BAND_94_HZ);
      break;
    case 184:
      mpu.setFilterBandwidth(MPU6050_BAND_184_HZ);
      break;
    case 260:
      mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);
      break;
    }

    // Report settings to monitor
    Serial.print("Accelerometer range set to: ");
    switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+/-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+/-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+/-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+/-16G");
      break;
    }
    Serial.print("Gyro range set to: ");
    switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+/- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+/- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+/- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+/- 2000 deg/s");
      break;
    }
    Serial.print("Filter bandwidth set to: ");
    switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
    }
  } else {
    Serial.println("MPU was not able to initialize");
  }
}
// END OF  mpu_setup()
/////////////////////////////////////////////////////////

void mpu_debug() {
  // Prints out sensor reading data to the console for debugging
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  // Print sensor readings out to console
  Serial.printf("ACCEL: <%4.1f, %4.1f, %4.1f> (m/s^2)  ", a.acceleration.x,
                a.acceleration.y, a.acceleration.z);
  Serial.printf("GYRO: <%4.1f, %4.1f, %4.1f> (rad/s)  ", g.gyro.x, g.gyro.y,
                g.gyro.z);
  Serial.printf("TEMP: %4.1f (degC) \n", temp.temperature);
}
// END OF mpu_debug()
/////////////////////////////////////////////////////////

float mpu_fetch_a_y() {
  // returns the y axis accelerometer reading
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  return a.acceleration.y;
}
// END OF mpu_fetch_a_y()
/////////////////////////////////////////////////////////

float mpu_fetch_a_xz_quad() {
  // returns the x and z axis accelerometer readings added in quadrature
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float x = a.acceleration.x;
  float z = a.acceleration.z;
  // add x and z in quadrature for return value
  float xz_quadrature_sum = sqrt(pow(x, 2) + pow(z, 2));

  // println for debug
  // Serial.println(xz_quadrature_sum);

  return xz_quadrature_sum;
}
// END OF mpu_fetch_axz_quad()
/////////////////////////////////////////////////////////

int8_t mpu_map_a_y(const float min_in, const float max_in, const float min_out,
                   const float max_out) {
  // maps the float output of the accelerometer to an 8bit int because the
  // built-in function doesn't seem to work reliably

  // grabs a recent accelerometer reading
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  float a_val = a.acceleration.y;

  // relates the accelerometer reading to the specified range
  float output_val = (a_val - min_in) * (max_out / max_in);
  if (output_val > max_out) {
    output_val = max_out;
  } else if (output_val < min_out) {
    output_val = min_out;
  }
  return int8_t(output_val);
}
// END OF mpu_map_a_y()
/////////////////////////////////////////////////////////
