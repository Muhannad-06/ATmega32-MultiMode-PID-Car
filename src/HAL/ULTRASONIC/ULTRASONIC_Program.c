#include "../../LIBs/STD_TYPES.h"
#include "../../LIBs/BIT_MATH.h"

#include "../DIO/DIO_Interface.h"
#include "../TIMER/TIMER_Interface.h"

#include "ULTRASONIC_Interface.h"
#include "ULTRASONIC_Private.h"
#include "ULTRASONIC_Config.h"

/* Static variables to store pulse high duration time */
static volatile u16 g_u16Time1 = 0;
static volatile u16 g_u16Time2 = 0;
static volatile u8  g_u8Flag   = 0;

void ULTRASONIC_voidInit(void)
{
    /* 1. Configure Trigger pin as Output */
    pinMode(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, DIO_PIN_OUTPUT);
    digitalWrite(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, DIO_PIN_LOW);

    /* 2. Configure Echo pin (PD6 / ICP1) as Input */
    pinMode(ULTRASONIC_ECHO_PORT, ULTRASONIC_ECHO_PIN, DIO_PIN_INPUT);

    /* 3. Initialize Timer1 */
    TIMER1_voidInit();

    /* 4. Set ICU CallBack and edge trigger to Rising Edge initially */
    TIMER1_voidSetCallBackICU(ULTRASONIC_voidICUCallback);
    TIMER1_voidICUSetEdge(TIMER1_ICU_RISING_EDGE);
}

void ULTRASONIC_voidSendTrigger(void)
{
    /* Send a 10us High pulse to trigger the sensor */
    digitalWrite(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, DIO_PIN_HIGH);
    
    /* Delay approximately 10us for system clock F_CPU = 8MHz */
    /* 80 clock cycles = 10us */
    for (volatile u8 i = 0; i < 20; i++)
    {
        __asm__("NOP");
    }
    
    digitalWrite(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, DIO_PIN_LOW);
}

u16 ULTRASONIC_u16GetDistance(void)
{
    u16 Local_u16TimeDistance = 0;
    u16 Local_u16DistanceCM   = 0;

    /* Reset sequence flags */
    g_u8Flag = 0;

    /* Trigger the ultrasonic sensor */
    ULTRASONIC_voidSendTrigger();

    /* Wait for ICU measurement completion flag */
    u32 Local_u32Timeout = 0;
    while ((g_u8Flag < 2) && (Local_u32Timeout < 100000UL))
    {
        Local_u32Timeout++;
    }

    if (g_u8Flag == 2)
    {
        /* Calculate high-level pulse duration */
        Local_u16TimeDistance = g_u16Time2 - g_u16Time1;

        /* 
         * Sound speed = 34300 cm/s
         * F_CPU = 8MHz with Prescaler 64 -> Timer clock = 125 kHz (8us per tick)
         * Distance = (Ticks * 8us * 34300) / (2 * 10^6) = Ticks / 7.29 ≈ Ticks / 7.3
         */
        Local_u16DistanceCM = (u16)((f32)Local_u16TimeDistance / 7.3f);
    }
    else
    {
        /* Timeout occurred or no echo returned */
        Local_u16DistanceCM = 0xFFFF;
    }

    return Local_u16DistanceCM;
}

static void ULTRASONIC_voidICUCallback(void)
{
    if (g_u8Flag == 0)
    {
        /* Capture timestamp on Rising Edge */
        g_u16Time1 = TIMER1_u16ICUGetCapturedValue();
        g_u8Flag = 1;

        /* Switch edge detection to Falling Edge */
        TIMER1_voidICUSetEdge(TIMER1_ICU_FALLING_EDGE);
    }
    else if (g_u8Flag == 1)
    {
        /* Capture timestamp on Falling Edge */
        g_u16Time2 = TIMER1_u16ICUGetCapturedValue();
        g_u8Flag = 2;

        /* Reset edge detection back to Rising Edge for next read */
        TIMER1_voidICUSetEdge(TIMER1_ICU_RISING_EDGE);
    }
}