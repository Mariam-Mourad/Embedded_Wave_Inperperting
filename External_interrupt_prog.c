/*
 * External_interrupt_prog.c
 *
 *  Created on: Sep 27, 2019
 *      Author: Mariam
 */
#include"std_types.h"
#include"Bit_calc.h"

#include<avr/interrupt.h>
#include<avr/io.h>
#include"Timer_regs.h"
#include "External_interrupt_interface.h"

static	u8 flag=0;
static  u16 Ton;
static	u16 Toff;
static	u16 Time__;

ISR(INT0_vect)
{
Time__=Timer_TCCR0;
Timer_TCCR0=0;
if(flag==0)
{
	Ton=Time__;
	//set external interrupt on rising edge
	MCUCR=3;
	flag=1;
}
else if(flag==1)
{
	Toff=Time__;
	//set external interrupt on falling edge
		MCUCR=2;
		flag=0;
}


}
/********************************************/
void VidExternal_interrupt0INT (void)
{

//set interrupt on falling edge
	ClrBit(MCUCR,0);
	SetBit(MCUCR,1);
//INT0 interrupt0 enable
	SetBit(GICR,6);
//clearing interrupt0 flag
	SetBit(GIFR,6);
//enable global interrupt
	SetBit(SREG,7);
}
/***************************************************/
u16 u16GetICUvalues(u16* freq, u16* DutyCycle)
{
	if((Ton+Toff)>0)
	{
		DutyCycle=(Ton*(u16)100/(u16)(Ton+Toff));
		freq=(u16)((u32)1000000/((u32)(Ton+Toff)*(u32)8));
	}
}
