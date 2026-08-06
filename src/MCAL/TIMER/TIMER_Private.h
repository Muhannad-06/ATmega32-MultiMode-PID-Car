#ifndef TIMER_PRIVATE_H
#define TIMER_PRIVATE_H

/* Timer 0 Registers */
#define TCCR0       *((volatile u8*)0x53)
#define TCNT0       *((volatile u8*)0x52)
#define OCR0        *((volatile u8*)0x5C)
#define TIMSK       *((volatile u8*)0x59)
#define TIFR        *((volatile u8*)0x58)

/* TCCR0 Bits */
#define FOC0        7
#define WGM00       6
#define COM01       5
#define COM00       4
#define WGM01       3
#define CS02        2
#define CS01        1
#define CS00        0

/* TIMSK Bits */
#define OCIE2       7
#define TOIE2       6
#define TICIE1      5
#define OCIE1A      4
#define OCIE1B      3
#define TOIE1       2
#define OCIE0       1
#define TOIE0       0

/* Timer0 Modes */
#define TIMER0_NORMAL_MODE          1
#define TIMER0_PHASE_PWM_MODE       2
#define TIMER0_CTC_MODE             3
#define TIMER0_FAST_PWM_MODE        4

/* Timer0 Prescaler Options */
#define TIMER0_NO_CLOCK             0
#define TIMER0_PRESCALER_1          1
#define TIMER0_PRESCALER_8          2
#define TIMER0_PRESCALER_64         3
#define TIMER0_PRESCALER_256        4
#define TIMER0_PRESCALER_1024       5

#endif /* TIMER_PRIVATE_H */
