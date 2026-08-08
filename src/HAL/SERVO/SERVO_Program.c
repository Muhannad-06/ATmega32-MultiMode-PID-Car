#include "../../LIBs/STD_TYPES.h"
#include "../../LIBs/BIT_MATH.h"

/* MCAL Layer Inclusions */
#include "../../MCAL/DIO/DIO_Interface.h"

/* HAL Layer Inclusions */
#include "../../HAL/obstacle avoider/obstacle_avoider_Interface.h"

/* Servo Driver Inclusions */
#include "SERVO_Interface.h"
#include "SERVO_Config.h"
#include "SERVO_Private.h"

void SERVO_voidInit(void)
{
    /* Set the configured servo pin as an output using the DIO module */
    DIO_voidSetPinDirection(SERVO_PORT, SERVO_PIN, DIO_PIN_OUTPUT);
    
    /* Initialize the servo to its default forward-facing angle */
    SERVO_voidSetAngle(SERVO_DEFAULT_ANGLE);
}

void SERVO_voidSetAngle(u8 Copy_u8Angle)
{
    if (Copy_u8Angle > SERVO_MAX_ANGLE)
    {
        Copy_u8Angle = SERVO_MAX_ANGLE; /* Clamp to maximum */
    }
    
    /* 
     * Note: In a hardware PWM setup, you would pass Copy_u8Angle to a Timer module here.
     * Since we are focusing on DIO functionality, this is a conceptual placeholder for 
     * a Software PWM implementation using DIO toggling and delays.
     */
     
    u32 Local_u32PulseWidth = SERVO_CALC_PULSE(Copy_u8Angle);
    
    /* Software PWM execution (Conceptual via DIO) */
    DIO_voidSetPinValue(SERVO_PORT, SERVO_PIN, DIO_PIN_HIGH);
    /* _delay_us(Local_u32PulseWidth); */
    
    DIO_voidSetPinValue(SERVO_PORT, SERVO_PIN, DIO_PIN_LOW);
    /* _delay_us(20000 - Local_u32PulseWidth); */
}

void SERVO_voidObstacleAvoidanceSweep(void)
{
    u8 Local_u8ObstacleStatus = 0;
    
    /* Read the status from the obstacle avoider sensor */
    Local_u8ObstacleStatus = OBSTACLE_AVOIDER_u8GetStatus(); 
    
    if (Local_u8ObstacleStatus == 1 /* Assuming 1 means Obstacle Detected */)
    {
        /* Look left */
        SERVO_voidSetAngle(180);
        /* Add delay to allow physical movement */
        
        /* Check if path is clear, else look right */
        if (OBSTACLE_AVOIDER_u8GetStatus() == 1)
        {
            SERVO_voidSetAngle(0);
        }
    }
    else
    {
        /* Path is clear, look straight ahead */
        SERVO_voidSetAngle(SERVO_DEFAULT_ANGLE);
    }
}