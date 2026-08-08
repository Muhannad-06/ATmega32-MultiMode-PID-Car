#ifndef PID_CONFIG_H
#define PID_CONFIG_H

/* Proportional, Integral, and Derivative Tuning Constants */
#define PID_KP  5.0
#define PID_KI  0.1
#define PID_KD  1.5

/* Target position for the 5-IR sensor array (0.0 implies the line is dead center) */
#define PID_SETPOINT 0.0

/* Maximum limit for the integral term to prevent integral windup */
#define PID_MAX_INTEGRAL 100.0

#endif