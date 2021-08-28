#include "main.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor top_left_mtr(14);
pros::Motor top_right_mtr(5, true);
pros::Motor btm_left_mtr(20);
pros::Motor btm_right_mtr(10, true);
pros::Motor Lift_One(2);
pros::Motor Lift_Two(12, true);
pros::Motor Hook(15);
pros::Motor Lift_Hook(13);
int LockStart;


void WaitTillStopLift() {
  int Volts;
  pros::delay(150);
  Volts = Lift_One.get_actual_velocity();
  while(abs(Volts) > 0){
    pros::delay(50);
    Volts = Lift_One.get_actual_velocity();
  }
}
void WaitTillStopDriveBase() {
  int Volts;
  pros::delay(150);
  master.print(0, 0, "PlaceHolder: %i", 1);
  Volts = top_left_mtr.get_actual_velocity();
  while(abs(Volts) > 1){
    pros::delay(50);
    Volts = top_left_mtr.get_actual_velocity();
  }
  master.print(0, 0, "PlaceHolder: %s", "You Did IT :3");
}
void WaitTillStopTail() {
  int Volts;
  pros::delay(150);
  Volts = Hook.get_voltage();
  while(abs(Volts) > 0){
    pros::delay(50);
    Volts = Hook.get_voltage();
  }
}

void DriveFwd(int T1) {
	//Reversing right motors may be necesarry
	top_left_mtr.move_relative((T1 / 12.75) * 1800, 100);
	btm_left_mtr.move_relative((T1 / 12.75) * 1800, 100);
	top_right_mtr.move_relative((T1 / 12.75) * 1800, 100);
	btm_right_mtr.move_relative((T1 / 12.75) * 1800, 100);
  WaitTillStopDriveBase();
}

void DriveFwdSlow(int T1) {
	//Reversing right motors may be necesarry
	top_left_mtr.move_relative((T1 / 12.75) * 1800, 50);
	btm_left_mtr.move_relative((T1 / 12.75) * 1800, 50);
	top_right_mtr.move_relative((T1 / 12.75) * 1800, 50);
	btm_right_mtr.move_relative((T1 / 12.75) * 1800, 50);
  WaitTillStopDriveBase();
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
 WaitTillStopDriveBase();
}

void TurnLeft90(int NT) {
 //Reversing right motors may be necesarry
 top_left_mtr.move_relative(-2137 * NT, 100);
 btm_left_mtr.move_relative(-2137 * NT, 100);
 top_right_mtr.move_relative(2137 * NT, 100);
 btm_right_mtr.move_relative(2137 * NT, 100);
 WaitTillStopDriveBase();
}

void DeployLift() {
  //Lift_One.tare_position();
  //Lift_Two.tare_position();
 //Reversing right motors may be necesarry
 Lift_One.move_relative(-1200, 100);
 Lift_Two.move_relative(-1200, 100);
 WaitTillStopLift();
 //Lift_One.tare_position();
 //Lift_Two.tare_position();
}

void RaiseLift() {
 //Reversing right motors may be necesarry
 Lift_One.move_relative(1000, 100);
 Lift_Two.move_relative(1000, 100);
}

void DeployTail() {
 //Reversing right motors may be necesarry
 Hook.move_relative(-900, 100);
 WaitTillStopTail();
}

void RaiseTail() {
 //Reversing right motors may be necesarry
 Hook.move_relative(800, 100);
}
