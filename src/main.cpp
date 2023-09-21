#include "main.h"
#include "lemlib/api.hpp"
#include "CustomFiles/DriveOdomConst.hpp"

// ..................................................................................
// ..................................................................................

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
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
	chassis.calibrate();
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	pros::lcd::initialize();
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	pros::lcd::initialize();	
}

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
	// file name: path.txt
	// timeout: 2000 ms
	// lookahead distance: 15 inches
	chassis.follow("offside match1.txt", 2000, 15);
	Intake.move_velocity(600);
  	pros::delay(1000); // Move at 100 RPM for 1 second
  	Intake.move_velocity(0);
	chassis.follow("offside match2.txt", 2000, 15);
	chassis.follow("offside match3.txt", 2000, 15);
	chassis.follow("offside match4.txt", 2000, 15);
	chassis.follow("offside match5.txt", 2000, 15);
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
	
	while(true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
						 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
						 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		
		int power = master.get_analog(ANALOG_LEFT_Y);
    	int turn = master.get_analog(ANALOG_RIGHT_X);
    	int left = power + turn;
    	int right = power - turn;
		Leftsidedrive.move(left);
    	Rightsidedrive.move(right);

		// Rightsidedrive.move_velocity(master.get_analog(ANALOG_LEFT_Y) + (master.get_analog(ANALOG_RIGHT_X)*-1));


		pros::delay(20);
	}
}