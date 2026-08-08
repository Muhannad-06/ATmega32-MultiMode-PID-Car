#ifndef LTRACK_CONFIG_H_
#define LTRACK_CONFIG_H_

/* 
 * Configure the DIO Port for the IR Sensor Array
 * Options: DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD
 */
#define LTRACK_PORT          DIO_PORTA

/* Pin Assignment for 5-Channel IR Sensor Array */
#define LTRACK_PIN_FAR_LEFT   DIO_PIN0
#define LTRACK_PIN_LEFT       DIO_PIN1
#define LTRACK_PIN_CENTER     DIO_PIN2
#define LTRACK_PIN_RIGHT      DIO_PIN3
#define LTRACK_PIN_FAR_RIGHT  DIO_PIN4

/* Logic level mapping for line detection (1 = Line detected, 0 = Surface) */
#define LTRACK_BLACK_LINE     1
#define LTRACK_WHITE_SPACE    0

#endif /* LTRACK_CONFIG_H_ */