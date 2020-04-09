#include "main.h"

double kp= 0;

int minSpeed = 0;

PIDController::PIDController(double inKP, int inMinSpeed){
  kP=inKP;
  minSpeed=inMinSpeed;
}
int PIDController::getSpeedToMotor(int target, int current){

  error = target- current;

  int speed = error* kp;

  if (speed<= minSpeed && speed>=0){
    speed=minSpeed;
  }
  else if (speed<=minSpeed && speed<=0){
    speed=-minSpeed;
  }

  return speed;
}

double PIDController::getError(){
  return error;
}
