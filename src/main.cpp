#include "main.h"
#include "Functions_and_Variables.h"
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

 int autonselect;



void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "Right Side Auton Active");
    autonselect = 0;
	} else {
		pros::lcd::clear_line(2);
	}
}

void on_button_1() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "Left Side Auton Active");
    autonselect = 1;
	} else {
		pros::lcd::clear_line(2);
	}
}
void on_button_2() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "Right Side Auton Active");
    autonselect = 2;
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
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
  pros::lcd::register_btn1_cb(on_button_1);
  pros::lcd::register_btn1_cb(on_button_2);
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
  pros::Controller master(pros::E_CONTROLLER_MASTER);
  pros::Motor top_left_mtr(11);
  pros::Motor top_right_mtr(5, true);
  pros::Motor btm_left_mtr(20);
  pros::Motor btm_right_mtr(10, true);
  pros::Motor Lift_One(2);
  pros::Motor Lift_Two(12, true);
  pros::Motor Hook(15);
  pros::Motor Lift_Hook(13);
  LockStart = Lift_Hook.get_position();


if (autonselect == 0){
  DeployLift();
  DriveFwd(48);
  RaiseLift();
  DriveFwd(12);
  TurnRight90(1);
  DeployTail();
  DriveFwd(-36);
  RaiseTail();
  TurnRight90(1);
  DriveFwd(36);
}
else if (autonselect == 1){
  DriveFwdSlow(0);
  LockFullYeet();
  DriveFwd(-1);
  LockReset();
  DeployLift();
  DriveFwd(0);
  Lock();
  RaiseLift();
  DriveFwd(-1);
}
else if (autonselect == 2){
  DriveFwdSlow(0);
  LockFullYeet();
  DriveFwd(-1);
  TurnLeft90(1);
  DriveFwd(71);
  TurnRight90(1);
  LockReset();
  DeployLift();
  DriveFwd(1);
  Lock();
  RaiseLift();
  TurnRight90(1);
  DriveFwd(71);
  TurnRight90(1);
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
 	pros::Motor top_left_mtr(11);
 	pros::Motor top_right_mtr(5, true);
 	pros::Motor btm_left_mtr(20);
 	pros::Motor btm_right_mtr(10, true);
 	pros::Motor Lift_One(2);
 	pros::Motor Lift_Two(12, true);
	pros::Motor Hook(15);
  pros::Motor Lift_Hook(13);
	int hold;
	int timer = 1;
	int hold_Tail;

 	while (true) {
 		int left = master.get_analog(ANALOG_LEFT_Y);
 		int right = master.get_analog(ANALOG_RIGHT_Y);
 		int leftx = master.get_analog(ANALOG_LEFT_X);
 		int rightx = master.get_analog(ANALOG_RIGHT_X);
		/*Check left joystick for turn input*/
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
		/*Right Joystick deadband*/
		else if ((5 > left) && (-5 < left) && (5 > leftx) && (-5 < leftx)){
			top_left_mtr = 0;
			btm_right_mtr = 0;
			top_right_mtr = 0;
			btm_left_mtr = 0;
		}
		/*Right Joystick to motor power calculations*/
		else {
			top_left_mtr = left + leftx;
			btm_right_mtr = left + leftx;
			top_right_mtr = left - leftx;
			btm_left_mtr = left - leftx;
		}

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

      if (master.get_digital(DIGITAL_X)){
        Lift_Hook.move_velocity(100);
      }
      else if (master.get_digital(DIGITAL_Y)){
        Lift_Hook.move_velocity(-100);
      }
      else {
        Lift_Hook.move_velocity(0);
        Lift_Hook.set_brake_mode(MOTOR_BRAKE_HOLD);
      }
 		pros::delay(10);
 	}
 }



//test
