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

//	goFwd(2, 100);
//	zigFwd(2, 100);
//	strafeLeft(2, 100);
//	zigBck(2, 100);
//	goBck(2, 100);
//	zagBck(2, 100);
//	strafeRight(2, 100);
//	zagFwd(2, 100);

//	spinRight(5, 100);
//	spinLeft(5, 100);
//	doDonut(6, 100);
//	donutReverse(8, 100);
	figEight(1, 100);
	spinLeft(5, 100);

	park();

	// free everything
	gpioTerminate();
	DEV_ModuleExit();
	return 0;
}
