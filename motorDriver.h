#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#include <stdio.h>      //printf()
#include <stdlib.h>     //exit()
#include <stdint.h>
#include "DEV_Config.h"
#include <time.h>
#include <pigpio.h>
#include "PCA9685.h"

#define FWD 1
#define BCK 0

#define MOTOR_PWM PCA_CHANNEL_0
#define MOTOR_IN1 PCA_CHANNEL_1
#define MOTOR_IN2 PCA_CHANNEL_2

#define MOTOR_PWMB PCA_CHANNEL_5
#define MOTOR_IN1B PCA_CHANNEL_3
#define MOTOR_IN2B PCA_CHANNEL_4

void initMotors();
void runMotor(int motorGroup, uint8_t direction, uint16_t speed);
void stopMotor(int motorGroup);

// figure out how to calculate distance instead of using seconds
void goFwd(int sec, uint16_t speed);
void goBck(int sec, uint16_t speed);

void strafeRight(int sec, uint16_t speed);
void strafeLeft(int sec, uint16_t speed);

void zigFwd(int sec, uint16_t speed);
void zagFwd(int sec, uint16_t speed);

void park();

#endif
