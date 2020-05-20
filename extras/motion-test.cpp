void test() {
  pros::Controller master(pros::E_CONTROLLER_MASTER);
  pros::Motor left_mtr_t(1);
  pros::Motor left_mtr_b(2);
  pros::Motor right_mtr_t(3);
  pros::Motor right_mtr_b(4);
  pros::Motor lift_mtr(11);

  double lt[10];
  double lb[10];
  double rt[10];
  double rb[10];
  double vels[4][1000];
  double accels[4][1000];

  double lift_enc[5];
  double lift_vels[100];
  double lift_accels[20];

  int i = 0;
  int j = 0;
  int k = 0;

  int f = -1;

for (int b = 0; b < 2; b++) {
  i = 0;
  j = 0;
  k = 0;

  for (int n = 0; n < 100; n++) {
    lift_vels[n] = 0;
  }

  for (int n = 0; n < 20; n++) {
    lift_accels[n] = 0;
  }

  while (j <= 28) {
    /*lt[i] = left_mtr_t.get_position();
    lb[i]= left_mtr_b.get_position();
    rt[i] = right_mtr_t.get_position();
    rb[i] = right_mtr_b.get_position();


    if (i % 10 == 0 && i != 0) {
      i = 0;
      vels[0][j] = (lt[9] - lt[0]) / 200.0;
      vels[1][j] = (lb[9] - lb[0]) / 200.0;
      vels[2][j] = (rt[9] - rt[0]) / 200.0;
      vels[3][j] = (rb[9] - rb[0]) / 200.0;
      j++;
    }

    if (j % 4 == 0 && j != 0) {
      for (int n = 0; n < 4; n++) {
        accels[n][k] = (vels[n][j] - vels[n][j - 9]) / 800.0;
      }
    }

    i++;

    left_mtr_t = 127;
    left_mtr_b = -127;
    right_mtr_t = -127;
    right_mtr_b = 127;*/


    lift_enc[i] = -1 * lift_mtr.get_position();

    if (i % 4 == 0 && i != 0) {
      i = 0;
      lift_vels[j] = (lift_enc[4] - lift_enc[0]) / (20.0 * 5);
      j++;
    }

    if (j % 2 == 0 && j != 0) {
        lift_accels[k] = (lift_vels[j] - 0) / (400.0);
    }

    i++;
    lift_mtr = 60* f;

    pros::delay(20);
  }

  lift_mtr = 0;
  double max_vel = 0;
  for (int n = 0; n < j; n++) {
    if (lift_vels[n] > max_vel) {
      max_vel = lift_vels[n];
    }
  }
  double max_accel = 0;
  for (int n = 0; n <= k; n++) {
    if (lift_accels[n] > max_accel) {
      max_accel = lift_accels[n];
    }
  }


  max_vel /= 18;
  max_accel /= 18;
    f = 1;
    pros::lcd::print(0, "Max Velocity: %f", max_vel);
    pros::lcd::print(1, "Max Acceleration: %f", max_accel);
    pros::delay(4000);
  }


}
