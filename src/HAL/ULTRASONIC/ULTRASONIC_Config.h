#ifndef ULTRASONIC_CONFIG_H_
#define ULTRASONIC_CONFIG_H_

/* 
 * Trigger Pin Configuration
 * Choose any available GPIO port and pin
 */
#define ULTRASONIC_TRIG_PORT    DIO_PORTC
#define ULTRASONIC_TRIG_PIN     DIO_PIN0

/* 
 * Echo Pin is fixed to ATmega32 ICP1 Pin (PORTD - PIN6)
 * as it is managed by Timer1 Input Capture Unit
 */
#define ULTRASONIC_ECHO_PORT    DIO_PORTD
#define ULTRASONIC_ECHO_PIN     DIO_PIN6

#endif /* ULTRASONIC_CONFIG_H_ */