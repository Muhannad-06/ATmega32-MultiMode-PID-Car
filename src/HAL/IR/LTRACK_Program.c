#include "../../LIBs/STD_TYPES.h"
#include "../../LIBs/BIT_MATH.h"

#include "../DIO/DIO_Interface.h"

#include "LTRACK_Interface.h"
#include "LTRACK_Private.h"
#include "LTRACK_Config.h"

void LTRACK_voidInit(void)
{
    /* Configure all IR sensor pins as Digital Inputs */
    pinMode(LTRACK_PORT, LTRACK_PIN_FAR_LEFT, DIO_PIN_INPUT);
    pinMode(LTRACK_PORT, LTRACK_PIN_LEFT,     DIO_PIN_INPUT);
    pinMode(LTRACK_PORT, LTRACK_PIN_CENTER,   DIO_PIN_INPUT);
    pinMode(LTRACK_PORT, LTRACK_PIN_RIGHT,    DIO_PIN_INPUT);
    pinMode(LTRACK_PORT, LTRACK_PIN_FAR_RIGHT, DIO_PIN_INPUT);
}

u8 LTRACK_u8ReadSensorsRaw(void)
{
    u8 Local_u8SensorValues = 0;
    u8 Local_u8PinState = 0;

    /* Read Far Left Sensor */
    digitalRead(LTRACK_PORT, LTRACK_PIN_FAR_LEFT, &Local_u8PinState);
    if(Local_u8PinState == LTRACK_BLACK_LINE) SET_BIT(Local_u8SensorValues, 0);

    /* Read Left Sensor */
    digitalRead(LTRACK_PORT, LTRACK_PIN_LEFT, &Local_u8PinState);
    if(Local_u8PinState == LTRACK_BLACK_LINE) SET_BIT(Local_u8SensorValues, 1);

    /* Read Center Sensor */
    digitalRead(LTRACK_PORT, LTRACK_PIN_CENTER, &Local_u8PinState);
    if(Local_u8PinState == LTRACK_BLACK_LINE) SET_BIT(Local_u8SensorValues, 2);

    /* Read Right Sensor */
    digitalRead(LTRACK_PORT, LTRACK_PIN_RIGHT, &Local_u8PinState);
    if(Local_u8PinState == LTRACK_BLACK_LINE) SET_BIT(Local_u8SensorValues, 3);

    /* Read Far Right Sensor */
    digitalRead(LTRACK_PORT, LTRACK_PIN_FAR_RIGHT, &Local_u8PinState);
    if(Local_u8PinState == LTRACK_BLACK_LINE) SET_BIT(Local_u8SensorValues, 4);

    return Local_u8SensorValues;
}

LTRACK_Position_t LTRACK_enumGetLinePosition(void)
{
    u8 Local_u8Raw = LTRACK_u8ReadSensorsRaw();
    LTRACK_Position_t Local_enumPosition = LTRACK_STOP_OUT_OF_PATH;

    switch (Local_u8Raw)
    {
        /* Line is aligned in center: 00100 */
        case 0x04:
            Local_enumPosition = LTRACK_CENTERED;
            break;

        /* Slight deviation to the left: 01100 or 01000 */
        case 0x0C:
        case 0x08:
            Local_enumPosition = LTRACK_SLIGHT_LEFT;
            break;

        /* Sharp deviation to the left: 11000 or 10000 */
        case 0x18:
        case 0x10:
            Local_enumPosition = LTRACK_HARD_LEFT;
            break;

        /* Slight deviation to the right: 00110 or 00010 */
        case 0x06:
        case 0x02:
            Local_enumPosition = LTRACK_SLIGHT_RIGHT;
            break;

        /* Sharp deviation to the right: 00011 or 00001 */
        case 0x03:
        case 0x01:
            Local_enumPosition = LTRACK_HARD_RIGHT;
            break;

        default:
            Local_enumPosition = LTRACK_STOP_OUT_OF_PATH;
            break;
    }

    return Local_enumPosition;
}