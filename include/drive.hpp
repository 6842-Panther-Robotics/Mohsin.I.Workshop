
//driver control
void driveOP();

//autonomous functions
void moveForward(int inches);
void moveBackward(int inches);
void turnRight(int degrees, int speed);
void turn(int degrees, int speed);

//helper functions
void wait(int time);
void left(int speed);
void right(int speed);
void timedDrive(int time, int speed);
void brake();
void coast();
