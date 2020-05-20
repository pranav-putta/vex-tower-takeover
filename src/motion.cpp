#include "motion.hpp"
using namespace std;

void perform_lift_test() {
  double lift_enc[5];
  double lift_vels[100];
  double lift_accels[20];

  int i = 0;
  int j = 0;
  int k = 0;
  double dt = 10;
  int vel_increments = 5;
  int accel_increments = 2;

  while (j <= 28) {

    lift_enc[i] = -1 * mtr_ramp_lift.get_position();

    // Calculate velocity from previous 4 encoder updates
    if (i % vel_increments == 0 && i != 0) {
      i = 0; // Reset encoder array
      lift_vels[j] = (lift_enc[4] - lift_enc[0]) / (dt * vel_increments);
      j++;
    }

    // Calculate acceleration from previous 2 velocity updates
    if (j % 2 == 0 && j != 0) {
        lift_accels[k] = (lift_vels[j] - 0) / (dt * vel_increments * accel_increments);
    }

    i++;

    // set motor speed to 60 power
    mtr_ramp_lift = 60;

    pros::delay(dt);
  }

  // stop motor
  mtr_ramp_lift = 0;

  // calculate max velocity and acceleration in array
  double max_vel = *std::max_element(lift_vels, lift_vels + j);
  double max_accel = *std::max_element(lift_accels, lift_accels + k);

  // Conversion rate
  max_vel /= 18;
  max_accel /= 18;

  // Display results
  while (true) {
    pros::lcd::print(0, "Distance Travelled: %f", -1 * mtr_ramp_lift.get_position());
    pros::lcd::print(1, "Max Velocity: %f rad/s", max_vel);
    pros::lcd::print(2, "Max Acceleration: %f rad/s^2", max_accel);
    pros::delay(200);
  }
}

void perform_drive_test() {
  double lt[10];
  double lb[10];
  double rt[10];
  double rb[10];
  double vels[4][1000];
  double accels[4][1000];

  int i = 0;
  int j = 0;
  int k = 0;

  double dt = 10; // time delay
  int vel_increments = 5; // velocity cycle rate
  int accel_increments = 2; // acceleration cycle rate

  while (j <= 28) {
    lt[i] = mtr_drive_lt.get_position(); // left top encoder value
    lb[i]= mtr_drive_lb.get_position(); // left bottom encoder value
    rt[i] = mtr_drive_rt.get_position(); // right top encoder value
    rb[i] = mtr_drive_rb.get_position(); // right bottom encoder value

    // Calculate velocity based on previous 5 positions
    if (i % 10 == 0 && i != 0) {
      i = 0;
      vels[0][j] = (lt[9] - lt[0]) / (dt * vel_increments);
      vels[1][j] = (lb[9] - lb[0]) / (dt * vel_increments);
      vels[2][j] = (rt[9] - rt[0]) / (dt * vel_increments);
      vels[3][j] = (rb[9] - rb[0]) / (dt * vel_increments);
      j++;
    }

    // Calculate accceleration based on previous 2 velocities
    if (j % 4 == 0 && j != 0) {
      for (int n = 0; n < 4; n++) {
        accels[n][k] = (vels[n][j] - vels[n][j - 9]) / (dt * vel_increments * accel_increments);
      }
    }

    i++;

    // Set motors to full speed
    mtr_drive_lt = 127;
    mtr_drive_lb = -127;
    mtr_drive_rt = -127;
    mtr_drive_rb = 127;

  }

  // Set motors to 0
  mtr_drive_lt = 0;
  mtr_drive_lb = 0;
  mtr_drive_rt = 0;
  mtr_drive_rb = 0;

  // calculate max velocity and acceleration in array
  double max_vel = *std::max_element(vels[0], vels[0] + j);
  double max_accel = *std::max_element(accels[0], accels[0] + k);

  // Conversion rate
  max_vel /= 18;
  max_accel /= 18;

  // Display results
  while (true) {
    pros::lcd::print(0, "Distance Travelled: %f", -1 * mtr_ramp_lift.get_position());
    pros::lcd::print(1, "Max Velocity: %f m/s", max_vel);
    pros::lcd::print(2, "Max Acceleration: %f m/s^2", max_accel);
    pros::delay(200);
  }
}
