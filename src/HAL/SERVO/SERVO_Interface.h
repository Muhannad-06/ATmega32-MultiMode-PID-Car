#ifndef SERVO_INTERFACE_H
#define SERVO_INTERFACE_H

#include "../../LIBs/STD_TYPES.h"

void SERVO_voidInit(void);


void SERVO_voidSetAngle(u8 Copy_u8Angle);


void SERVO_voidObstacleAvoidanceSweep(void);

#endif /* SERVO_INTERFACE_H */