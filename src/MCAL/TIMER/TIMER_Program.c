#include "../../LIBs/STD_TYPES.h"
#include "../../LIBs/BIT_MATH.h"

#include "TIMER_Interface.h"
#include "TIMER_Private.h"
#include "TIMER_Config.h"

/* Global pointers to functions to hold the callback addresses for ISRs */
static void (*TIMER0_pvCallBackOVF)(void) = NULL;
static void (*TIMER0_pvCallBackCTC)(void) = NULL;

void TIMER0_voidInit(void)
{
    /* 1. Configure Timer Mode */
#if TIMER0_MODE == TIMER0_NORMAL_MODE
    CLEAR_BIT(TCCR0, WGM00);
    CLEAR_BIT(TCCR0, WGM01);

    /* Enable Overflow Interrupt */
    SET_BIT(TIMSK, TOIE0);

#elif TIMER0_MODE == TIMER0_CTC_MODE
    CLEAR_BIT(TCCR0, WGM00);
    SET_BIT(TCCR0, WGM01);

    /* Enable Compare Match Interrupt */
    SET_BIT(TIMSK, OCIE0);

#elif TIMER0_MODE == TIMER0_FAST_PWM_MODE
    SET_BIT(TCCR0, WGM00);
    SET_BIT(TCCR0, WGM01);

    /* Set Default PWM Behavior: Clear OC0 on compare match, set at BOTTOM */
    CLEAR_BIT(TCCR0, COM00);
    SET_BIT(TCCR0, COM01);

#elif TIMER0_MODE == TIMER0_PHASE_PWM_MODE
    SET_BIT(TCCR0, WGM00);
    CLEAR_BIT(TCCR0, WGM01);

    /* Set Default PWM Behavior: Clear OC0 on compare match when up-counting */
    CLEAR_BIT(TCCR0, COM00);
    SET_BIT(TCCR0, COM01);
#endif

    /* 2. Configure Clock & Prescaler */
    /* Clear the prescaler bits first */
    TCCR0 &= 0xF8;

    /* Set the new prescaler value */
    TCCR0 |= TIMER0_PRESCALER;
}

void TIMER0_voidSetPreload(u8 Copy_u8Preload)
{
    TCNT0 = Copy_u8Preload;
}

void TIMER0_voidSetCompareMatch(u8 Copy_u8CompareValue)
{
    OCR0 = Copy_u8CompareValue;
}

void TIMER0_voidSetCallBackOVF(void (*Copy_pvCallBackFunc)(void))
{
    if (Copy_pvCallBackFunc != NULL)
    {
        TIMER0_pvCallBackOVF = Copy_pvCallBackFunc;
    }
}

void TIMER0_voidSetCallBackCTC(void (*Copy_pvCallBackFunc)(void))
{
    if (Copy_pvCallBackFunc != NULL)
    {
        TIMER0_pvCallBackCTC = Copy_pvCallBackFunc;
    }
}

/* ==================================================================== */
/*                      Interrupt Service Routines                      */
/* ==================================================================== */

/* Timer0 Overflow ISR (Vector 11) */
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
    if (TIMER0_pvCallBackOVF != NULL)
    {
        TIMER0_pvCallBackOVF();
    }
}

/* Timer0 Compare Match ISR (Vector 10) */
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
    if (TIMER0_pvCallBackCTC != NULL)
    {
        TIMER0_pvCallBackCTC();
    }
}
