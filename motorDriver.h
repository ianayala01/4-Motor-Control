#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#include <stdio.h>      //printf()
#include <stdlib.h>     //exit()
#include <stdint.h>
#include "DEV_Config.h"
#include <time.h>
#include <pigpio.h>
#include "PCA9685.h"
#include <stdbool.h>

#define FWD 1
#define BCK 0

#define HAT1 0x40
#define HAT2 0x45

#define MOTOR_PWM PCA_CHANNEL_0
#define MOTOR_IN1 PCA_CHANNEL_1
#define MOTOR_IN2 PCA_CHANNEL_2

#define MOTOR_PWMB PCA_CHANNEL_5
#define MOTOR_IN1B PCA_CHANNEL_3
#define MOTOR_IN2B PCA_CHANNEL_4

#define SPEED_COEFF_1 1
#define SPEED_COEFF_2 .9448
#define SPEED_COEFF_3 .9927
#define SPEED_COEFF_4 .9716

typedef struct {
	int num;
	int hat;
	int idx;

	int pwm;
	int in1;
	int in2;
	double speedCoefficient;
} Motor;

void initMotors();
void runMotor(Motor m, uint8_t direction, uint16_t speed);
void stopMotor(Motor m);

// figure out how to calculate distance instead of using seconds
void goFwd(int sec, uint16_t speed);
void goBck(int sec, uint16_t speed);

void strafeRight(int sec, uint16_t speed);
void strafeLeft(int sec, uint16_t speed);

void zigFwd(int sec, uint16_t speed);
void zagFwd(int sec, uint16_t speed);

void zigBck(int sec, uint16_t speed);
void zagBck(int sec, uint16_t speed);

void spinRight(int sec, uint16_t speed);
void spinLeft(int sec, uint16_t speed);

void doDonut(int sec, uint16_t speed);
void donutReverse(int sec, uint16_t speed);
void figEight(int laps, uint16_t speed);

void park();

#endif
