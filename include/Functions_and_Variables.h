#include "main.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor top_left_mtr(11);
pros::Motor top_right_mtr(5, true);
pros::Motor btm_left_mtr(20);
pros::Motor btm_right_mtr(10, true);
pros::Motor Lift_One(2);
pros::Motor Lift_Two(12, true);
pros::Motor Hook(15);
pros::Motor Lift_Hook(13);
int LockStart;


void DriveFwd(int T1) {
	//Reversing right motors may be necesarry
	top_left_mtr.move_relative((T1 / 17.72) * 1800, 100);
	btm_left_mtr.move_relative((T1 / 17.72) * 1800, 100);
	top_right_mtr.move_relative((T1 / 17.72) * 1800, 100);
	btm_right_mtr.move_relative((T1 / 17.72) * 1800, 100);
}

void DriveFwdSlow(int T1) {
	//Reversing right motors may be necesarry
	top_left_mtr.move_relative((T1 / 17.72) * 1800, 50);
	btm_left_mtr.move_relative((T1 / 17.72) * 1800, 50);
	top_right_mtr.move_relative((T1 / 17.72) * 1800, 50);
	btm_right_mtr.move_relative((T1 / 17.72) * 1800, 50);
}

void LockFullYeet() {
  Lift_Hook.move_relative(500, 100);
}

void Lock() {
  Lift_Hook.move_relative(500, 100);
  Lift_Hook.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void LockReset() {
  Lift_Hook.move_relative(LockStart, 100);
}

void TurnRight90(int NT) {
 //Reversing right motors may be necesarry
 top_left_mtr.move_relative(2137 * NT, 100);
 btm_left_mtr.move_relative(2137 * NT, 100);
 top_right_mtr.move_relative(-2137 * NT, 100);
 btm_right_mtr.move_relative(-2137 * NT, 100);
}

void TurnLeft90(int NT) {
 //Reversing right motors may be necesarry
 top_left_mtr.move_relative(-2137 * NT, 100);
 btm_left_mtr.move_relative(-2137 * NT, 100);
 top_right_mtr.move_relative(2137 * NT, 100);
 btm_right_mtr.move_relative(2137 * NT, 100);
}

void DeployLift() {
 //Reversing right motors may be necesarry
 Lift_One.move_relative(-900, 100);
 Lift_One.move_relative(-900, 100);
}

void RaiseLift() {
 //Reversing right motors may be necesarry
 Lift_One.move_relative(800, 100);
 Lift_One.move_relative(800, 100);
}

void DeployTail() {
 //Reversing right motors may be necesarry
 Hook.move_relative(-900, 100);
}

void RaiseTail() {
 //Reversing right motors may be necesarry
 Hook.move_relative(800, 100);
}
