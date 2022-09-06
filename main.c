/*
 ============================================================================
 Name        : Vehicle_Control_system.c
 Author      : Bassant Ahmed Elbakry
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Vehicle.h"

/*
 You can choose to run  the code lines that are related to the "Engine Temperature Controller"
 or not by the line 11 at header file if it == 1 the code will run else it won't run
 */

int main(void) {

	Init_Values(); //Set the initial values of the system
	Print_Vehicle_State(); //Start the system by print the vehicle state
	fflush(stdout);
	Choose_Vehicle_State(); //Bassed on your choice you can control your vehicle

	return 0;
}


