#ifndef SERVO_PRIVATE_H
#define SERVO_PRIVATE_H

/* Servo Motor physical constraints */
#define SERVO_MIN_ANGLE     0
#define SERVO_MAX_ANGLE     180

/* Internal macro to map angles to PWM duty cycles or DIO delay times (Software PWM) */
#define SERVO_CALC_PULSE(angle)  ( ((angle) * 1000UL / 180UL) + 1000UL ) 

#endif /* SERVO_PRIVATE_H */