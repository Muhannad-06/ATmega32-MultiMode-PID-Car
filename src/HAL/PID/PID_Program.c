#include "../../LIBs/STD_TYPES.h" /*[cite: 1] */
#include "../../LIBs/BIT_MATH.h"  /*[cite: 1] */

#include "PID_Config.h"
#include "PID_Private.h"
#include "PID_Interface.h"

/* Global static instance holding the PID memory state */
static PID_State_t Global_PIDState;

void PID_voidInit(void) {
    Global_PIDState.PreviousError = 0.0f;
    Global_PIDState.IntegralSum = 0.0f;
}

static f32 PID_f32CalculatePosition(u8* Copy_pu8SensorReadings) {
    f32 Local_f32Position = 0.0f;
    u8 Local_u8ActiveSensors = 0;

    /* Accumulate weights based on active sensors (assuming 1 means line detected) */
    if (Copy_pu8SensorReadings[0] == 1) { Local_f32Position += SENSOR_0_WEIGHT; Local_u8ActiveSensors++; }
    if (Copy_pu8SensorReadings[1] == 1) { Local_f32Position += SENSOR_1_WEIGHT; Local_u8ActiveSensors++; }
    if (Copy_pu8SensorReadings[2] == 1) { Local_f32Position += SENSOR_2_WEIGHT; Local_u8ActiveSensors++; }
    if (Copy_pu8SensorReadings[3] == 1) { Local_f32Position += SENSOR_3_WEIGHT; Local_u8ActiveSensors++; }
    if (Copy_pu8SensorReadings[4] == 1) { Local_f32Position += SENSOR_4_WEIGHT; Local_u8ActiveSensors++; }

    /* Prevent division by zero if the array loses the line entirely */
    if (Local_u8ActiveSensors == 0) {
        /* A more advanced implementation might return the last known extreme error here. */
        return 0.0f; 
    }

    /* Return weighted average position */
    return (Local_f32Position / (f32)Local_u8ActiveSensors);
}

f32 PID_f32ComputeControlAction(u8* Copy_pu8SensorReadings) {
    /* 1. Calculate current error */
    f32 Local_f32CurrentPosition = PID_f32CalculatePosition(Copy_pu8SensorReadings);
    f32 Local_f32Error = PID_SETPOINT - Local_f32CurrentPosition;

    /* 2. Compute Proportional Term */
    f32 Local_f32P_Term = PID_KP * Local_f32Error;

    /* 3. Compute Integral Term with Anti-Windup */
    Global_PIDState.IntegralSum += Local_f32Error;
    
    if (Global_PIDState.IntegralSum > PID_MAX_INTEGRAL) {
        Global_PIDState.IntegralSum = PID_MAX_INTEGRAL;
    } else if (Global_PIDState.IntegralSum < -PID_MAX_INTEGRAL) {
        Global_PIDState.IntegralSum = -PID_MAX_INTEGRAL;
    }
    
    f32 Local_f32I_Term = PID_KI * Global_PIDState.IntegralSum;

    /* 4. Compute Derivative Term */
    f32 Local_f32Derivative = Local_f32Error - Global_PIDState.PreviousError;
    f32 Local_f32D_Term = PID_KD * Local_f32Derivative;

    /* 5. Save current error for the next iteration */
    Global_PIDState.PreviousError = Local_f32Error;

    /* 6. Calculate and return final output */
    f32 Local_f32Output = Local_f32P_Term + Local_f32I_Term + Local_f32D_Term;

    return Local_f32Output;
}