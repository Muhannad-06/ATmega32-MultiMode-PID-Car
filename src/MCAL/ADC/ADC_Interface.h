#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#define ADC_PRESCALAR_by2           1
#define ADC_PRESCALAR_by4           2
#define ADC_PRESCALAR_by8           3
#define ADC_PRESCALAR_by16          4
#define ADC_PRESCALAR_by32          5
#define ADC_PRESCALAR_by64          6
#define ADC_PRESCALAR_by128         7

/*  ADC Always PORT A */
#define ADC_CHANNEL_0               DIO_PIN0
#define ADC_CHANNEL_1               DIO_PIN1
#define ADC_CHANNEL_2               DIO_PIN2
#define ADC_CHANNEL_3               DIO_PIN3
#define ADC_CHANNEL_4               DIO_PIN4
#define ADC_CHANNEL_5               DIO_PIN5
#define ADC_CHANNEL_6               DIO_PIN6
#define ADC_CHANNEL_7               DIO_PIN7


void ADC_voidInit();

/* THIS FUNV READS A SPECIFIC ADC CHANNEL*/
u16 ADC_u16ReadSynchronus(u8 Copy_u8ChannelNum);

/*  This FUNC READS A SPECIFIC ADC CHANNEL
    Copy_u8ChannelNum: 0 ----> 7
    *pvCallBackFuncPtr: Address of the Functioin to be Executed */
u16 ADC_u16ReadAsynchronus(u8 Copy_u8ChannelNum, void (*pvCallBackFuncPtr)(void));

#endif /*ADC_INTERFACE_H*/
