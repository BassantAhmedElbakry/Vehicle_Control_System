/*
 * Vehicle.h
 *
 *  Created on: ٢٤‏/٠٨‏/٢٠٢٢
 *      Author: BASSNT
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#define WITH_ENGINE_TEMP_CONTROLLER 1

typedef unsigned char uint8;

typedef enum{
	ON,
	OFF
}State;

typedef struct {
	float temperature;
    State AC_State;
}Temp_Room_Data;

typedef struct {
	float temperature;
    State Controller_sate;
}Temp_Engine_Data;

typedef struct{
	uint8 Vehicle_Speed ;
	Temp_Room_Data TR1,*TR1_ptr;
	Temp_Engine_Data TE1,*TE1_ptr;

}Values;

void Init_Values();
void Print_Vehicle_State();
void Choose_Vehicle_State();
void Print_Sensors_Set_Menu();
void Choose_Sensors_Set_Menu();
uint8 Traffic_Light_Color();
Temp_Room_Data Temperature_Data_R();

#if(WITH_ENGINE_TEMP_CONTROLLER == 1)
Temp_Engine_Data Temperature_Data_E();
#endif

void Vehicle_Data(uint8);


#endif /* VEHICLE_H_ */
