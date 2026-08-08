#ifndef SERVO_CONFIG_H
#define SERVO_CONFIG_H

/* 
 * Define the DIO Port and Pin connected to the Servo Motor's signal line.
 * Adjust these based on your specific microcontroller pinout.
 */
#define SERVO_PORT          DIO_PORTA  
#define SERVO_PIN           DIO_PIN0   

/* 
 * Define the default starting angle for the servo.
 */
#define SERVO_DEFAULT_ANGLE 90

#endif /* SERVO_CONFIG_H */