#ifndef PRIVATE_H
#define PRIVATE_H

#include "../../LIBs/STD_TYPES.h"

/* === INTERNAL STATE STRUCTURES === */
typedef struct {
    u8 current_angle;
    u8 sweep_direction; /* 1 for incrementing angle, 0 for decrementing */
} ServoState_t;

/* === PRIVATE MACROS === */
/* Calculates distance in cm based on echo duration in microseconds */
#define CALCULATE_DISTANCE_CM(duration_us) ((duration_us) / SPEED_OF_SOUND_DIVISOR)

/* === PRIVATE FUNCTION DECLARATIONS === */
/* Private helper to send a 10us trigger pulse to the ultrasonic sensor */
static inline void trigger_ultrasonic(void);

/* Private helper to measure the duration of the echo pulse */
static inline u16 measure_echo_time_us(void);

/* Private helper to update the servo motor PWM signal based on angle */
static inline void set_servo_angle(u8 angle_deg);

/* Private helper to manage the sweeping logic of the servo */
static inline void update_servo_sweep(void);

#endif /* PRIVATE_H */