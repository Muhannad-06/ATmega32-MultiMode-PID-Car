#ifndef PID_PRIVATE_H
#define PID_PRIVATE_H

/* Internal state tracking variables for the PID controller */
typedef struct {
    f32 PreviousError;
    f32 IntegralSum;
} PID_State_t;

/* 
 * Sensor weights for position calculation.
 * Far left is highly negative, center is 0, far right is highly positive. 
 */
#define SENSOR_0_WEIGHT -20.0
#define SENSOR_1_WEIGHT -10.0
#define SENSOR_2_WEIGHT   0.0
#define SENSOR_3_WEIGHT  10.0
#define SENSOR_4_WEIGHT  20.0

/* Helper function to compute the weighted average position of the line */
static f32 PID_f32CalculatePosition(u8* Copy_pu8SensorReadings);

#endif