/*
* main.c
*
*  Created on: Aug 30, 2025
*      Author: YOUSEFS
*/

#include "STD_TYPES.h"
#include "DIO_interface.h"
#include <util/delay.h>

void main()
{
    uint8 SevenSegDigits[10] = {
        0x3F, 0x06, 0x5B, 0x4F, 0x66,
        0x6D, 0x7D, 0x07, 0x7F, 0x6F
    };

    DIO_u8SetPortDirection(DIO_u8PORTA, DIO_u8PORT_OUTPUT); // cathode control
    DIO_u8SetPortDirection(DIO_u8PORTB, DIO_u8PORT_OUTPUT); // units
    DIO_u8SetPortDirection(DIO_u8PORTC, DIO_u8PORT_OUTPUT); // tens
    DIO_u8SetPortDirection(DIO_u8PORTD, DIO_u8PORT_OUTPUT); // minutes

    uint8 i, second = 1, minute = 1, COUNT = 1;

    while(1)
    {
        // set all cathodes HIGH initially
        DIO_u8SetPortValue(DIO_u8PORTA, DIO_u8PORT_HIGH);
        DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN2, DIO_u8PIN_LOW);

        // seconds counter
        for(second = 1; second < 6; second++)
        {
            // cathode A0
            DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_LOW);
            DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN1, DIO_u8PIN_LOW);

            for(i = 0; i < 10; i++)
            {
                DIO_u8SetPortValue(DIO_u8PORTB, SevenSegDigits[i]);
                _delay_ms(30);
            }

            DIO_u8SetPortValue(DIO_u8PORTC, SevenSegDigits[second]);
            _delay_ms(30);

            // turn off cathodes A0 and A1 after display
            DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_HIGH);
            DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN1, DIO_u8PIN_HIGH);
        }

        // units of minutes (cathode A2)
        DIO_u8SetPortValue(DIO_u8PORTD, SevenSegDigits[minute]);
        minute++;

        // update tens when units exceed 10
        if(minute == 11)
        {
            minute = 1;
            DIO_u8SetPortValue(DIO_u8PORTA, DIO_u8PORT_LOW);

            // tens of minutes (cathode A3)
            DIO_u8SetPortValue(DIO_u8PORTB, SevenSegDigits[COUNT]);
            _delay_ms(200);
            COUNT++;
        }
    }
}
