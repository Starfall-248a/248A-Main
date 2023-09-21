#include "main.h"
 
// Motors for drivetrain, cata, and intake
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor FL(3, pros::E_MOTOR_GEARSET_06, true); // port 3, blue gearbox, reversed
pros::Motor BL(4, pros::E_MOTOR_GEARSET_06, true); // port 4, blue gearbox, reversed
pros::Motor TL(5, pros::E_MOTOR_GEARSET_06, false); // port 5, blue gearbox, not reveresed
pros::Motor FR(6, pros::E_MOTOR_GEARSET_06, false); // port 6, blue gearbox, not reveresed
pros::Motor BR(7, pros::E_MOTOR_GEARSET_06, false); // port 7, blue gearbox, not reveresed
pros::Motor TR(8, pros::E_MOTOR_GEARSET_06, true); // port 8, blue gearbox, reversed
pros::Motor Cata(1, pros::E_MOTOR_GEARSET_36, false); // port 1, red gearbox, not reveresed
pros::Motor Intake(11, pros::E_MOTOR_GEARSET_06, false); // port 11, blue gearbox, not reveresed

// Motor groups for drive
pros::MotorGroup Leftsidedrive({FL, BL, TL});
pros::MotorGroup Rightsidedrive({FR, BR, TR});

// Rotation sensors for odom
pros::Rotation rot(9, false); // port 9, not reversed
pros::Rotation brot(10, false); // port 10, not reversed

// inertial sensor
pros::Imu inertial_sensor(2); // port 2