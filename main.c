#include "main.h"

int isAlive = 1;

void Handler(int signo){

	isAlive = 0;
	park();
	usleep(1000000);
}


int main(void){
	initMotors();

	// for ctrl + c
	signal(SIGINT, Handler);
/*
	goFwd(100);
	getHdg();
	sleep(2);

	park();
	zigFwd(100);
        getHdg();
        sleep(2);

	strafeLeft(100);
        getHdg();
        sleep(2);

	park();
	zigBck(100);
        getHdg();
        sleep(2);

	goBck(100);
        getHdg();
        sleep(2);

	park();
	zagBck(100);
        getHdg();
        sleep(2);

	strafeRight(100);
        getHdg();
        sleep(2);

	park();
	zagFwd(100);
        getHdg();
        sleep(2);
*/

//	spinRight(5, 100);
//	spinLeft(5, 100);
	doDonut(6, 100, .5);
//	donutReverse(8, 100);
//	figEight(1, 100);
//	spinRight(5, 100);

	park();

	// free everything
	gpioTerminate();
	DEV_ModuleExit();
	return 0;
}
