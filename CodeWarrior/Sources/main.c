#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "timer.h"
#include "lcd.h"
#include "usonic.h"
#include "utils.h"
#include "canModule.h"
#include "spi.h"

// Elevator Defines
#define ELEV_THRESHOLD 5  // Threshold to have arrived at a floor, in mm.

#define FLOOR_DISTANCE 50  //Distance between floors
#define FLOOR_OFFSET 50     //Sensor reading at ground floor in mm

#define ELEV_1ST 50       // Distance to be at the 1st floor, in mm.
#define ELEV_2ND 100       // Distance to be at the 1st floor, in mm.
#define ELEV_3RD 150       // Distance to be at the 1st floor, in mm.
#define ELEV_4TH 200       // Distance to be at the 1st floor, in mm.

//Elevator directions
#define DIR_UP 1
#define DIR_DOWN 2
#define DIR_STOPPED 3

#define NUM_FLOORS 4

//Elevator panel buttons
#define PANEL_FLOOR_1 0x01
#define PANEL_FLOOR_2 0x02
#define PANEL_FLOOR_3 0x03
#define PANEL_FLOOR_4 0x04
#define DOOR_OPEN 0x10
#define DOOR_CLOSE 0x11
#define EMERG_STOP 0xEE

#define UP_CALL_BTN 0x02

void main(void) {
    char i;
	unsigned char txbuff[8] = "";
	word distance;
	CANMessage message = { 0x00, 0x00, 0x00, {0}};
	unsigned char curFloor = 0;
	unsigned char lastFloor = 0;
	unsigned char elevatorDirection = 0;
	unsigned char callButtonsPressed[2][NUM_FLOORS] = { 0 };
	unsigned char elevatorTarget = 0;
	unsigned char targetFound = 0;

	timer_init();
	LCDinit();

	initCan();

	while (!(CANCTL0 & 0x10));

	CANRFLG = 0xC3;
	CANRIER = 0x01;

	//LCDprintf("Hello World");

	usonic_init();
	
	EnableInterrupts;

	for(;;) {
		LCDclear();
		
		
		//get elevator distance
		distance = usonic_getDistance();
		
		//generalized for NUM_FLOORS, for a given floor offset to the ground floor, and distance between floors (left in big if statement in case
		        //distance between floors is non-constant
		for(i=0; i< NUM_FLOORS; i++){
		   if (distance < (FLOOR_OFFSET + (FLOOR_DISTANCE*i) + ELEV_THRESHOLD) && distance > (FLOOR_OFFSET + (FLOOR_DISTANCE*i) - ELEV_THRESHOLD)) {
                //LCDprintf("1st Floor!\n %d mm", distance);
                curFloor = i+1;	
		   }
		}
		 
        /*if (distance < (ELEV_1ST + ELEV_THRESHOLD) && distance > (ELEV_1ST - ELEV_THRESHOLD)) {
            //LCDprintf("1st Floor!\n %d mm", distance);
            curFloor = 1;
        } else if (distance < (ELEV_2ND + ELEV_THRESHOLD) && distance > (ELEV_2ND - ELEV_THRESHOLD)) {
            //LCDprintf("2nd Floor!\n %d mm", distance);  
            curFloor = 2;
    	} else if (distance < (ELEV_3RD + ELEV_THRESHOLD) && distance > (ELEV_3RD - ELEV_THRESHOLD)) {
            //LCDprintf("3rd Floor!\n %d mm", distance); 
            curFloor = 3; 
        } else if (distance < (ELEV_4TH + ELEV_THRESHOLD) && distance > (ELEV_4TH - ELEV_THRESHOLD)) {
    	    //LCDprintf("4th Floor!\n %d mm", distance);  
            curFloor = 4;
    	} */
		
    	if (elevatorTarget != curFloor) {
    	    if ((elevatorTarget - curFloor) > 0 ) { 
    	        elevatorDirection = DIR_UP;        
    	    } else {
    	        elevatorDirection = DIR_DOWN;
    	    }
    	    txbuff[0] = ELEV_LOCATION;
    	    txbuff[1] = curFloor;
    	    txbuff[2] = elevatorDirection;
      		
      		message.id = ELEVATOR_CAR_ID | FLOOR_1_ID | FLOOR_2_ID | FLOOR_3_ID;
      		message.priority = 0x00;
      		message.length = sizeof(txbuff) - 1;
      		message.payload = txbuff;
    	    
    	    lastFloor = curFloor;
    	} else {   //elevatorTarget = curFloor, which means elevator is stationary     	    
    	    elevatorDirection = DIR_STOPPED; //set direction to stationary
    	    txbuff[0] = ELEV_LOCATION;
    	    txbuff[1] = curFloor;
            txbuff[2] = elevatorDirection;
    	    
    	    message.id = ELEVATOR_CAR_ID | FLOOR_1_ID | FLOOR_2_ID | FLOOR_3_ID;
    	    message.priority = 0x00;
    	    message.length = sizeof(txbuff) - 1;
    	    message.payload = txbuff;
    	    
    	    targetFound = 0; //clear the target found flag to find a new target
    	}	
		sendCanFrame(message); 
		
		if ( canRXFlag )  //have received a message from one of the various floor buttons, receive message and enter it into the required motor output.
		{
		    if (canRXData[0] == CALL_BTN_PRESS){
		        if(canRXData[2] == UP_CALL_BTN){
		            callButtonsPressed[0][canRXData[1]-1] = 1;
		        }else {
		            callButtonsPressed[1][canRXData[1]-1] = 1;
		        }
		        
		    } else if (canRXData[0] == PANEL_BTN_PRESS){
		        switch (canRXData[1]){
		            case PANEL_FLOOR_1:
		                break;
		            case PANEL_FLOOR_2:
		                break;
		            case PANEL_FLOOR_3:
		                break;
		            case PANEL_FLOOR_4:
		                break;
		            case DOOR_CLOSE:
		                break;
		            case DOOR_OPEN:
		                break;
		            case EMERG_STOP:
		                break;
		            default:
		                break;
		        
		        }
		    } else if (canRXData[0] == ERROR_MSG){
		        
		    } //else ignore message
		    
		    //LCDprintf("Floor %d!\n %d mm", canRXData[0], distance);
			canRXFlag = 0;
		}
		else
			//LCDprintf("Hello World!\n %d mm", distance);
			
	    
	    //Logic to determine the current elevator target
	    if (targetFound == 0) {
	        
    	    if (elevatorDirection == DIR_UP){    //Elevator is currently moving up, handle any up requests above elevator before moving down
    	        for(i=curFloor-1; i< NUM_FLOORS; i++){
    	            if(callButtonsPressed[0][i]){
    	                callButtonsPressed[0][i] = 0;
    	                elevatorTarget = i+1;
    	                targetFound = 1;
    	                break;
    	            }
    	        }
    	        if (targetFound == 0) {             //No up requests above elevator current position, service any down requests, from the top floor first 
    	           for(i = NUM_FLOORS; i >= 0; i--){
    	                if(callButtonsPressed[1][i]){
    	                    callButtonsPressed[1][i] = 0;
    	                    elevatorTarget = i+1;
    	                    targetFound = 1;
    	                    break;
    	                }
    	           }
    	           if(targetFound == 0){                //no down requests found, service any up requests below the elevator's current floor
    	                for(i=0; i< curFloor-1; i++){
    	                    if(callButtonsPressed[0][i]){
    	                        callButtonsPressed[0][i] = 0;
    	                        elevatorTarget = i+1;
    	                        targetFound = 1;
    	                        break;
    	                    }
    	                }
    	           }
    	        }
    	    } else if (elevatorDirection == DIR_DOWN){    //Elevator currently moving down, handle any down requests below the elevator before moving back up
    	        for (i=curFloor-1; i >= 0; i--){
    	            if(callButtonsPressed[1][i]){
    	                callButtonsPressed[0][i] = 0;
    	                elevatorTarget = i + 1;
    	                targetFound = 1;
    	                break;
    	            }
    	        }
    	        if (targetFound == 0) {             //No down requests below elevator current position, service any up requests, from the bottom floor first 
    	           for(i = 0; i < NUM_FLOORS; i++){
    	                if(callButtonsPressed[0][i]){
    	                    callButtonsPressed[0][i] = 0;
    	                    elevatorTarget = i+1;
    	                    targetFound = 1;
    	                    break;
    	                }
    	           }
    	           if(targetFound == 0){                //no up requests found, service any down requests above the elevator's current floor
    	                for(i=NUM_FLOORS; i >= curFloor-1; i--){
    	                    if(callButtonsPressed[1][i]){
    	                        callButtonsPressed[1][i] = 0;
    	                        elevatorTarget = i+1;
    	                        targetFound = 1;
    	                        break;
    	                    }
    	                }
    	           }
    	        }
    	    }
	    }
			
		if(targetFound){
		    LCDprintf("Elevator target floor is %d!", elevatorTarget);
		} else {
		    LCDprintf("Elevator is stationary, no buttons pressed.");
		}
		msleep(100);
  } 
}
