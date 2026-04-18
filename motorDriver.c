#include "motorDriver.h"

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
        PCA9685_SetPWMFreq(100);
}

// this function will be passed a speed and direction for the motor
void runMotor(Motor m, uint8_t direction, uint16_t speed){
//	printf("running motor group %d\n", motorGroup);

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
//		printf("forward ");
		// turn motor to one direction
		PCA9685_SetLevel(motorIn1, 0);
		PCA9685_SetLevel(motorIn2, 1);
	} else {
		// turn motor to opposite direction
                PCA9685_SetLevel(motorIn1, 1);
                PCA9685_SetLevel(motorIn2, 0);
//		printf("backward ");
	}
//	printf("at %d percent speed\n", speed);
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

	gpioDelay(5000);
}

void goFwd(int sec, uint16_t speed){
	printf("car going forward!\n");

        DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
	runMotor(m1, FWD, speed);
	runMotor(m2, FWD, speed);

        DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
        runMotor(m1, FWD, speed);
        runMotor(m2, FWD, speed);

	gpioDelay(sec * 1000000);
	park();
}

void goBck(int sec, uint16_t speed){
        printf("car going backward!\n");
        DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
        runMotor(m1, BCK, speed);
        runMotor(m2, BCK, speed);

        DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
        runMotor(m1, BCK, speed);
        runMotor(m2, BCK, speed);
        gpioDelay(sec * 1000000);
        park();
}

void strafeLeft(int sec, uint16_t speed){
        printf("car going to the Right!\n");
        DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
        runMotor(m1, BCK, speed);
        runMotor(m2, FWD, speed);

        DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
        runMotor(m3, BCK, speed);
        runMotor(m4, FWD, speed);

        gpioDelay(sec * 1000000);
        park();
}

void strafeRight(int sec, uint16_t speed){
        printf("car going to the Left!\n");
        DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
        runMotor(m1, FWD, speed);
        runMotor(m2, BCK, speed);

        DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
        runMotor(m3, FWD, speed);
        runMotor(m4, BCK, speed);

        gpioDelay(sec * 1000000);
        park();
}

// forward and left
void zigFwd(int sec, uint16_t speed){
	printf("car zigging forward!\n");
        DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
	runMotor(m2, FWD, speed);
        DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
        runMotor(m4, FWD, speed);

	gpioDelay(sec * 1000000);
	park();
}

// forward and right
void zagFwd(int sec, uint16_t speed){
	printf("car zagging forward!\n");
        DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
	runMotor(m1, FWD, speed);
        DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
        runMotor(m3, FWD, speed);
	gpioDelay(sec * 1000000);
	park();
}

// back and left
void zigBck(int sec, uint16_t speed){
	printf("car zigging backward!\n");
        DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
	runMotor(m1, BCK, speed);
        DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
        runMotor(m3, BCK, speed);
	gpioDelay(sec * 1000000);
	park();
}

// back and right
void zagBck(int sec, uint16_t speed){
        printf("car zigging backward!\n");
        DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
        runMotor(m2, BCK, speed);
        DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
        runMotor(m4, BCK, speed);

        gpioDelay(sec * 1000000);
        park();
}

void spinRight(int sec, uint16_t speed){
        DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
        runMotor(m1, BCK, speed);
        runMotor(m2, FWD, speed);

        DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
        runMotor(m3, FWD, speed);
        runMotor(m4, BCK, speed);

        gpioDelay(sec * 1000000);
        park();
}

void spinLeft(int sec, uint16_t speed){
        DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
        runMotor(m1, FWD, speed);
        runMotor(m2, BCK, speed);

        DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
        runMotor(m3, BCK, speed);
        runMotor(m4, FWD, speed);

        gpioDelay(sec * 1000000);
        park();
}

void doDonut(int sec, uint16_t speed){
        printf("car going to the Left!\n");
        DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
        runMotor(m1, FWD, speed/2);
        runMotor(m2, BCK, speed/2);

        DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
        runMotor(m3, FWD, speed);
        runMotor(m4, BCK, speed);

        gpioDelay(sec * 1000000);
        park();
}

void donutReverse(int sec, uint16_t speed){
        printf("car going to the Left!\n");
        DEV_HARDWARE_I2C_setSlaveAddress(HAT1);
        runMotor(m1, FWD, speed);
        runMotor(m2, BCK, speed);

        DEV_HARDWARE_I2C_setSlaveAddress(HAT2);
        runMotor(m3, FWD, speed/2);
        runMotor(m4, BCK, speed/2);

        gpioDelay(sec * 1000000);
        park();
}

void figEight(int laps, uint16_t speed){
	printf("half nut\n");
	doDonut(6, speed);

	for(int i = 0; i < laps; i++){
		printf("top of 8\n");
		donutReverse(8, speed);
		printf("bottom of 8\n");
		doDonut(12, speed);
	}
	donutReverse(8, speed);
}
