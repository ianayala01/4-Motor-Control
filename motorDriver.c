#include "motorDriver.h"

// keep track of where the car is moving (0-359)
int currentHeading = -1; // negative to imply stopped

Motor m1 = {1, HAT1, 2, MOTOR_PWM, MOTOR_IN1, MOTOR_IN2, SPEED_COEFF_1};
Motor m2 = {2, HAT1, 1, MOTOR_PWMB, MOTOR_IN1B, MOTOR_IN2B, SPEED_COEFF_2};
Motor m3 = {3, HAT2, 2, MOTOR_PWM, MOTOR_IN1, MOTOR_IN2, SPEED_COEFF_3};
Motor m4 = {4, HAT2, 1, MOTOR_PWMB, MOTOR_IN1B, MOTOR_IN2B, SPEED_COEFF_4};

void initMotors(){

	// initialize pigpio library
	int init = gpioInitialise();
	printf("initialised: %d\n", init);

	// initialize DEV module
	if(DEV_ModuleInit()) exit(0);
	// more init
	PCA9685_Init(0x40);
        PCA9685_Init(0x45);
        PCA9685_SetPWMFreq(100);
}

// this function will be passed a speed and direction for the motor
void runMotor(Motor m, uint8_t direction, uint16_t speed){
	printf("running motor %d\n", m.num);

	int motorPwm = m.pwm;
	int motorIn1 = m.in1;
	int motorIn2 = m.in2;

	// cap speed at 100%
	if (speed > 100) speed = 100;

	speed = m.speedCoefficient * speed;

	// speed is now duty cycle of the motor
	PCA9685_SetPwmDutyCycle(motorPwm, speed);

	// if direction is forward
	if(direction == FWD){
		printf("forward ");
		// turn motor to one direction
		PCA9685_SetLevel(motorIn1, 0);
		PCA9685_SetLevel(motorIn2, 1);
	} else {
		// turn motor to opposite direction
                PCA9685_SetLevel(motorIn1, 1);
                PCA9685_SetLevel(motorIn2, 0);
		printf("backward ");
	}
	printf("at %d percent speed\n", speed);
}

void stopMotor(Motor m){

	int motorPwm = m.pwm;
//	printf("stopping motor\n");
	// duty cycle of zero means off
	PCA9685_SetPwmDutyCycle(motorPwm, 0);
}

void park(){
	printf("stopping\n");
	PCA9685_Init(HAT1);
	stopMotor(m1);
	stopMotor(m2);

	DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
	stopMotor(m3);
	stopMotor(m4);

	currentHeading = -1;

	gpioDelay(5000);
}

int getHdg(){
	printf("current heading is: %d\n", currentHeading);
	return currentHeading;
}

void veerLeft(){
	printf("veering left!\n");
        DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
	stopMotor(m1);

	DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
	stopMotor(m3);
}

void veerRight(){
	printf("veering right!\n");
	DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
	stopMotor(m2);

	DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
	stopMotor(m4);
}

void goFwd(uint16_t speed){
	printf("car going forward!\n");

        DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
	runMotor(m1, FWD, speed);
	runMotor(m2, FWD, speed);

	DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
	runMotor(m1, FWD, speed);
	runMotor(m2, FWD, speed);

	currentHeading = 0;
}

void goBck(uint16_t speed){
	printf("car going backward!\n");
	DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
	runMotor(m1, BCK, speed);
	runMotor(m2, BCK, speed);

 	DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
  	runMotor(m1, BCK, speed);
	runMotor(m2, BCK, speed);

	currentHeading = 180;
}

void strafeRight(uint16_t speed){
	printf("car going to the Right!\n");
	DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
	runMotor(m1, BCK, speed);
	runMotor(m2, FWD, speed);

	DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
	runMotor(m3, BCK, speed);
	runMotor(m4, FWD, speed);

	currentHeading = 270;
}

void strafeLeft(uint16_t speed){
	printf("car going to the Left!\n");
	DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
	runMotor(m1, FWD, speed);
	runMotor(m2, BCK, speed);

	DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
	runMotor(m3, FWD, speed);
	runMotor(m4, BCK, speed);

	currentHeading = 90;
}

// forward and left
void zigFwd(uint16_t speed){
	printf("car zigging forward!\n");
	DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
	runMotor(m2, FWD, speed);
	DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
	runMotor(m4, FWD, speed);

	currentHeading = 315;
}

// forward and right
void zagFwd(uint16_t speed){
	printf("car zagging forward!\n");
	DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
	runMotor(m1, FWD, speed);
	DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
	runMotor(m3, FWD, speed);

	currentHeading = 45;
}

// back and left
void zigBck(uint16_t speed){
	printf("car zigging backward!\n");
	DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
	runMotor(m1, BCK, speed);
	DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
	runMotor(m3, BCK, speed);

	currentHeading = 225;
}

// back and right
void zagBck(uint16_t speed){
	printf("car zigging backward!\n");
	DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
	runMotor(m2, BCK, speed);
	DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
	runMotor(m4, BCK, speed);

	currentHeading = 135;
}

void spinRight(uint16_t speed){
	printf("See ya later grandmas!\n");
	DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
	runMotor(m1, BCK, speed);
	runMotor(m2, FWD, speed);

	DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
	runMotor(m3, FWD, speed);
	runMotor(m4, BCK, speed);
}

void spinLeft(uint16_t speed){
	printf("car is spinning counter-clockwise!\n");
	DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
	runMotor(m1, FWD, speed);
	runMotor(m2, BCK, speed);

	DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
	runMotor(m3, BCK, speed);
	runMotor(m4, FWD, speed);
}

void doDonut(int radius, uint16_t speed){
	printf("car is doing a donut!\n");

	double top = ((radius * 2) - 4.5);
	printf("top: %f\n", top);
	double bottom = ((radius * 2) + 4.5);
	printf("bottom: %f\n", bottom);

	double innerWheel = top / bottom;

	if (radius == 0) innerWheel = 0;

	printf("innerWheel speed is %f of outter wheel\n", innerWheel);


	if (innerWheel < 0) innerWheel = innerWheel * -1;
	if (innerWheel > 1) innerWheel = 1;

	DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
	runMotor(m1, BCK, speed * innerWheel);
	runMotor(m2, FWD, speed * innerWheel);

	DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
	runMotor(m3, BCK, speed);
	runMotor(m4, FWD, speed);

//	gpioDelay(sec * 1000000);
}


void donutReverse(int radius, uint16_t speed){
        printf("car is doing a donut!\n");

        double top = ((radius * 2) - 4.5);
        printf("top: %f\n", top);
        double bottom = ((radius * 2) + 4.5);
        printf("bottom: %f\n", bottom);

        double innerWheel = top / bottom;

        if (radius == 0) innerWheel = 0;

        printf("innerWheel speed is %f of outter wheel\n", innerWheel);


        if (innerWheel < 0) innerWheel = innerWheel * -1;
        if (innerWheel > 1) innerWheel = 1;

        DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
        runMotor(m1, BCK, speed);
        runMotor(m2, FWD, speed);

        DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
        runMotor(m3, BCK, speed * innerWheel);
        runMotor(m4, FWD, speed * innerWheel);

//      gpioDelay(sec * 1000000);
}


/*
void donutReverse(int sec, uint16_t speed, double innerWheel){
	printf("car is doing reverse donut!\n");
	if (innerWheel < 0) innerWheel = innerWheel * -1;
	if (innerWheel > 1) innerWheel = 1;

	DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
	runMotor(m1, FWD, speed);
	runMotor(m2, BCK, speed);

	DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
	runMotor(m3, FWD, speed * innerWheel);
	runMotor(m4, BCK, speed * innerWheel);

	gpioDelay(sec * 1000000);
}

void figEight(int laps, uint16_t speed, double innerWheel){
	printf("half nut\n");
	doDonut(6, speed, innerWheel);

	for(int i = 0; i < laps; i++){
		printf("top of 8\n");
		donutReverse(8, speed, innerWheel);
		printf("bottom of 8\n");
		doDonut(12, speed, innerWheel);
	}
	donutReverse(8, speed, innerWheel);
}
*/
