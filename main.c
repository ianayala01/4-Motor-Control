#include "main.h"

int isAlive = 1;

void Handler(int signo){

	isAlive = 0;
}


int main(void){
	initMotors();

	// for ctrl + c
	signal(SIGINT, Handler);

        while(isAlive){
		goFwd(5, 100);
		goBck(5, 100);

		strafeRight(5, 100);
		strafeLeft(5, 100);

		zigFwd(5, 100);
		zagFwd(5, 100);

		zigBck(5, 100);
		zagBck(5, 100);
        }
	park();
	// free everything
	gpioTerminate();
	DEV_ModuleExit();
	return 0;
}
