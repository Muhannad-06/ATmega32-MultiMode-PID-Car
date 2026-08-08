#ifndef OBSTACLE_AVOIDER_CONFIG_H
#define OBSTACLE_AVOIDER_CONFIG_H

/* === HARDWARE PIN CONFIGURATION === */
/* Assumes standard DIO ports: 0=PORTA, 1=PORTB, 2=PORTC, 3=PORTD */
#define ULTRASONIC_TRIG_PORT    0  
#define ULTRASONIC_TRIG_PIN     0  

#define ULTRASONIC_ECHO_PORT    0  
#define ULTRASONIC_ECHO_PIN     1  

#define SERVO_PORT              1  
#define SERVO_PIN               3  

/* === OBSTACLE DETECTION THRESHOLDS === */
#define OBSTACLE_THRESHOLD_CM   20
#define SENSOR_TIMEOUT_US       30000UL /* ~500cm max distance */
#define SPEED_OF_SOUND_DIVISOR  58      /* us to cm conversion factor */

/* === SERVO SWEEP PARAMETERS === */
#define SERVO_MIN_ANGLE_DEG     0
#define SERVO_MAX_ANGLE_DEG     180
#define SERVO_SWEEP_STEP_DEG    15
#define SERVO_DELAY_MS          50

/* === DIO DIRECTION MACROS === */
#define DIO_DIRECTION_INPUT     0
#define DIO_DIRECTION_OUTPUT    1
#define DIO_VALUE_LOW           0
#define DIO_VALUE_HIGH          1

#endif /* OBSTACLE_AVOIDER_CONFIG_H */