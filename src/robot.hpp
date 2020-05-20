#ifndef MAIN_H_
  #define MAIN_H_
  #include "main.h"
#endif

#ifndef MOTORS_H_
  #define MOTORS_H_
  #include "motors.hpp"
#endif

#define PI 3.14159265
#define LIFT_GOAL 0.6283

enum drive_state {Forward = 1, Backward = -1};
enum intake_state {In = 1, Out = -1};
enum arm_state {Low, Mid, High};
enum lift_state {Lifted = -1, Dropped = 1};
enum component {Drive, Arm, Ramp, Intake};

struct control_vars {
  double kP;
  double kI;
  double kD;
  double kV;
  double kA;
};

extern control_vars lift_constants;
extern control_vars intake_constants;
extern control_vars arm_constants;
extern control_vars lift_constants;

struct point {
  double x;
  double y;
  double theta;
};

struct trajectory {

};

// Load preset values
void initialize_components();

// Set value for specified component
void set_component_value(component component, double value);

// set component states
void set_drive_state(drive_state dir, int speed = 50);
void set_intake_state(intake_state state, int speed = 60, bool lock = true);
void set_lift_state(lift_state state, int speed = 60, control_vars lift = lift_constants);
void set_arm_state(arm_state state, int speed = 60, bool lock = true);

// autonomous functions
void drop_off_cubes();
void follow_trajectory(point p1, point p2, control_vars vars);
