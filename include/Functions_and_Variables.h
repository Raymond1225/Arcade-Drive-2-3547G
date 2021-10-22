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
pros::Vision Visions(6);
pros::vision_signature_s_t RING = pros::Vision::signature_from_utility(1, 1311, 2173, 1742, 1981, 3679, 2830, 3, 0);
pros::vision_signature_s_t NGOAL = pros::Vision::signature_from_utility(2, 1121, 3883, 2502, -4275, -3865, -4070, 2.5, 0);
pros::vision_signature_s_t RGOAL = pros::Vision::signature_from_utility(3, 6921, 9167, 8044, -1573, -703, -1138, 3, 0);
pros::vision_signature_s_t BGOAL = pros::Vision::signature_from_utility(4, -2823, -1375, -2099, 5159, 10403, 7781, 2.5, 0);

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

void WaitTillStopLock() {
  int Volts;
  pros::delay(150);
  master.print(0, 0, "PlaceHolder: %i", 1);
  Volts = Lift_Hook.get_actual_velocity();
  while(abs(Volts) > 1){
    pros::delay(50);
    Volts = Lift_Hook.get_actual_velocity();
  }
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
  //LockStart = Lift_Hook.get_position();
  //master.print(0, 0, "Lock: %i", LockStart);
  Lift_Hook.move_relative(-300, 100);
  WaitTillStopLock();
  //Lift_Hook.move_relative(LockStart, 100);
  //WaitTillStopLock();
}

void Lock() {
  Lift_Hook.move_relative(-300, 100);
  WaitTillStopLock();
  Lift_Hook.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void LockReset(int LockStart) {
  Lift_Hook.move_absolute(LockStart, 100);
  WaitTillStopLock();
}

void TurnByDegree(int ND) {
 //Reversing right motors may be necesarry
 top_left_mtr.move_relative(-(((((((2*(13.5*13.5) / (13.5*13.5))) * 3.14) / 12.75) * 1800) / 360) * ND), 100);
 btm_left_mtr.move_relative(-(((((((2*(13.5*13.5) / (13.5*13.5))) * 3.14) / 12.75) * 1800) / 360) * ND), 100);
 top_right_mtr.move_relative((((((((2*(13.5*13.5) / (13.5*13.5))) * 3.14) / 12.75) * 1800) / 360) * ND), 100);
 btm_right_mtr.move_relative((((((((2*(13.5*13.5) / (13.5*13.5))) * 3.14) / 12.75) * 1800) / 360) * ND), 100);
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

void GoalFind() {
  top_left_mtr.move_velocity(-50);
  btm_left_mtr.move_velocity(-50);
  top_right_mtr.move_velocity(50);
  btm_right_mtr.move_velocity(50);
  int Volts;
  Volts = top_left_mtr.get_actual_velocity();
  while(abs(Volts) > 1){
    pros::delay(50);
    Volts = top_left_mtr.get_actual_velocity();
    pros::vision_object_s_t TRG = Visions.get_by_sig(0, 2);
    if (TRG.width > 5){
      top_left_mtr.move_velocity(0);
      btm_left_mtr.move_velocity(0);
      top_right_mtr.move_velocity(0);
      btm_right_mtr.move_velocity(0);
      master.print(0, 0, "PlaceHolder: %i", 1);
    }


    }

//void DriveToGoal() {

}
