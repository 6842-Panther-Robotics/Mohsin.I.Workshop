#include "main.h"

using namespace pros;

Motor liftMotor(1, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);

ADIPotentiometer pot('H');
ADILineSensor line('B');


PIDController liftPID(0.465, 7);

//AutonFunctions
void lift(int speed){
  liftMotor.move_velocity(speed);
}

void brakeLift(){
  liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
}

void coastLift(){
  liftMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
}

void moveLift(int target){

  int time=0;

  while(time<50){
    //variables
    int potPosition=pot.get_value();
    int PIDSpeed = liftPID.getSpeedToMotor(target, pot.get_value());

    if(fabs(liftPID.getError())<1){
      time++;//increment by 1
      wait(2);
    }

    lift(PIDSpeed);

  }
  lift(0);
}

//liftOP
void liftOP(){
    if (master.get_digital(DIGITAL_L1)){
      liftMotor.move_velocity(100);
    }
    if (master.get_digital(DIGITAL_L2)){
      liftMotor.move_velocity(-100);
    }
    else{
      liftMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
      liftMotor.move_velocity(0);
    }
  }
