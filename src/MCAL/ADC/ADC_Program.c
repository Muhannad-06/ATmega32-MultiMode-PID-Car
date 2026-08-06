#include "../../LIBs/STD_TYPES.h"
#include "../../LIBs/BIT_MATH.h"

#include <util/delay.h>

#include "../DIO/DIO_Interface.h"
#include "ADC_Interface.h"
#include "ADC_Private.h"
#include "ADC_Config.h"

u8  ADC_u8BusyFlag = NOTBUSY;
u16 ADC_u16Result;

void (*ADC_pvNotificationFUNC)(void) = NULL;

void ADC_voidInit()
{
    pinMode(DIO_PORTA, DIO_PIN7,DIO_PIN_INPUT);
   
    #if         ADC_REFVOLT == ADC_AREF
            CLEAR_BIT(ADC_ADMUX_REG, ADC_ADMUX_pinREFS0);
            CLEAR_BIT(ADC_ADMUX_REG, ADC_ADMUX_pinREFS1);
    #elif       ADC_REFVOLT == ADC_AVCC
              SET_BIT(ADC_ADMUX_REG, ADC_ADMUX_pinREFS0);
            CLEAR_BIT(ADC_ADMUX_REG, ADC_ADMUX_pinREFS1);
    #elif       ADC_REFVOLT == ADC_INTERNAL
            SET_BIT(ADC_ADMUX_REG, ADC_ADMUX_pinREFS0);
            SET_BIT(ADC_ADMUX_REG, ADC_ADMUX_pinREFS1);
    #else   
        #error "Error In ADC_REFVOLT Configuration"
    #endif

    #if         ADC_ADJUST_CTRL == ADC_LEFT
            SET_BIT(ADC_ADMUX_REG, ADC_ADMUX_pinADLAR);
    #elif       ADC_ADJUST_CTRL == ADC_RIGHT
            CLEAR_BIT(ADC_ADMUX_REG, ADC_ADMUX_pinADLAR);
    #else
        #error "Error In ADC_ADJUST_CTRL Configuration"
    #endif

    ADC_ADCSRA_REG &= ADC_PRES_MASK;
    ADC_ADCSRA_REG |= ADC_PRESCALAR_by128;

    SET_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_pinADEN);

}

u16 ADC_u16ReadSynchronus(u8 Copy_u8ChannelNum)
{
    if(ADC_u8BusyFlag == BUSY)
    {
        return BUSY;
    }
    else
    {
            ADC_u8BusyFlag = BUSY;

        
        ADC_ADMUX_REG &= ADC_CHANNEL_MASK;
        ADC_ADMUX_REG |= Copy_u8ChannelNum;

        SET_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_pinADSC);
        
        while ( READ_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_pinADIF) == 0 )
        {
            /* Do Nothing Until It's 1 */
        }

        SET_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_pinADIF);
        _delay_us(10);

        ADC_u8BusyFlag = NOTBUSY;
        
    }

    return ADC_ADC_REG;
}


u16 ADC_u16ReadAsynchronus(u8 Copy_u8ChannelNum, void (*pvCallBackFuncPtr)(void))
{
   if((ADC_u8BusyFlag == BUSY) || (pvCallBackFuncPtr == NULL))
	{
		return 0;
	}
	else
	{
		ADC_u8BusyFlag = BUSY;
		
		ADC_ADMUX_REG &= ADC_CHANNEL_MASK;
		ADC_ADMUX_REG |= Copy_u8ChannelNum;
		
		ADC_pvNotificationFUNC = pvCallBackFuncPtr;
		
		SET_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_pinADSC);
		
		SET_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_pinADIE);
		return ADC_u16Result;

	}
}
/*************************************************************************/

void __vector_16 (void)     __attribute__((signal));
void __vector_16 (void)
{
	ADC_u16Result = ADC_ADC_REG;
	
	ADC_u8BusyFlag = NOTBUSY;
	ADC_pvNotificationFUNC();
	CLEAR_BIT(ADC_ADCSRA_REG, ADC_ADCSRA_pinADIE);
}
