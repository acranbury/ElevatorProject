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
    int i = 0;  // Loop counter for printing to LCD.
    int curFloor = 0;
    int desiredFloor = 0;
    int elevatorDirection = 0xFF;
    CANMessage message = { 0x00, 0x00, 0x00, {0}};
	  unsigned char txbuff[8] = "";
    for(;;){
        if (PORTB == FLOOR1) {           
           desiredFloor = FLOOR_NUM_1; 
           
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
           desiredFloor = FLOOR_NUM_2; 
           
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
        else if (PORTB == FLOOR3) {           
           desiredFloor = FLOOR_NUM_3; 
           
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
        else if (PORTB == DROPEN) {           
           txbuff[0] = PANEL_BTN_PRESS;
    	     txbuff[1] = DOOR_OPEN;
    	     txbuff[2] = DIR_STOPPED;
      		
      		 message.id = CONTROLLER_ID;
      		 message.priority = 0x00;
      		 message.length = sizeof(txbuff) - 1;
      		 message.payload = txbuff; 
      		 sendCanFrame(message);
        } 
        else if (PORTB == DRCLOSE) {           
           txbuff[0] = PANEL_BTN_PRESS;
    	     txbuff[1] = DOOR_CLOSE;
    	     txbuff[2] = DIR_STOPPED;
      		
      		 message.id = CONTROLLER_ID;
      		 message.priority = 0x00;
      		 message.length = sizeof(txbuff) - 1;
      		 message.payload = txbuff;
      		 sendCanFrame(message);
        } 
        else if (PORTB == ESTOP) {           
           txbuff[0] = PANEL_BTN_PRESS;
    	     txbuff[1] = EMERG_STOP;
      		
      		 message.id = CONTROLLER_ID;
      		 message.priority = 0x00;
      		 message.length = sizeof(txbuff) - 1;
      		 message.payload = txbuff; 
      		 sendCanFrame(message);
        }
        
        i = (i + 1) % 50;
        if (i == 0) {           
          LCDclear();
          switch (txbuff[1]) {
            case FLOOR_NUM_1:
              LCDprintf("Floor 1 pressed\ncurrent:%d", curFloor);
              break;
            case FLOOR_NUM_2:
              LCDprintf("Floor 2 pressed\ncurrent:%d", curFloor);
              break;
            case FLOOR_NUM_3:
              LCDprintf("Floor 3 pressed\ncurrent:%d", curFloor);
              break; 
            case DOOR_OPEN:            
              LCDprintf("Door Opening\ncurrent:%d", curFloor);
              break; 
            case DOOR_CLOSE:            
              LCDprintf("Door Closing\ncurrent:%d", curFloor);
              break;
            default:
              LCDprintf("current:%d", curFloor);
              break;
          } 
        }
        
        if (canRXFlag) {
           DisableInterrupts;
           if (canRXData[0] == ELEV_LOCATION) {
              curFloor = canRXData[1];
           }
			     canRXFlag = 0;
			     EnableInterrupts; 
        }
        msleep(10);
    }
}