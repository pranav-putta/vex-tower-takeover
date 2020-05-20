#ifndef MAIN_H_
  #define MAIN_H_
  #include "main.h"
#endif

#define PORT_DRIVE_LT 1
#define PORT_DRIVE_LB 2
#define PORT_DRIVE_RT 3
#define PORT_DRIVE_RB 4
#define PORT_RAMP_LIFT 5
#define PORT_ARM_LIFT 6
#define PORT_ARM_L 7
#define PORT_ARM_R 8

extern pros::Motor mtr_drive_lt;
extern pros::Motor mtr_drive_lb;
extern pros::Motor mtr_drive_rt;
extern pros::Motor mtr_drive_rb;
extern pros::Motor mtr_ramp_lift;
extern pros::Motor mtr_arm_lift;
extern pros::Motor mtr_intake_left;
extern pros::Motor mtr_intake_right;
