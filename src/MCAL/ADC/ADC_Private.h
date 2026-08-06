#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H


/* ADUMX Register */
#define ADC_ADMUX_REG         *((volatile u8*) 0x27)

#define ADC_ADMUX_pinMUX0               0
#define ADC_ADMUX_pinMUX1               1            
#define ADC_ADMUX_pinMUX2               2            
#define ADC_ADMUX_pinMUX3               3            
#define ADC_ADMUX_pinMUX4               4            
#define ADC_ADMUX_pinADLAR              5            
#define ADC_ADMUX_pinREFS0              6            
#define ADC_ADMUX_pinREFS1              7

/* ADCSRA Register*/
#define ADC_ADCSRA_REG         *((volatile u8*) 0x26)

#define ADC_ADCSRA_pinADPS0               0
#define ADC_ADCSRA_pinADSP1               1            
#define ADC_ADCSRA_pinADSP2               2            
#define ADC_ADCSRA_pinADIE                3            
#define ADC_ADCSRA_pinADIF                4            
#define ADC_ADCSRA_pinADATE               5            
#define ADC_ADCSRA_pinADSC                6            
#define ADC_ADCSRA_pinADEN                7

/* ADCH Register*/
#define ADC_ADCH_REG         *((volatile u8*) 0x25)

/* ADCL Register*/
#define ADC_ADCL_REG         *((volatile u8*) 0x24)

/****** A Short Cut To ACCESS THE ADC's 10 bits AT ONCE ******/
#define ADC_ADC_REG          *((volatile u16*) 0x24)

/* Private Macros Used In Configration */
#define ADC_AREF                  0
#define ADC_AVCC                  1
#define ADC_INTERNAL              2

#define ADC_RIGHT                 0
#define ADC_LEFT                  1

#define ADC_PRES_MASK          0b11111000
#define ADC_CHANNEL_MASK       0b11100000


#define    NOTBUSY          0
#define    BUSY             1



#endif /*ADC_PRIVATE_H*/