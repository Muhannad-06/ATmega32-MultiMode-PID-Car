#ifndef OBSTACLE_AVOIDER_INTERFACE_H
#define OBSTACLE_AVOIDER_INTERFACE_H

#include "../../LIBs/STD_TYPES.h"

/* === PUBLIC DATA STRUCTURES === */
typedef struct {
    u16 distance_cm;       /* Measured distance in centimeters */
    u8 angle_deg;          /* Angle at which the measurement was taken */
    u8 obstacle_detected;  /* 1 if distance < OBSTACLE_THRESHOLD_CM, 0 otherwise */
} ObstacleInfo_t;

/* === PUBLIC API DECLARATIONS === */

/**
 * @brief Initializes the obstacle avoidance system.
 *        Configures DIO pins for the ultrasonic sensor and servo motor.
 */
void obstacle_avoidance_init(void);

/**
 * @brief Sweeps the servo, triggers the ultrasonic sensor, and reads the distance.
 * @return ObstacleInfo_t Struct containing the current distance, angle, and detection status.
 */
ObstacleInfo_t obstacle_avoidance_read(void);

#endif /* OBSTACLE_AVOIDER_INTERFACE_H */