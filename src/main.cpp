#include "main.h"


void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

pros::ADIDigitalIn selector ('A');
int autonIndex = 0;

void autonSelector(void* parameter){
	const int autoCount = 2;

	const char *autoNames[autoCount] ={
		"Red Front Auton", //0
		"Blue Front Auton" //1
	};
	while(true){
		if(selector.get_value()==1){
			autonIndex++;
			if(autonIndex ==autoCount) {
				autonIndex = 0;
			}

			//%s = print string
			//%d = print integer
			//%f = print double or float
			pros::lcd::print(4, "%s", autoNames[autonIndex]);
			wait(300);
		}
	}
}

void initialize() {
	pros::lcd::initialize();

	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);

	pros::Task auton_selector(autonSelector);
}


void disabled() {}


void competition_initialize() {}

pros::Controller master(pros::E_CONTROLLER_MASTER);

void opcontrol() {
	while (true) {
		driveOP();
		liftOP();
		wait(20);
	}
}
