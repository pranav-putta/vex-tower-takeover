#include "robot.hpp"
using namespace std;

// initialize vars
control_vars lift_constants {20, 0, 0, -1, -1};

bool initialized = false;

/**
 * Load all necessary components
 */
void initialize_components() {
  if (!initialized) {
  //  mtr_ramp_lift.set_encoder_units(MOTOR_ENCODER_ROTATIONS);

    initialized = true;
  }
}

/**
 * Sets motor value for component
 * @param comp  [component enum]
 * @param value [-127 to 127]
 */
void set_component_value(component comp, double value) {

}


/**
 * Sets the drive speed for left and right drive
 * @param dir   [which side of the drive train to run]
 * @param speed [desired rotation speed]
 */
void set_drive_state(drive_state dir, int speed) {
    mtr_drive_lt = speed * dir;
    mtr_drive_lb = -speed * dir;
    mtr_drive_rt = speed * dir;
    mtr_drive_rb = -speed * dir;
}


/**
 * Run the intake
 * @param dir   [desired direction]
 * @param speed [speed value]
 */
void set_intake_state(intake_state state, int speed) {
    mtr_intake_left = speed * state;
    mtr_intake_right = -speed * state;
}

/**
 * Set lift state to desired state
 * @param state [lift_state sub]
 * @param speed [speed, default 60]
 */
void set_lift_state(lift_state state, int speed, control_vars pid) {
  // pid control
  initialize_components();
  double current_position = mtr_ramp_lift.get_position() / (18 * 2 * PI);
  double current_error = LIFT_GOAL - current_position;
  double error_arr[1000];
  double dt = 10;
  double deriv_err = 0;
  double integral_err = 0;
  for (int i = 0; current_error < 0.08726; i++) {
    error_arr[i] = current_error;
    if (i >= 9) {
      deriv_err = (error_arr[i] - error_arr[i - 9]) / (dt * 10);
      integral_err += (error_arr[i] * dt);
    }

    mtr_ramp_lift = state * ((pid.kP * current_error) + (pid.kI * integral_err) + (pid.kD * deriv_err));
    pros::delay(dt);
  }
}

/**
 * Set arm state to desired state
 * @param state [desired arm_state sub]
 * @param speed [speed, default 60]
 * @param lock  [lock motors]
 */
void set_arm_state(arm_state state, int speed, bool lock) {

}

// Drop off cubes
void drop_off_cubes() {
}

// follow trjectory
void follow_trajectory(point p1, point p2, int preset_id, component component, control_vars vars) {
  initialize_components();
}
