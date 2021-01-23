// This is the starter code for the Lab 4 Task 2B.
// Designed for ECE/CSE 474.
//
// Please read through the entire file and make sure
// you understand your tasks, the structure of the code,
// and the hints you are given (although you are not
// required to follow them)
//
// The only requirement is to use the three tasks specified
// in the main function. Feel free to add/delete the code we
// provided, though it is recommended to follow the hints.
//
// Here's the documentation page for FreeRTOS.
// You may want to look at it when doing this assignment.
// https://www.freertos.org/FreeRTOS-quick-start-guide.html
/*
* CHOU, HENG-YINg
 * 1926322
 * 12/9/2020
*/

#include "FreeRTOS.h"
#include "task.h"
// Include the LCD driver's header file, the PLL driver's header file,
// and your own header file here.
#include "FreeRTOSConfig.h"
#include "SSD2119_Display_42b.h"
#include "SSD2119_Touch_42b.h"
#include "tm4c1294ncpdt_42b.h"
#include "Lab42b_Inits_42b.h"
#include "PLL_Header42b.h"
#include <stdbool.h>// boolean 
int X,Y;
// After skimming through the entire file,
// you might want to add some FSM states here.
bool x = false; // This bool is for jumping out of while loop when switch 1 is pressed. 
enum LA_States { LA_SMStart, go, stop, warn , LA_end } LA_State; // states of state machine

// Hint:
//
// The following global variables are flags you may want to use
int pedestrian_status = 0;
int onoff_status = 0;


// Below are function prototypes for our RTOS task.
// You should not change the function declerations.
// However, you are allowed to add more helper functions
// as needed.

// Task function that checks the state of the virtual pedestrian button.
// Keeps track of how many seconds the pedestrian button has been pressed.
// Once the user has pressed the virtual pedestrian button for 2 seconds,
// it will set the global flag indicating the virtual pedestrian button
// has been pressed.
void Pedestrian(void *p);

// Task function that checks the state of the virtual onoff button.
// Keeps track of how many seconds the onoff button has been pressed.
// Once the user has pressed the onoff button for 2 seconds,
// it will set the global flag indicating the onoff button has been
// pressed
void StartStop(void *p);

// Task function that represents your Finite State Machine.
// Keeps track of how many seconds the virtual traffic light has been
// lighting on. It will update the state of the traffic light system
// every 5 seconds or once there's virtual button input.
void Control(void *p);

// Helper function that represents your FSM.
// You are allowed to change this function decleration.
//
// Handles the traffic light state transition.
void FSM(void);


// Do not modify this function.
//
// This hook is called by FreeRTOS when an stack overflow error is detected.
void vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName) {
  // This function can not return, so loop forever.  Interrupts are disabled
  // on entry to this function, so no processor interrupts will interrupt
  // this loop.
  while (1) {}
}


// Initialize FreeRTOS and start the tasks.
int main(void) {
  // STEP 1
  //
  // This is the beginning of the main function,
  // Initialize your system by initialize the display and touch
  // functionalities of your SSD2119 touch display assembly. You may
  // also want to initialize (draw) your virtual buttons here.
  // Moreover, initialize the PLL to set the system clock to 60 MHz.
  LCD_Init();            // Initialize the 4 onboard LEDs (GPIO)
  LCD_DrawFilledRect(20,100,100,100,Color4[13]);
  LCD_SetCursor(50, 140);
  LCD_PrintString("On/off");
  LCD_DrawFilledRect(180,100,100,100,Color4[13]);
  LCD_SetCursor(205, 140);
  LCD_PrintString("Pedistrain");
  Touch_Init();
  enum frequency freq = PRESET2;
  PLL_Init(freq);
  LA_State = LA_SMStart;

  


  // STEP 2
  //
  // The code below creates three tasks.
  // Your task here is to assign priorities to the tasks.
  //
  // Think about which task(s) should be given the highest
  // priority and which should be given lower. It is possible to assign
  // the same priority to all the tasks, however.
  //
  // Priorities are in range: [0, configMAX_PRIORITIES - 1], where
  // configMAX_PRIORITIES - 1 corresponds to the highest priority and
  // 0 corresponds to the lowest priority.
  // You can find configMAX_PRIORITIES defined in the file called FreeRTOSConfig.h
  // under the freertos_demo directory.
  //
  // You should not create more tasks. However, you are allowed to add as many
  // helper functions as you want.
  // xTaskCreate(Function Name,
  //             Descriptive Task Name,
  //             Stack Depth,
  //             Task Function Parameter,
  //             Priority,
  //             Task Handle);
  xTaskCreate(StartStop, (const char *)"StartStopButton", 1024, NULL,15 , NULL);
  xTaskCreate(Pedestrian, (const char *)"PedestrianButton", 1024, NULL,15 , NULL);
  xTaskCreate(Control, (const char *)"Control FSM", 1024, NULL,15, NULL);

  // Start the scheduler. This should not return.
  // The scheduler will do the scheduling and switch between
  // different tasks for you.
  // Refer to the lecture slides and RTOS documentation
  // page for more details about task scheduling and context switching.
  //
  // One important concept for context switching and task scheduling
  // is preemption. Think about what the terminology preemptive and
  // non-preemptive mean.
  //
  // Hint: Non-preemptive scheduling will allow other tasks to be scheduled
  // after the current task has entered the "waiting state". That is, in our context,
  // the current task will keep running until it reaches vTaskDelay
  // (you'll see this in task functions).
  //
  // You can find in FreeRTOSConfig.h the setting of preemption
  // for the RTOS. Feel free to change this setting as needed.
  vTaskStartScheduler();

  // In case the scheduler returns for some reason, loop forever.
  while(1) {}
}

void StartStop(void *p) {
  // Hint:
  //
  // Static variable will only be decleared once and
  // will retain its last assigned value until the entire
  // program exits
  static int curr_onoff_tick_time = 0;
  static int prev_onoff_tick_time = 0;

  // xTaskGetTickCount() will return the count of ticks
  // since the Task Scheduler started (i.e. your program starts executing).
  //
  // The tick rate (configTICK_RATE_HZ) is defined in FreeRTOSConfig.h,
  // the default rate is 1000 (1KHz), so one tick is equivalent to 1 ms
  //
  // It is similar to the timer we used before, but you'll
  // need to calculate the time elapsed by taking the difference
  // between curr_tick and prev_tick.
  curr_onoff_tick_time = xTaskGetTickCount();

  // STEP 3
  //
  // Complete the implementation of this task function.
  // It checks whether the virtual StartStop button has been
  // pressed for 2 seconds and needs to set the global flags accordingly
  //
  // Task function should never return so is typically
  // implemented as an infinite loop
  //
  // The vTaskDelay(n) will cause the task to enter Blocked state
  // for n system clock ticks. i.e. the task is unblocked
  // after n systicks and will enter Ready State to be arranged for
  // running
  while (1) {
    curr_onoff_tick_time = xTaskGetTickCount();

    // Check whether the virtual button is pressed.
    //
    // If the virtual button has been pressed for 2 or more seconds,
    // set the global flag to 1 and set the prev_tick to be equal
    // to curr_tick (clear the timer). Otherwise clear the global flag.
    //
    // If the virtual button is not pressed, clear the global flag and
    // set the prev_tick to curr_tick.
 
    
    
    
    if (655 < Touch_ReadX() && Touch_ReadX() < 1312 && 818 < Touch_ReadY() && Touch_ReadY() < 1392) { // replace this condition checking with something else
      if (curr_onoff_tick_time - prev_onoff_tick_time >= 2000) {
        // Set the global flag
        // Clear the timer
        onoff_status = 1;
        prev_onoff_tick_time = curr_onoff_tick_time;
      }
      else {
        // Clear the global flag
        onoff_status = 0;
      }
    } else {
      // Clear the global flag
      // Clear the timer
      onoff_status = 0;
      prev_onoff_tick_time = curr_onoff_tick_time;
    }

    vTaskDelay(1);
  }
}

void Pedestrian(void *p) {
  static int curr_ped_tick_time = 0;
  static int prev_ped_tick_time = 0;
  // STEP 4
  //
  // Complete the implementation of this task function.
  // It checks whether the virtual pedestrian button has been pressed
  // for 2 seconds and update the global flag accordingly.
  //
  // (Refer to instructions in the StartStop function to implement
  // this function.)
  while (1) {
    curr_ped_tick_time = xTaskGetTickCount();
    
    
  if (1513 < Touch_ReadX() && Touch_ReadX() < 1900 && 822 < Touch_ReadY() && Touch_ReadY() < 1349) { // replace this condition checking with something else
      if (curr_ped_tick_time - prev_ped_tick_time >= 2000) {
        // Set the global flag
        // Clear the timer
        pedestrian_status = 1;
        prev_ped_tick_time = curr_ped_tick_time;
      }
      else {
        // Clear the global flag
        pedestrian_status = 0;
      }
    } else {
      // Clear the global flag
      // Clear the timer
      pedestrian_status = 0;
      prev_ped_tick_time = curr_ped_tick_time;
    }
 
    vTaskDelay(1);
  }
}

void Control(void *p) {
  static int curr_light_tick_time = 0;
  static int prev_light_tick_time = 0;

  // STEP 5
  //
  // Complete the implementation of this task function.
  // It represents your Finite State Machine.
  while (1) {
    curr_light_tick_time = xTaskGetTickCount();
    
    // If the one of the virtual lights been lighting up for 5 or more
    // seconds, or if any of the virtual button flags has been set, switch
    // to the corresponding next state and reset the light tick.
    if ((curr_light_tick_time - prev_light_tick_time >= 5000) && x == true) {  // replace this condition checking with something else

      // Reset the light tick
      // Switch to next state
      FSM();
      prev_light_tick_time = curr_light_tick_time;
    }
    if(pedestrian_status == 1 && LA_State == go && x == true){ // to detect whether pedestrian button is pressed
        FSM();// go into finite state machine
        pedestrian_status = 0; // pull down flag
        prev_light_tick_time = curr_light_tick_time; // Clear the timer
        
     }
     
    if(onoff_status == 1 && LA_State == LA_SMStart && x == false){
      FSM();// go into finite state machine
      onoff_status == 0;// pull down flag
      x = true; //change bool 
      prev_light_tick_time = curr_light_tick_time; // Clear the timer
    }else if(onoff_status == 1 && x == true){
      LA_State = LA_end; // turn off system
      FSM(); // go into finite state machine
      x = false; // change bool
      onoff_status == 0; // pull down flag
      prev_light_tick_time = curr_light_tick_time; // Clear the timer
    }
        
    vTaskDelay(1);
  }
}

void FSM(void) {
  // STEP 6
  //
  // Add your FSM implementation here.,
  // This function will be called by the control task function.
  switch(LA_State) {   // Transitions
     case LA_SMStart:  // Initial transition
        LA_State = stop; // Transit to go
        break;

     case go:
       if(pedestrian_status == 1){
         LA_State = warn;
       }else{
        LA_State = stop;// transit to stop
       }
        break;

     case warn:
        LA_State = stop; // transit to stop
        break;
        
     case stop:
         LA_State = go; // transit to go
         break;
     case LA_end: // if the state is LA_end then just break 
        
        break; 
        
     default:
        LA_State = LA_SMStart;
        break;
  } // Transitions

  switch(LA_State) {   // State actions
     case go:
       LCD_DrawFilledRect(40,20,40,40,Color4[0]); // Turn off LED connect to pc6
       LCD_DrawFilledRect(160,20,40,40,Color4[10]);  // Turn on LED connect to pc4
        break;

     case warn:
       LCD_DrawFilledRect(160,20,40,40,Color4[0]); // Turn off LED connect to pc4
       LCD_DrawFilledRect(100,20,40,40,Color4[14]);// Turn on LED connect to pc5
      
        break;
     case stop:
       LCD_DrawFilledRect(160,20,40,40,Color4[0]); // Turn off LED connect to pc4
       LCD_DrawFilledRect(100,20,40,40,Color4[0]);// Turn off LED connect to pc5
       LCD_DrawFilledRect(40,20,40,40,Color4[12]); // Turn off LED connect to pc6
       break;
       
       case LA_end:
         LCD_DrawFilledRect(160,20,40,40,Color4[0]); // Turn off LED connect to pc4
         LCD_DrawFilledRect(100,20,40,40,Color4[0]); // Turn off LED connect to pc5
         LCD_DrawFilledRect(40,20,40,40,Color4[0]); // Turn off LED connect to pc6
         LA_State = LA_SMStart;
         break; 
           
     default:
        break;
   }
  
  
  
  
  
  
  

}
