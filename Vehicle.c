/*
 * Vehicle.c
 *
 *  Created on: ٢٤‏/٠٨‏/٢٠٢٢
 *      Author: BASSNT
 */

#include <stdio.h>
#include <stdlib.h>
#include "Vehicle.h"

uint8 Choose;
Values Val; //Object of the Values structure

void Init_Values(){ //Set the initial values of the system
	Val.Vehicle_Speed = 100;
	Val.TR1.temperature = 25;
	Val.TR1.AC_State = OFF;
	Val.TE1.temperature = 90;
	Val.TE1.Controller_sate = ON;

	return;
}

void Print_Vehicle_State(){ //Start the system by print the vehicle state
	printf("a. Turn on the vehicle engine\n"
		   "b. Turn off the vehicle engine\n"
		   "c. Quit the system\n");
	return;
}

void Choose_Vehicle_State(){ //Bassed on your choice you can control your vehicle
	uint8 choose1;
	scanf(" %c",&choose1);
	switch (choose1){
	case 'a': //Turn on the vehicle
		Print_Sensors_Set_Menu(); //Show the options that can help you control the vehicle
		fflush(stdout);
		Choose_Sensors_Set_Menu(); //Choose one of these options
		break;
	case 'b': //Turn off the vehicle
		printf("Turn off the vehicle engine\n\n");
		Print_Vehicle_State(); //Show the options of vehicle state again
		fflush(stdout);
		Choose_Vehicle_State(); //Choose one of them
		break;
	case 'c': //To Quit the system
		printf("Quit the system\n");
		_Exit(0); //built in function
		break;
	default: // In case that the user enter wrong choice
		printf("Please choose from this list : \n\n");
		Print_Vehicle_State(); //Show the options again
		fflush(stdout);
		Choose_Vehicle_State();
		break;
	}
	return;
}

void Print_Sensors_Set_Menu(){
	printf("\nSensors set menu\n"
		   "a. Turn off the engine\n"
		   "b. Set the traffic light color.\n"
		   "c. Set the room temperature (Temperature Sensor)\n");

#if (WITH_ENGINE_TEMP_CONTROLLER == 1) //If this condition is wrong this part won't run
    printf("d. Set the engine temperature (Engine Temperature Sensor)\n");
#endif

	return;
}

void Choose_Sensors_Set_Menu(){
	uint8 choose2;
	scanf(" %c",&choose2);
	switch (choose2){
	case 'a': //Turn off the vehicle
		Print_Vehicle_State(); //In this case it will return him to the options of vehicle state
		fflush(stdout);
		Choose_Vehicle_State();
		break;
	case 'b': //Set the traffic light color
		printf("Enter the required color : \n");
		fflush(stdout);
		scanf(" %c",&Choose);
		Traffic_Light_Color();
		Vehicle_Data(Traffic_Light_Color()); // Show all the data of the vehicle
		fflush(stdout);
		Print_Sensors_Set_Menu(); //Show the sensors set menu again
		fflush(stdout);
		Choose_Sensors_Set_Menu();
		break;
	case 'c': //Set the room temperature
		printf("Enter the required room temperature: \n");
		fflush(stdout);
		Temperature_Data_R();
		Vehicle_Data(Traffic_Light_Color());// Show all the data of the vehicle
		fflush(stdout);
		Print_Sensors_Set_Menu();
		fflush(stdout);
		Choose_Sensors_Set_Menu();//Show the sensors set menu again
		break;
#if(WITH_ENGINE_TEMP_CONTROLLER == 1)
	case 'd': //Set the engine temperature
		printf("Enter the required engine temperature: \n");
		fflush(stdout);
		Temperature_Data_E();
		Vehicle_Data(Traffic_Light_Color());
		fflush(stdout);
		Print_Sensors_Set_Menu();
		fflush(stdout);
		Choose_Sensors_Set_Menu();
		break;
#endif
	default: //In case of wrong choice
		printf("\nPlease choose from this list : \n\n");
		Print_Sensors_Set_Menu();
		fflush(stdout);
		Choose_Sensors_Set_Menu();
		break;
	}
	return;
}

uint8 Traffic_Light_Color(){

	switch(Choose){
	case 'G': //At the traffic light is green the speed of the vehicle is 100 Km/Hr
	case 'g':
		Val.Vehicle_Speed = 100;
		break;
	case 'O': //At the traffic light is yellow the speed of the vehicle is 30 Km/Hr
	case 'o':
		Val.Vehicle_Speed = 30;
		break;
	case 'R': //At the traffic light is red the speed of the vehicle is 0 Km/Hr
	case 'r':
		Val.Vehicle_Speed = 0;
		break;
	}

	return Val.Vehicle_Speed;

}

Temp_Room_Data Temperature_Data_R(){

	Val.TR1_ptr = &Val.TR1;

	scanf("%f",&Val.TR1.temperature);

	//At temperature less than 10 or above 30 turn on the AC and set the temperature to 20
	if( (Val.TR1.temperature < 10) || (Val.TR1.temperature > 30) ){
		Val.TR1_ptr -> temperature = 20;
		Val.TR1_ptr -> AC_State = ON;
	}
	else{//At temperature between 10 and 30 turn off the AC and show the current temp
		Val.TR1_ptr -> temperature = Val.TR1.temperature ;
		Val.TR1_ptr -> AC_State = OFF;
	}
	return Val.TR1;
}

#if (WITH_ENGINE_TEMP_CONTROLLER == 1)
Temp_Engine_Data Temperature_Data_E(){

	Val.TE1_ptr = &Val.TE1;

	scanf("%f",&Val.TE1.temperature);

	//At temperature less than 100 or above 150 turn on the Enrine Temp Controller and set the temperature to 125
	if( (Val.TE1.temperature < 100) || ( (Val.TE1.temperature > 150) ) ){
		Val.TE1_ptr -> temperature = 125;
		Val.TE1_ptr -> Controller_sate = ON ;
	}
	else{//At temperature between 100 and 150 turn off the Enrine Temp Controller and show the current temp
		Val.TE1_ptr -> temperature = Val.TE1.temperature;
		Val.TE1_ptr -> Controller_sate = OFF ;
	}
	return Val.TE1;
}
#endif


void Vehicle_Data(uint8 Speed){ //To show all the data of the vehicle

	if(Speed == 30){ //At the speed = 30 turn on the AC and the ETC and set the currunt temp by the following eq:
		Val.TR1.temperature = Val.TR1.temperature * (5.0/4) + 1 ;
		Val.TR1.AC_State = ON;
#if(WITH_ENGINE_TEMP_CONTROLLER == 1)
		Val.TE1.temperature = Val.TE1.temperature * (5.0/4) + 1 ;
		Val.TE1.Controller_sate = ON ;
#endif
	}

	printf("Engine is ON\n");

	if (Val.TR1.AC_State == ON)
		printf("AC is ON\n");
	else
		printf("AC is OFF\n");

	printf("Vehicle Speed: %d Km/Hr\n",Traffic_Light_Color());
	printf("Room Temperature: %f C\n",Val.TR1.temperature);


#if(WITH_ENGINE_TEMP_CONTROLLER == 1)

	if(Val.TE1.Controller_sate == ON)
		printf("Engine Temp Controller is ON\n");
	else
		printf("Engine Temp Controller is OFF\n");

	printf("Engine Temperature: %f C\n",Val.TE1.temperature);
#endif

	return;
}
