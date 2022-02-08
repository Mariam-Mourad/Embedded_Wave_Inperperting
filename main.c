/*
 * main.c
 *
 *  Created on: Aug 23, 2019
 *      Author: Mariam
 */
#include"std_types.h"
#include"Bit_calc.h"

#include"DIO_interface.h"
#include"LCD_interface.h"
#include"Timer_interface.h"
#include"External_interrupt_interface.h"


void Seperate_Result (u32 u32Result, u16 * u8array_Result)
{

	u8array_Result[0]= ((u32Result / 10000) % 10) + 48;//48 is the zero character is ASCII
	u8array_Result[1]= ((u32Result / 1000 ) % 10) + 48;
	u8array_Result[2]= ((u32Result / 100  ) % 10) + 48;
	u8array_Result[3]= ((u32Result / 10   ) % 10) + 48;
	u8array_Result[4]=  (u32Result % 10   ) + 48;

}

void main (void)
{	u16 freq=0;
	u16 DutyCycle=0;
	u16	u8array_freq[5]={0};
	u16	u8array_DutyCycle[5]={0};

	//LCD data port and control port
	//OC0 is PORTb pin 3
	DIO_vidSetPortDirection(PORTC,OUTPUT);
	DIO_vidSetPortDirection(PORTB,OUTPUT);

	//external interrupt pin
	DIO_vidSetPinDirection(PORTD,PIN2,INPUT);

	LCD_vidIntitalize();
	Timer_vidIntFastPWMmode();
	Timer_vidIntTimer1NormalMode();

	VidExternal_interrupt0INT();

	while(1)
	{



	}
}

