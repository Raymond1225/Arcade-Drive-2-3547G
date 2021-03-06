#include "main.h"
#include "Functions_and_Variables.h"
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

 int autonselect = 7;



void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "Skills");
    autonselect = 5;
	} else {
		pros::lcd::clear_line(2);
	}
}

void on_button_1() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "Ramp Side");
    autonselect = 8;
	} else {
		pros::lcd::clear_line(2);
	}
}
void on_button_2() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "AWP Line");
    autonselect = 7;
	} else {
		pros::lcd::clear_line(2);
	}
}
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  Visions.set_zero_point(pros::E_VISION_ZERO_CENTER);
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn0_cb(on_center_button);
  pros::lcd::register_btn1_cb(on_button_1);
  pros::lcd::register_btn2_cb(on_button_2);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  Visions.set_zero_point(pros::E_VISION_ZERO_CENTER);
  pros::Controller master(pros::E_CONTROLLER_MASTER);
  pros::Motor top_left_mtr(11);
  pros::Motor top_right_mtr(5, true);
  pros::Motor btm_left_mtr(20);
  pros::Motor btm_right_mtr(10, true);
  pros::Motor Lift_One(2);
  pros::Motor Lift_Two(12, true);
  pros::Motor Hook(15);
  pros::Motor Lift_Hook(13);
  int LockStart = Lift_Hook.get_position();
  int Count = 0;

if (autonselect == 0){
  //Start Red right
  Lift_Hook.move_velocity(-1);
  DeployLift();
  DriveFwd(12);
//  Lock();
  RaiseLift();
  DriveFwdSPED(60);
  DeployLift();
//  LockReset(LockStart);
  DriveFwdARC(-20);
  //end of red start of right yellow
  TurnByDegree(90);
  DriveFwdSPED(14);
//  Lock();
  RaiseLift();
  TurnByDegree(-90);
  DriveFwd(14);
  DeployLift();
//  LockReset(LockStart);
  DriveFwd(-14);
  //end of right yellow start of middle yellow
  TurnByDegree(90);
  DriveFwdSPED(32);
//  Lock();
  RaiseLift();
  TurnByDegree(-90);
  DriveFwd(14);
  DeployLift();
//  LockReset(LockStart);
  DriveFwd(-14);
  //end of middle yellow start of left yellow
  TurnByDegree(90);
  DriveFwdSPED(34);
//  Lock();
  RaiseLift();
  TurnByDegree(-90);
  DriveFwd(14);
  DeployLift();
//  LockReset(LockStart);
  DriveFwd(-14);
  //end of left yellow start of blue
  TurnByDegree(90);
  RaiseLift();
  DriveFwd(28);
  TurnByDegree(-90);
  DeployLift();
  DriveFwdSPED(34);
//  Lock();
  RaiseLift();
  DriveFwdSPED(-88);
  //stops after two goals currently
}
else if (autonselect == 1){
  DriveFwdSlow(12);
//  LockFullYeet();
  DriveFwd(-12);
//  LockReset(LockStart);
}
else if (autonselect == 2){
  DriveFwdSlow(12);
  //LockFullYeet();
  DriveFwd(-12);
  //LockReset(LockStart);
  Lift_Hook.move_velocity(-1);
  DeployLift();
  DriveFwd(12);
  //Lock();
  RaiseLift();
  DriveFwd(-12);
}
else if (autonselect == 3){
  TurnByDegree(90);
  //SetSigs();
  //VisTest();
  //GoalFind();
  //DriveToGoal();
}

else if (autonselect == 4){
  //pick up AWP line goal
  RetractClaw();
  DeployDriveFwd(14);
  DriveFwdFindGoal();
  DriveFwdSPED(-36);
  /*
  TurnByDegree(90);
  DriveFwd(12);
  TurnLeft90(90);
  DriveFwdSPED(24);
  LockClaw();
  RaiseLift();
  DriveFwdSPED(-24);
  */
}

else if (autonselect == 5){
  //red side goal on ramp
  //DeployTail();
//  DeployDriveFwd(-36);
  //yellow goal 1
//  DriveFwdARCR(12);
  RetractClaw();
  DeployDriveFwd(36);
  DriveFwdSPED(-27);
  TurnByDegree(-47);
  DriveFwdFindGoal();
  DriveFwdARCR(-10);
  DriveFwdSPED(-60);
  Lift_Two.move_relative(100, 100);
  Lift_One.move_relative(100, 100);
}

else if (autonselect == 6){
  RetractClaw();
  DriveFwdFindGoal();
}

else if (autonselect == 7){
  YoinkProtocal(22.6);
  /*
  YoinkProtocal(-22.6);
  RaiseLift();
  TurnByDegree(49);
  DriveFwd(13);
  DriveFwd(-2.5);
  DepoRings();
  DriveFwd(-5);
  Lift_One.move_relative(-650, 100);
  Lift_Two.move_relative(-650, 100);
  WaitTillStopLift();
  RetractClaw();
  DriveFwdFindGoal();
  DriveFwd(-10);
  */
}

else if (autonselect == 8){
  DriveFwdDeployAll(-12);
  top_right_mtr.move_relative((-.5 / 12.75) * 3600, 100);
  btm_right_mtr.move_relative((-.5 / 12.75) * 3600, 100);
  top_left_mtr.move_relative((-.5 / 12.75) * 3600 * .5, 30);
  btm_left_mtr.move_relative((-.5 / 12.75) * 3600 * .5, 30);
  WaitTillStopDriveBaseR();
  DriveFwdARCR(-3.45);
  DriveFwdSPED(-9.1);
  RaiseTail();
  pros::delay(100);
  WaitTillStopLift();
  DriveFwdSPED(10);
  RaiseLift();
  TurnByDegree(28);
  DriveFwd(15);
  DriveFwd(-3);
  DepoRings();
  DriveFwd(-5);
  Lift_One.move_relative(-650, 100);
  Lift_Two.move_relative(-650, 100);
  WaitTillStopLift();
}
	/**
	field wall to middle line: 71in
	Lift to back: 23in
	Lift to center: 12in
	Center to back: 11in
	wheels go 17.72in per revolution
	diameter of circle wheels travel on in 19in
	circumference of said circle is 59.69in
	90 degree turn = 2,137ticks


	Order of Auton for Fair competition.
	1. Lower lift and drive to first goal.
	2. Drive forward another 12in to center ourselves on the middle line.
	3. turn 90 degrees to the right to line with with center goal.
	4. Back up and lower tail till we are at center goal.
	5. Pick up center and turn 90 degrees right.
	6. Drive forward to score 40 points.
	*/
}




/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
 void opcontrol() {
 	pros::Controller master(pros::E_CONTROLLER_MASTER);
 	pros::Motor top_left_mtr(14);
 	pros::Motor top_right_mtr(5, true);
 	pros::Motor btm_left_mtr(20);
 	pros::Motor btm_right_mtr(10, true);
 	pros::Motor Lift_One(2);
 	pros::Motor Lift_Two(12, true);
	pros::Motor Hook(15);
  pros::ADIDigitalOut Lift_Hook(1);
	int hold;
	int timer = 1;
	int hold_Tail;
  int DriverSelect = 1;
  int IntakeToggle = 0;
  int LiftSpeed = 100;
  //master.print(0, 0, "PlaceHolder: %i", autonselect);
  int test = -3;
  master.clear();
  master.print(0, 0, "PlaceHolder: %i", abs(test));
  master.print(1, 0, "Lift Speed: %i", LiftSpeed);

 	while (true) {
    int left = master.get_analog(ANALOG_LEFT_Y);
    int right = master.get_analog(ANALOG_RIGHT_Y);
    int leftx = master.get_analog(ANALOG_LEFT_X);
    int rightx = master.get_analog(ANALOG_RIGHT_X);






		/*Check left joystick for turn input*/
    if(DriverSelect == 1) {
      btm_left_mtr.move_velocity(left*(200/127));
      btm_right_mtr.move_velocity(right*(200/127));
      top_left_mtr.move_velocity(left*(200/127));
      top_right_mtr.move_velocity(right*(200/127));

      if (timer == 1){
  			hold = Lift_One.get_position();
  			hold_Tail = Hook.get_position();

  			timer --;
  		}

      if(master.get_digital(DIGITAL_UP)){
        LiftSpeed = 200;
      }
      else if(master.get_digital(DIGITAL_DOWN)){
        LiftSpeed = 100;
      }

  			if(master.get_digital(DIGITAL_L1) == 1){
  				Lift_One.move_velocity(LiftSpeed);
  	 			Lift_Two.move_velocity(LiftSpeed);
  				hold = Lift_One.get_position();
  			}
  			else if(master.get_digital(DIGITAL_L2) == 1){
  				Lift_One.move_velocity(-LiftSpeed);
  	 			Lift_Two.move_velocity(-LiftSpeed);
  				hold = Lift_One.get_position();
  			}

        /*
  	  	else if (Lift_One.get_position() < (hold - 5)){
  				Lift_One.move_velocity(1);
  				Lift_Two.move_velocity(1);
  	  	}
        */
  			else {
          Lift_One.move_velocity(0);
  	 			Lift_Two.move_velocity(0);
  				Lift_One.set_brake_mode(MOTOR_BRAKE_HOLD);;
  				Lift_Two.set_brake_mode(MOTOR_BRAKE_HOLD);;
  			}




  			if (master.get_digital(DIGITAL_A)){
  				Hook.move_velocity(100);
  				hold_Tail = Hook.get_position();
  			}
  			else if (master.get_digital(DIGITAL_B)){
  				Hook.move_velocity(-100);
  				hold_Tail = Hook.get_position();
  			}
        /*
  			else if (Hook.get_position() < (hold_Tail - 5)){
  				Hook.move_velocity(1);
  			}
        */
  			else {
          Hook.move_velocity(0);
  				Hook.set_brake_mode(MOTOR_BRAKE_HOLD);
  			}

        if (master.get_digital(DIGITAL_R1)){
          Lift_Hook.set_value(false);
        }
        else if (master.get_digital(DIGITAL_R2)){
          Lift_Hook.set_value(true);
        }
        /*else {
          Lift_Hook.move_velocity(0);
          Lift_Hook.set_brake_mode(MOTOR_BRAKE_HOLD);
        }
        */



        if (master.get_digital(DIGITAL_X)){
          Tail_Scraper1.set_value(true);
          Tail_Scraper2.set_value(true);
        }

        if (master.get_digital(DIGITAL_Y)){
          Tail_Scraper1.set_value(false);
          Tail_Scraper2.set_value(false);
    }
/*
    else if(DriverSelect == 2) {
      top_left_mtr = left;
      btm_left_mtr = left;
      top_right_mtr = left;
      btm_right_mtr = left;

      if (rightx > 5){
        top_left_mtr = rightx;
        btm_left_mtr = rightx;
        top_right_mtr = -rightx;
        btm_right_mtr = -rightx;
      }

      else if (rightx < 5){
        top_left_mtr = -rightx;
        btm_left_mtr = -rightx;
        top_right_mtr = rightx;
        btm_right_mtr = rightx;
      }

      if (timer == 1){
        hold = Lift_One.get_position();
        hold_Tail = Hook.get_position();
        timer --;
      }
        if(master.get_digital(DIGITAL_L1) == 1){
          Lift_One.move_velocity(100);
          Lift_Two.move_velocity(100);
          hold = Lift_One.get_position();
        }
        else if(master.get_digital(DIGITAL_L2) == 1){
          Lift_One.move_velocity(-100);
          Lift_Two.move_velocity(-100);
          hold = Lift_One.get_position();
        }
        else if (Lift_One.get_position() < (hold - 5)){
          Lift_One.move_velocity(1);
          Lift_Two.move_velocity(1);
        }
        else {
          Lift_One.move_velocity(0);
          Lift_Two.move_velocity(0);
          Lift_One.set_brake_mode(MOTOR_BRAKE_HOLD);;
          Lift_Two.set_brake_mode(MOTOR_BRAKE_HOLD);;
        }


        if (master.get_digital(DIGITAL_A)){
          Hook.move_velocity(100);
          hold_Tail = Hook.get_position();
        }
        else if (master.get_digital(DIGITAL_B)){
          Hook.move_velocity(-100);
          hold_Tail = Hook.get_position();
        }

        else if (Hook.get_position() < (hold_Tail - 5)){
          Hook.move_velocity(1);
        }

        else {
          Hook.move_velocity(0);
          Hook.set_brake_mode(MOTOR_BRAKE_HOLD);
        }

        if (master.get_digital(DIGITAL_R1)){
          Lift_Hook.move_velocity(100);
        }
        else if (master.get_digital(DIGITAL_R2)){
          Lift_Hook.move_velocity(-100);
        }
        else {
          Lift_Hook.move_velocity(0);
          Lift_Hook.set_brake_mode(MOTOR_BRAKE_HOLD);
        }

        if (master.get_digital(DIGITAL_UP)) {
          DriverSelect = 1;
        }
    }
    */
/*
  	if (rightx > 10){
 			top_left_mtr = rightx;
 			btm_right_mtr = -rightx;
 			top_right_mtr = -rightx;
 			btm_left_mtr = rightx;
 		}

		else if (rightx < -10){
 			top_left_mtr = rightx;
 			btm_right_mtr = -rightx;
 			top_right_mtr = -rightx;
 			btm_left_mtr = rightx;
 		}
		//Right Joystick deadband
		else if ((5 > left) && (-5 < left) && (5 > leftx) && (-5 < leftx)){
			top_left_mtr = 0;
			btm_right_mtr = 0;
			top_right_mtr = 0;
			btm_left_mtr = 0;
		}
		//Right Joystick to motor power calculations
		else {
			top_left_mtr = left + leftx;
			btm_right_mtr = left + leftx;
			top_right_mtr = left - leftx;
			btm_left_mtr = left - leftx;
		}
*/
		/*
		else if ((-right - right < 5) && (rightx - rightx < 5)){
			top_left_mtr = right + rightx;
			btm_right_mtr = right + rightx;
		}

		else if ((right > 5) && (rightx > 5)){
			top_left_mtr = right + rightx;
			btm_right_mtr = right + rightx;
		}

		else if ((right - right < -5) && (rightx > 5)){
			top_right_mtr = right + -rightx;
			btm_left_mtr = right + -rightx;
		}

		else if ((rightx - rightx < -5) && (right > 5)){
			top_right_mtr = right + -rightx;
			btm_left_mtr = right + -rightx;
		}

 		else if (abs(rightx) < 5) {
 			top_left_mtr = right;
 			btm_right_mtr = right;
 			top_right_mtr = right;
 			btm_left_mtr = right;
 		}

		else if (abs(right) < 5) {
 			top_left_mtr = rightx;
 			btm_right_mtr = rightx;
 			top_right_mtr = rightx;
 			btm_left_mtr = rightx;
 		}

 		else {
 			top_left_mtr = 0;
 			btm_right_mtr = 0;
 			top_right_mtr = 0;
 			btm_left_mtr = 0;
 		}
		*/

/*
 		if (master.get_digital(DIGITAL_L1)){
 			Lift_One.move_velocity(100);
 			Lift_Two.move_velocity(100);
 		}

 		else if (master.get_digital(DIGITAL_L2)){
 			Lift_One.move_velocity(-100);
 			Lift_Two.move_velocity(-100);
 		}

 		else {
 			Lift_One.move_velocity(1);
 			Lift_Two.move_velocity(1);
 		}
*/
		if (timer == 1){
			hold = Lift_One.get_position();
			hold_Tail = Hook.get_position();
			timer --;
		}






			if (master.get_digital(DIGITAL_A)){
				Hook.move_velocity(100);
				hold_Tail = Hook.get_position();
			}
			else if (master.get_digital(DIGITAL_B)){
				Hook.move_velocity(-100);
				hold_Tail = Hook.get_position();
			}

      /*
			else if (Hook.get_position() < (hold_Tail - 5)){
				Hook.move_velocity(1);
			}
      */
			else {
        Hook.move_velocity(0);
				Hook.set_brake_mode(MOTOR_BRAKE_HOLD);
			}
/*
      if (master.get_digital(DIGITAL_R1)){
        Lift_Hook.move_velocity(100);
      }
      else if (master.get_digital(DIGITAL_R2)){
        Lift_Hook.move_velocity(-100);
      }
      else {
        Lift_Hook.move_velocity(0);
        Lift_Hook.set_brake_mode(MOTOR_BRAKE_HOLD);
      }
      */
 		pros::delay(10);
 	}
 }
}


//test
