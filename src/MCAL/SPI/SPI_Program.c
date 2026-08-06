#include "../../LIBs/STD_TYPES.h"
#include "../../LIBs/BIT_MATH.h"

#include "../DIO/DIO_Interface.h"

#include "SPI_Interface.h"
#include "SPI_Private.h"
#include "SPI_Config.h"


void SPI_voidMasterInit()
{
    /* Configure SPI pin directions */
    pinMode(DIO_PORTB, DIO_PIN4, DIO_PIN_OUTPUT); /* SS   - must be output in master mode */
    pinMode(DIO_PORTB, DIO_PIN5, DIO_PIN_OUTPUT); /* MOSI */
    pinMode(DIO_PORTB, DIO_PIN6, DIO_PIN_INPUT);  /* MISO */
    pinMode(DIO_PORTB, DIO_PIN7, DIO_PIN_OUTPUT); /* SCK  */

    /* Set The Node Be Master Node */
    SET_BIT(SPI_SPCR_REG, SPI_SPCR_MSTR);
    /* Set The MSB to Be Sent First*/
    CLEAR_BIT(SPI_SPCR_REG, SPI_SPCR_DORD);
    /* SET The Leading Edge As Rising Edge*/
    CLEAR_BIT(SPI_SPCR_REG, SPI_SPCR_CPOL);
    /* Sample At Leading Edge*/
    CLEAR_BIT(SPI_SPCR_REG, SPI_SPCR_CPHA);
    /* Clock Prescaller, Divided By 16 */
    SET_BIT(SPI_SPCR_REG, SPI_SPCR_SPR0);
    CLEAR_BIT(SPI_SPCR_REG, SPI_SPCR_SPR1);
    CLEAR_BIT(SPI_SPSR_REG, SPI_SPSR_SPI2X);
    /* Enable The SPI */
    SET_BIT(SPI_SPCR_REG, SPI_SPCR_SPE);

}

void SPI_voidSlaveInit()
{
    /* Configure SPI pin directions */
    pinMode(DIO_PORTB, DIO_PIN4, DIO_PIN_INPUT);  /* SS   */
    pinMode(DIO_PORTB, DIO_PIN5, DIO_PIN_INPUT);  /* MOSI */
    pinMode(DIO_PORTB, DIO_PIN6, DIO_PIN_OUTPUT); /* MISO - must be output in slave mode */
    pinMode(DIO_PORTB, DIO_PIN7, DIO_PIN_INPUT);  /* SCK  */

    /* Set The Node Be Slave Node */
    CLEAR_BIT(SPI_SPCR_REG, SPI_SPCR_MSTR);
    /* Set The MSB to Be Sent First*/
    CLEAR_BIT(SPI_SPCR_REG, SPI_SPCR_DORD);
    /* SET The Leading Edge As Rising Edge*/
    CLEAR_BIT(SPI_SPCR_REG, SPI_SPCR_CPOL);
    /* Sample At Leading Edge*/
    CLEAR_BIT(SPI_SPCR_REG, SPI_SPCR_CPHA);
    /* Enable The SPI */
    SET_BIT(SPI_SPCR_REG, SPI_SPCR_SPE);
}

u8 SPI_u8Tranceive(u8 Copy_u8Data)
{
    SPI_SPDR_REG = Copy_u8Data;
    while (READ_BIT(SPI_SPSR_REG, SPI_SPSR_SPIF) == 0)
    {
        /* Wait until transmission complete */
    }
    return SPI_SPDR_REG;
}
