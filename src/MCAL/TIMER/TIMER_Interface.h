#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

#include "../../LIBs/STD_TYPES.h"

/*
 * Function   : TIMER0_voidInit
 * Description: Initializes Timer0 based on the configurations in TIMER_Config.h
 */
void TIMER0_voidInit(void);

/*
 * Function   : TIMER0_voidSetPreload
 * Description: Sets the initial value for the timer in Normal mode.
 */
void TIMER0_voidSetPreload(u8 Copy_u8Preload);

/*
 * Function   : TIMER0_voidSetCompareMatch
 * Description: Sets the compare match value (OCR0) for CTC or PWM modes.
 */
void TIMER0_voidSetCompareMatch(u8 Copy_u8CompareValue);

/*
 * Function   : TIMER0_voidSetCallBackOVF
 * Description: Assigns the application function to be executed when an Overflow Interrupt occurs.
 */
void TIMER0_voidSetCallBackOVF(void (*Copy_pvCallBackFunc)(void));

/*
 * Function   : TIMER0_voidSetCallBackCTC
 * Description: Assigns the application function to be executed when a Compare Match Interrupt occurs.
 */
void TIMER0_voidSetCallBackCTC(void (*Copy_pvCallBackFunc)(void));

#endif /* TIMER_INTERFACE_H */
