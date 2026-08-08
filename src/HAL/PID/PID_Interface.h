#ifndef PID_INTERFACE_H
#define PID_INTERFACE_H

/* 
 * Function: PID_voidInit
 * Description: Initializes or resets the internal state of the PID controller.
 */
void PID_voidInit(void);

/* 
 * Function: PID_f32ComputeControlAction
 * Description: Computes the PID output based on the current 5-sensor array readings.
 * Parameters:  Copy_pu8SensorReadings - Array of 5 elements (0 or 1) representing IR states.
 * Returns:     The calculated control action (f32) to be applied to the actuators.
 */
f32 PID_f32ComputeControlAction(u8* Copy_pu8SensorReadings);

#endif