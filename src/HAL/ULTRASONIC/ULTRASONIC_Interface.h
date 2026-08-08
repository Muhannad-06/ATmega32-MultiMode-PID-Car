#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_

#include "../../LIBs/STD_TYPES.h"

/* Initializes the Ultrasonic Trigger pin and Timer1 ICU setup */
void ULTRASONIC_voidInit(void);

/* Sends a 10us pulse on Trigger pin to start measurement */
void ULTRASONIC_voidSendTrigger(void);

/* Reads distance in centimeters using non-blocking ICU */
u16 ULTRASONIC_u16GetDistance(void);

#endif /* ULTRASONIC_INTERFACE_H_ */
