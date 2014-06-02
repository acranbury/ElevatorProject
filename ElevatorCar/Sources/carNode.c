#include <hidef.h>      /* common defines and macros */
#include "carNode.h"
#include "utils.h"
#include "timer.h"
#include "lcd.h"
#include "canModule.h"


void initCarLoop (void) {
    SET_BITS(DDRB,0x00);
}

void runCarLoop (void) {
    int curFloor = 0;
    int desiredFloor = 0;
    int elevatorDirection = 0xFF;
    CANMessage message = { 0x00, 0x00, 0x00, {0}};
	  unsigned char txbuff[8] = "";
    for(;;){
        if (PORTB == FLOOR1) {
           LCDclear();
           LCDprintf("Floor 1 pressed, currently at Floor %d", curFloor); 
           
           desiredFloor = PANEL_FLOOR_1; 
           
           if (desiredFloor > curFloor) 
           {
               elevatorDirection = DIR_DOWN;
           } 
           else if (desiredFloor < curFloor) 
           {
               elevatorDirection = DIR_UP;
           } 
           else 
           {
               elevatorDirection = DIR_STOPPED;
           }
           
           txbuff[0] = PANEL_BTN_PRESS;
    	     txbuff[1] = desiredFloor;
    	     txbuff[2] = elevatorDirection;
      		
      		 message.id = CONTROLLER_ID;
      		 message.priority = 0x00;
      		 message.length = sizeof(txbuff) - 1;
      		 message.payload = txbuff;
      		 sendCanFrame(message);
        } 
        else if (PORTB == FLOOR2) {
           LCDclear();
           LCDprintf("Floor 2 pressed, currently at Floor %d", curFloor); 
           
           desiredFloor = PANEL_FLOOR_2; 
           
           if (desiredFloor > curFloor) 
           {
               elevatorDirection = DIR_DOWN;
           } 
           else if (desiredFloor < curFloor) 
           {
               elevatorDirection = DIR_UP;
           } 
           else 
           {
               elevatorDirection = DIR_STOPPED;
           }
           
           txbuff[0] = PANEL_BTN_PRESS;
    	     txbuff[1] = desiredFloor;
    	     txbuff[2] = elevatorDirection;
      		
      		 message.id = CONTROLLER_ID;
      		 message.priority = 0x00;
      		 message.length = sizeof(txbuff) - 1;
      		 message.payload = txbuff;
        } 
        else if (PORTB == FLOOR3) {
           LCDclear();
           LCDprintf("Floor 3 pressed, currently at Floor %d", curFloor);
           
           desiredFloor = PANEL_FLOOR_3; 
           
           if (desiredFloor > curFloor) 
           {
               elevatorDirection = DIR_DOWN;
           } 
           else if (desiredFloor < curFloor) 
           {
               elevatorDirection = DIR_UP;
           } 
           else 
           {
               elevatorDirection = DIR_STOPPED;
           }
           
           txbuff[0] = PANEL_BTN_PRESS;
    	     txbuff[1] = desiredFloor;
    	     txbuff[2] = elevatorDirection;
      		
      		 message.id = CONTROLLER_ID;
      		 message.priority = 0x00;
      		 message.length = sizeof(txbuff) - 1;
      		 message.payload = txbuff;
        } 
        else if (PORTB == DROPEN) {
           LCDclear();
           LCDprintf("Door Opening...");
           
           txbuff[0] = PANEL_BTN_PRESS;
    	     txbuff[1] = DOOR_OPEN;
    	     txbuff[2] = DIR_STOPPED;
      		
      		 message.id = CONTROLLER_ID;
      		 message.priority = 0x00;
      		 message.length = sizeof(txbuff) - 1;
      		 message.payload = txbuff;
        } 
        else if (PORTB == DRCLOSE) {
           LCDclear(); 
           LCDprintf("Door Closing..."); 
           
           txbuff[0] = PANEL_BTN_PRESS;
    	     txbuff[1] = DOOR_CLOSE;
    	     txbuff[2] = DIR_STOPPED;
      		
      		 message.id = CONTROLLER_ID;
      		 message.priority = 0x00;
      		 message.length = sizeof(txbuff) - 1;
      		 message.payload = txbuff;
        } 
        else if (PORTB == ESTOP) {
           LCDclear(); 
           LCDprintf("EMERGENCY STOP!!\n EXIT IF POSSIBLE!!!");
           
           txbuff[0] = PANEL_BTN_PRESS;
    	     txbuff[1] = DOOR_OPEN;
    	     txbuff[2] = EMERG_STOP;
      		
      		 message.id = CONTROLLER_ID;
      		 message.priority = 0x00;
      		 message.length = sizeof(txbuff) - 1;
      		 message.payload = txbuff;
        }
        
        if (canRXFlag) {
           DisableInterrupts;
           if (canRXData[0] == ELEV_LOCATION) {
              curFloor = canRXData[1];
           }
			     canRXFlag = 0;
			     EnableInterrupts; 
        }
    }
}