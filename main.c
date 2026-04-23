#include "main.h"

int isAlive = 1;

void Handler(int signo){

	isAlive = 0;
	park();
	//usleep(1000000);
}


int main(void){
	initMotors();

	// for ctrl + c
	signal(SIGINT, Handler);

//	goFwd(100);
//	getHdg();
//	sleep(2);

//	park();

	//forward-right
//	zigFwd(100);
//        getHdg();
//        sleep(2);

//	strafeLeft(100);
//        getHdg();
//        sleep(2);

//	park();
	// back-right
//	zigBck(100);
//        getHdg();
//        sleep(2);

//	goBck(100);
//        getHdg();
//        sleep(2);

//	park();
	// back-left
//	zagBck(100);
//        getHdg();
//        sleep(2);

//	strafeRight(100);
//        getHdg();
//        sleep(2);

//	park();
	// fwd-left
//	zagFwd(100);
//      getHdg();
//        sleep(2);

//	doDonut(5, 100);
//	spinRight(5, 100);
//	spinLeft(100);

	while (isAlive){

	}

	park();

	// free everything
	gpioTerminate();
	DEV_ModuleExit();
	return 0;
}
