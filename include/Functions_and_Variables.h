#include "main.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor top_left_mtr(14);
pros::Motor top_right_mtr(5, true);
pros::Motor btm_left_mtr(20);
pros::Motor btm_right_mtr(10, true);
pros::Motor Lift_One(2);
pros::Motor Lift_Two(12, true);
pros::Motor Hook(15);
pros::ADIDigitalOut Lift_Hook (1);
pros::ADIDigitalOut Tail_Scraper1 (2);
pros::ADIDigitalOut Tail_Scraper2 (3);
pros::Vision Visions(6);
pros::Motor Intake(7);
pros::vision_object_s_t TRG;
pros::ADIDigitalIn button(4);
int MotorHold = 0;

void SetSigs () {
  pros::vision_signature_s_t BGOAL = pros::Vision::signature_from_utility(1, -2473, -1709, -2092, 6949, 8435, 7692, 4.900, 1);
  pros::vision_signature_s_t NGOAL = pros::Vision::signature_from_utility(2, 1649, 2385, 2018, -3831, -3195, -3512, 3.000, 0);
  pros::vision_signature_s_t RGOAL = pros::Vision::signature_from_utility(3, 6903, 8369, 7636, -2319, -813, -1566, 3.400, 1);
  Visions.set_signature(1, &BGOAL);
  Visions.set_signature(2, &NGOAL);
  Visions.set_signature(3, &RGOAL);
}

void VisTest() {
  pros::vision_object_s_t NRG;
  pros::vision_object_s_t BRG;
  pros::vision_object_s_t VRG;
  while(true){
    if(Visions.get_object_count() > 0){
      pros::delay(200);
      NRG = Visions.get_by_sig(0, 3);
      VRG = Visions.get_by_sig(0,2);
      BRG = Visions.get_by_sig(0, 1);
      master.clear();
      master.print(0, 0, "BGOAL: %i", VRG.width);
      master.print(1, 0, "NGOAL: %i", BRG.width);
      master.print(2, 0, "RGOAL: %i", NRG.width);
    }
  }
}

void WaitTillStopLift() {
  int Volts;
  pros::delay(150);
  Volts = Lift_One.get_actual_velocity();
  while(abs(Volts) > 0){
    pros::delay(10);
    Volts = Lift_One.get_actual_velocity();
  }
}
void WaitTillStopDriveBase() {
  int Volts;
  pros::delay(150);
  master.print(0, 0, "PlaceHolder: %i", 1);
  Volts = top_left_mtr.get_actual_velocity();
  while(abs(Volts) > 1){
    pros::delay(10);
    Volts = top_left_mtr.get_actual_velocity();
  }


  master.print(0, 0, "PlaceHolder: %s", "You Did IT :3");
}

void WaitTillStopDriveBaseR() {
  int Volts;
  pros::delay(150);
  master.print(0, 0, "PlaceHolder: %i", 1);
  Volts = top_right_mtr.get_actual_velocity();
  while(abs(Volts) > 1){
    pros::delay(10);
    Volts = top_right_mtr.get_actual_velocity();
  }
}
/*
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
*/
void WaitTillStopTail() {
  int Volts;
  int timer = 0;
  pros::delay(150);
  Volts = Hook.get_actual_velocity();
  while(abs(Volts) > 10){
    pros::delay(100);
    Volts = Hook.get_actual_velocity();
    timer ++;
    if (timer == 10){
      Volts = 0;
    }
  }
}

void LockClaw () {
  Lift_Hook.set_value(false);
}

void RetractClaw () {
  Lift_Hook.set_value(true);
}

void TailScrape () {
  Tail_Scraper1.set_value(true);
  Tail_Scraper2.set_value(true);
}

void RetractScraper () {
  Tail_Scraper1.set_value(false);
  Tail_Scraper2.set_value(false);
}

void DriveFwd(float T1) {
	//Reversing right motors may be necesarry
	top_left_mtr.move_relative((T1 / 12.75) * 1800, 130);
	btm_left_mtr.move_relative((T1 / 12.75) * 1800, 130);
	top_right_mtr.move_relative((T1 / 12.75) * 1800, 130);
	btm_right_mtr.move_relative((T1 / 12.75) * 1800, 130);
  WaitTillStopDriveBase();
}

void RaiseTail() {
 //Reversing right motors may be necesarry
 Hook.move_relative(1200, 100);
 WaitTillStopTail();
}

void DriveFwdFindGoal() {
  int MotorAfter = 0;
	//Reversing right motors may be necesarry
  //MotorHold = top_left_mtr.get_position();
	while(!button.get_value()){
    top_left_mtr.move_velocity(200);
    top_right_mtr.move_velocity(200);
    btm_left_mtr.move_velocity(200);
    btm_right_mtr.move_velocity(200);
  }
  //MotorAfter = top_left_mtr.get_position();
  //int MotorDrive = MotorHold - MotorAfter;
  pros::delay(100);
  Lift_Hook.set_value(false);
  top_left_mtr.move_velocity(0);
  top_right_mtr.move_velocity(0);
  btm_left_mtr.move_velocity(0);
  btm_right_mtr.move_velocity(0);
  //top_left_mtr.move_relative(MotorDrive, 200);
  //btm_left_mtr.move_relative(MotorDrive, 200);
  //top_right_mtr.move_relative(MotorDrive, 200);
  //btm_right_mtr.move_relative(MotorDrive, 200);
}

void DeployDriveFwd(int T1) {
	//Reversing right motors may be necesarry
	top_left_mtr.move_relative((T1 / 12.75) * 1800, 130);
	btm_left_mtr.move_relative((T1 / 12.75) * 1800, 130);
	top_right_mtr.move_relative((T1 / 12.75) * 1800, 130);
	btm_right_mtr.move_relative((T1 / 12.75) * 1800, 130);
  Lift_One.move_relative(-4350, 100);
  Lift_Two.move_relative(-4350, 100);
  WaitTillStopDriveBase();
  WaitTillStopLift();
}

void DriveFwdSPED(float T1) {
	//Reversing right motors may be necesarry
	top_left_mtr.move_relative((T1 / 12.75) * 1800, 200);
	btm_left_mtr.move_relative((T1 / 12.75) * 1800, 200);
	top_right_mtr.move_relative((T1 / 12.75) * 1800, 200);
	btm_right_mtr.move_relative((T1 / 12.75) * 1800, 200);
  WaitTillStopDriveBase();
}


void YoinkProtocal(float T1) {
	//Reversing right motors may be necesarry
  RetractClaw();
	top_left_mtr.move_relative((T1 / 12.75) * 1800, 200);
	btm_left_mtr.move_relative((T1 / 12.75) * 1800, 200);
	top_right_mtr.move_relative((T1 / 12.75) * 1800, 200);
	btm_right_mtr.move_relative((T1 / 12.75) * 1800, 200);
  Lift_One.move_relative(-4350, 200);
  Lift_Two.move_relative(-4350, 200);
  Hook.move_relative(-2075, 100);
  WaitTillStopLift();
  WaitTillStopDriveBase();
  DriveFwdFindGoal();
  DriveFwdSPED(-900);
  WaitTillStopDriveBase();
  WaitTillStopTail();
}

void DriveFwdDeployAll(int T1) {
  top_left_mtr.move_relative((T1 / 12.75) * 1800, 200);
  btm_left_mtr.move_relative((T1 / 12.75) * 1800, 200);
  top_right_mtr.move_relative((T1 / 12.75) * 1800, 200);
  btm_right_mtr.move_relative((T1 / 12.75) * 1800, 200);
  Lift_One.move_relative(-4350, 100);
  Lift_Two.move_relative(-4350, 100);
  Hook.move_relative(-2075, 100);
  WaitTillStopTail();
  WaitTillStopDriveBase();
  //WaitTillStopLift();
}

void DriveFwdSlow(int T1) {
	//Reversing right motors may be necesarry
	top_left_mtr.move_relative((T1 / 12.75) * 1800, 50);
	btm_left_mtr.move_relative((T1 / 12.75) * 1800, 50);
	top_right_mtr.move_relative((T1 / 12.75) * 1800, 50);
	btm_right_mtr.move_relative((T1 / 12.75) * 1800, 50);
  WaitTillStopDriveBase();
}

void DriveFwdSwerve(int T1) {
	//Reversing right motors may be necesarry
	top_left_mtr.move_relative((T1 / 12.75) * 1800, 60);
	btm_left_mtr.move_relative((T1 / 12.75) * 1800, 60);
	top_right_mtr.move_relative((T1 / 12.75) * 1800, 120);
	btm_right_mtr.move_relative((T1 / 12.75) * 1800, 120);
  WaitTillStopDriveBase();
}

void DriveFwdARC(int T1) {
	//Reversing right motors may be necesarry
	top_left_mtr.move_relative((T1 / 12.75) * 1800, 120);
	btm_left_mtr.move_relative((T1 / 12.75) * 1800, 120);
//	top_right_mtr.move_relative((T1 / 12.75) * 900 * .5, 60);
//	btm_right_mtr.move_relative((T1 / 12.75) * 900 * .5, 60);
  WaitTillStopDriveBase();
}

void DriveFwdARCR(float T1) {
	//Reversing right motors may be necesarry
	top_right_mtr.move_relative((T1 / 12.75) * 1800, 200);
	btm_right_mtr.move_relative((T1 / 12.75) * 1800, 200);
	top_left_mtr.move_relative((T1 / 12.75) * 1800 * .5, 60);
	btm_left_mtr.move_relative((T1 / 12.75) * 1800 * .5, 60);
  WaitTillStopDriveBaseR();
}

void DriveFwdARCRR(int T1) {
	//Reversing right motors may be necesarry
	top_right_mtr.move_relative((T1 / 12.75) * 1800, 120);
	btm_right_mtr.move_relative((T1 / 12.75) * 1800, 120);
	top_left_mtr.move_relative((T1 / 12.75) * 1800 * .15, 60);
	btm_left_mtr.move_relative((T1 / 12.75) * 1800 * .15, 60);
  WaitTillStopDriveBaseR();
}
/*
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
*/
void TurnByDegree(int ND) {
 //Positive CCW Negative CW
 top_left_mtr.move_relative(-((((47.122 / 12.75) * 1800) / 360) * ND), 100);
 btm_left_mtr.move_relative(-((((47.122 / 12.75) * 1800) / 360) * ND), 100);
 top_right_mtr.move_relative(((((47.122 / 12.75) * 1800) / 360) * ND), 100);
 btm_right_mtr.move_relative(((((47.122 / 12.75) * 1800) / 360) * ND), 100);
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
 Lift_One.move_relative(-4350, 100);
 Lift_Two.move_relative(-4350, 100);
 WaitTillStopLift();
 //Lift_One.tare_position();
 //Lift_Two.tare_position();
}

void RaiseLift() {
 //Reversing right motors may be necesarry
 Lift_One.move_relative(1200, 100);
 Lift_Two.move_relative(1200, 100);
}

void LowerLift() {
 //Reversing right motors may be necesarry
 Lift_One.move_relative(-1200, 100);
 Lift_Two.move_relative(-1200, 100);
}
void DeployTail() {
 //Reversing right motors may be necesarry
 Hook.move_relative(-2000, 100);
WaitTillStopTail();
}

void LowerTail() {
 //Reversing right motors may be necesarry
 Hook.move_relative(-1200, 100);
 WaitTillStopTail();
}

void DepoRings(){
Lift_One.move_relative(-550, 100);
Lift_Two.move_relative(-550, 100);
}

void GoalFind() {
  top_left_mtr.move_velocity(-50);
  btm_left_mtr.move_velocity(-50);
  top_right_mtr.move_velocity(50);
  btm_right_mtr.move_velocity(50);
  int Volts;
  pros::delay(50);
  Volts = top_left_mtr.get_actual_velocity();
  while(abs(Volts) > 1){
    pros::delay(50);
    Volts = top_left_mtr.get_actual_velocity();
    TRG = Visions.get_by_sig(0, 2);
    master.clear();
    master.print(0, 0, "PlaceHolder: %i", TRG.width);
    if (TRG.width > 50){
      top_left_mtr.move_velocity(0);
      btm_left_mtr.move_velocity(0);
      top_right_mtr.move_velocity(0);
      btm_right_mtr.move_velocity(0);
    }
    }
    }

void DriveToGoal() {
  while (TRG.width < 150){
  top_left_mtr.move_velocity(70);
  btm_left_mtr.move_velocity(70);
  top_right_mtr.move_velocity(70);
  btm_right_mtr.move_velocity(70);
  if (TRG.x_middle_coord > 0) {
  top_left_mtr.move_velocity(50);
  btm_left_mtr.move_velocity(50);
  top_right_mtr.move_velocity(70);
  btm_right_mtr.move_velocity(70);
  }
  if (TRG.x_middle_coord < 0) {
  top_left_mtr.move_velocity(70);
  btm_left_mtr.move_velocity(70);
  top_right_mtr.move_velocity(50);
  btm_right_mtr.move_velocity(50);
  }
}
top_left_mtr.move_velocity(0);
btm_left_mtr.move_velocity(0);
top_right_mtr.move_velocity(0);
btm_right_mtr.move_velocity(0);
WaitTillStopDriveBase();
}
