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
	zigFwd(100);
//        getHdg();
//        sleep(2);

//	strafeLeft(100);
//        getHdg();
//        sleep(2);

//	park();
//	zigBck(100);
//        getHdg();
//        sleep(2);

//	goBck(100);
//        getHdg();
//        sleep(2);

//	park();
//	zagBck(100);
//        getHdg();
//        sleep(2);

//	strafeLeft(100);
//        getHdg();
//        sleep(2);

//	park();
//	zagFwd(100);
//      getHdg();
//        sleep(2);


//	spinRight(100);
//	spinLeft(100);
//	gpioDelay(1300000);
//	doDonut(5, 100);
//	donutReverse(5, 100);
//	figEight(1, 100);
//	spinRight(5, 100);

	while (isAlive){

	}



	park();

	// free everything
	gpioTerminate();
	DEV_ModuleExit();
	return 0;
}
