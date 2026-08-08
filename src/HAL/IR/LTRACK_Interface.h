#ifndef LTRACK_INTERFACE_H_
#define LTRACK_INTERFACE_H_

#include "../../LIBs/STD_TYPES.h"

/* Enum for tracking robot position relative to the line */
typedef enum
{
    LTRACK_CENTERED = 0,
    LTRACK_SLIGHT_LEFT,
    LTRACK_HARD_LEFT,
    LTRACK_SLIGHT_RIGHT,
    LTRACK_HARD_RIGHT,
    LTRACK_STOP_OUT_OF_PATH
} LTRACK_Position_t;

/* Initializes IR sensor array pins as digital inputs */
void LTRACK_voidInit(void);

/* Reads raw bitmask from the 5 IR sensors */
u8 LTRACK_u8ReadSensorsRaw(void);

/* Evaluates sensor readings and returns current path state */
LTRACK_Position_t LTRACK_enumGetLinePosition(void);

#endif /* LTRACK_INTERFACE_H_ */