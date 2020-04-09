#include "main.h"

using namespace pros;
// define inertial
pros::Imu inertial(8);

//18:1 -> Green cartridge
//36:1 -> Red cartridge
//6:1 -Blue cartridge
//Define motors
pros::Motor rightFront(1, pros::E_MOTOR_GEARSET_06, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor rightBack (1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftFront(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor leftBack (1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);


//variables
int TICS_PER_REVOLUTION= 360;
double WHEEL_DIAMETER= 4;
double pi= 3.14159;

double CORRECTION_FACTOR = 0.8;
int THRESHHOLD = -5;

PIDController movePID(0.1, 30);
PIDController turnPID(2.5, 30);

//auton functions
void wait(int time){
  pros::delay(time);
}

void left(int speed){
  leftFront.move(speed);
  leftBack.move(speed);

}

void right(int speed){
  rightFront.move(speed);
  rightBack.move(speed);
}

void timedDrive(int time, int speed){
  right(speed);
  left(speed);
  wait(time);
  right(0);
  left(0);

}

void brake(){
  leftFront.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  rightFront.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  leftBack.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  rightBack.set_brake_mode(E_MOTOR_BRAKE_HOLD);
}

void coast(){
  leftFront.set_brake_mode(E_MOTOR_BRAKE_COAST);
  rightFront.set_brake_mode(E_MOTOR_BRAKE_COAST);
  leftBack.set_brake_mode(E_MOTOR_BRAKE_COAST);
  rightBack.set_brake_mode(E_MOTOR_BRAKE_COAST);
}

void moveForward(int inches){

  rightFront.tare_position();
  leftFront.tare_position();

  int time=0;
  double target = TICS_PER_REVOLUTION*(inches / (WHEEL_DIAMETER * pi));

  while(time<50){

    int rightFrontPosition = rightFront.get_position();
    int leftFrontPosition = leftFront.get_position();

    int PIDSpeed = movePID.getSpeedToMotor(target, rightFront.get_position());

    if (rightFrontPosition - leftFrontPosition <= THRESHHOLD){
      right(PIDSpeed);
      left(PIDSpeed * CORRECTION_FACTOR);
    }

    if (leftFrontPosition - rightFrontPosition <= THRESHHOLD){
      right(PIDSpeed * CORRECTION_FACTOR);
      left(PIDSpeed);
    }
    else{
      right(PIDSpeed);
      left(PIDSpeed);
    }

    if(fabs(movePID.getError())<1){
      time++;//increment by 1
      wait(2);
    }
  }
  right(0);
  left(0);
}

void moveBackward(int inches){
  rightFront.tare_position();
  leftFront.tare_position();

  int time=0;
  double target = TICS_PER_REVOLUTION*(inches / (WHEEL_DIAMETER * pi));

  while(time<50){

    int rightFrontPosition = rightFront.get_position();
    int leftFrontPosition = leftFront.get_position();

    int PIDSpeed = movePID.getSpeedToMotor(target, rightFront.get_position());

    if (rightFrontPosition - leftFrontPosition <= -THRESHHOLD){
      right(-PIDSpeed);
      left(-PIDSpeed * CORRECTION_FACTOR);
    }

    if (leftFrontPosition - rightFrontPosition <= -THRESHHOLD){
      right(-PIDSpeed * CORRECTION_FACTOR);
      left(-PIDSpeed);
    }
    else{
      right(-PIDSpeed);
      left(-PIDSpeed);
    }

    if(fabs(movePID.getError())<1){
      time++;//increment by 1
      wait(2);
    }
  }
  right(0);
  left(0);
}

void turn(int degrees){

  int time=0;
  while(time<50) {
    right(turnPID.getSpeedToMotor(degrees, inertial.get_rotation()));
    left(-turnPID.getSpeedToMotor(degrees, inertial.get_rotation()));

    if(fabs(turnPID.getError())<1) {
      time++;//increment by one
      wait(2);
    }
  }
  right(0);
  left(0);
}

//drive control
void driveOP(){
    rightFront.move(master.get_analog(ANALOG_RIGHT_Y));
    leftFront.move(master.get_analog(ANALOG_LEFT_Y));
    rightBack.move(master.get_analog(ANALOG_RIGHT_Y));
    leftBack.move(master.get_analog(ANALOG_LEFT_Y));
  }
