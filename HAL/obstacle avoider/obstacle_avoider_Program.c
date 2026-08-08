#include "../../LIBs/STD_TYPES.h"
#include "../../LIBs/BIT_MATH.h"

/* Include MCAL layer dependencies[cite: 1] */
#include "../../MCAL/DIO/DIO_Interface.h"

#include "obstacle_avoider_Config.h"
#include "obstacle_avoider_Interface.h"
#include "obstacle_avoider_Private.h"

/* 
 * NOTE: Assumes existence of a basic TIMER_Interface.h providing 
 * microsecond delays and time-tracking for the blocking echo read,
 * as well as PWM for the servo. Placeholders are used here.
 */
extern void TIMER_voidSetDelayUS(u32 microseconds);
extern void TIMER_voidSetDelayMS(u32 milliseconds);
extern u32  TIMER_u32GetMicros(void);
extern void TIMER_voidSetPWM(u8 pin, u8 duty_cycle);

/* === GLOBAL PRIVATE STATE === */
static ServoState_t gs_servo_state = {SERVO_MIN_ANGLE_DEG, 1};

/* === PRIVATE FUNCTION IMPLEMENTATIONS === */

static inline void trigger_ultrasonic(void) {
    /* Send a 10 microsecond HIGH pulse to the trigger pin */
    DIO_u8SetPinValue(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, DIO_VALUE_HIGH);
    TIMER_voidSetDelayUS(10);
    DIO_u8SetPinValue(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, DIO_VALUE_LOW);
}

static inline u16 measure_echo_time_us(void) {
    u32 start_time;
    u32 duration = 0;
    u8 pin_state = DIO_VALUE_LOW;

    /* Wait for echo pin to go HIGH (start of pulse) */
    u32 timeout_start = TIMER_u32GetMicros();
    do {
        DIO_u8GetPinValue(ULTRASONIC_ECHO_PORT, ULTRASONIC_ECHO_PIN, &pin_state);
        if ((TIMER_u32GetMicros() - timeout_start) > SENSOR_TIMEOUT_US) {
            return 0; /* Timeout waiting for pulse start */
        }
    } while (pin_state == DIO_VALUE_LOW);

    start_time = TIMER_u32GetMicros();

    /* Wait for echo pin to go LOW (end of pulse) */
    do {
        DIO_u8GetPinValue(ULTRASONIC_ECHO_PORT, ULTRASONIC_ECHO_PIN, &pin_state);
        duration = TIMER_u32GetMicros() - start_time;
        if (duration > SENSOR_TIMEOUT_US) {
            return 0; /* Timeout waiting for pulse end */
        }
    } while (pin_state == DIO_VALUE_HIGH);

    return (u16)duration;
}

static inline void set_servo_angle(u8 angle_deg) {
    /* Convert angle (0-180) to appropriate PWM duty cycle.
       Specific mapping depends on the servo and timer config.
       Assuming a generic mapping function here. */
    u8 duty = 5 + (angle_deg * 5 / 180); /* Example: 5% to 10% duty cycle for 1ms to 2ms pulse */
    TIMER_voidSetPWM(SERVO_PIN, duty);
}

static inline void update_servo_sweep(void) {
    if (gs_servo_state.sweep_direction == 1) {
        gs_servo_state.current_angle += SERVO_SWEEP_STEP_DEG;
        if (gs_servo_state.current_angle >= SERVO_MAX_ANGLE_DEG) {
            gs_servo_state.current_angle = SERVO_MAX_ANGLE_DEG;
            gs_servo_state.sweep_direction = 0; /* Reverse direction */
        }
    } else {
        if (gs_servo_state.current_angle <= SERVO_MIN_ANGLE_DEG + SERVO_SWEEP_STEP_DEG) {
            gs_servo_state.current_angle = SERVO_MIN_ANGLE_DEG;
            gs_servo_state.sweep_direction = 1; /* Reverse direction */
        } else {
            gs_servo_state.current_angle -= SERVO_SWEEP_STEP_DEG;
        }
    }
    
    set_servo_angle(gs_servo_state.current_angle);
    TIMER_voidSetDelayMS(SERVO_DELAY_MS); /* Give servo time to reach position */
}

/* === PUBLIC API IMPLEMENTATIONS === */

void obstacle_avoidance_init(void) {
    /* Initialize Ultrasonic Pins using existing MCAL DIO driver */
    DIO_u8SetPinDirection(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, DIO_DIRECTION_OUTPUT);
    DIO_u8SetPinDirection(ULTRASONIC_ECHO_PORT, ULTRASONIC_ECHO_PIN, DIO_DIRECTION_INPUT);
    
    /* Ensure trigger is initially LOW */
    DIO_u8SetPinValue(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, DIO_VALUE_LOW);
    
    /* Initialize Servo PWM Pin */
    DIO_u8SetPinDirection(SERVO_PORT, SERVO_PIN, DIO_DIRECTION_OUTPUT);
    
    /* Set initial servo position */
    gs_servo_state.current_angle = SERVO_MIN_ANGLE_DEG;
    set_servo_angle(gs_servo_state.current_angle);
    TIMER_voidSetDelayMS(500); /* Wait for servo to center on boot */
}

ObstacleInfo_t obstacle_avoidance_read(void) {
    ObstacleInfo_t result;
    u16 echo_duration = 0;
    
    /* 1. Sweep Servo to next position */
    update_servo_sweep();
    
    /* 2. Trigger sensor */
    trigger_ultrasonic();
    
    /* 3. Read echo duration */
    echo_duration = measure_echo_time_us();
    
    /* 4. Process Reading */
    if (echo_duration == 0) {
        /* Timeout or error - assume clear path up to max range */
        result.distance_cm = 999; 
    } else {
        result.distance_cm = CALCULATE_DISTANCE_CM(echo_duration);
    }
    
    result.angle_deg = gs_servo_state.current_angle;
    
    /* 5. Determine if distance falls below the safety threshold */
    if (result.distance_cm <= OBSTACLE_THRESHOLD_CM) {
        result.obstacle_detected = 1;
    } else {
        result.obstacle_detected = 0;
    }
    
    return result;
}