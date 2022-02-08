/*
 * Timer_prog.c
 *
 *  Created on: Sep 20, 2019
 *      Author: Mariam
 */

#include"std_types.h"
#include"Bit_calc.h"

#include"Timer_regs.h"
#include"Timer_interface.h"

void Timer_vidInitctcMode(u8 copy_u8ctcValue)
{
	/*disable force output bit*/
		ClrBit(Timer_TCCR0,7);
		/*choosing waveform -> CTC*/
		ClrBit(Timer_TCCR0,6);
		SetBit(Timer_TCCR0,3);
		/*disable OC pins*/
		ClrBit(Timer_TCCR0,5);
		ClrBit(Timer_TCCR0,4);
		/*prescaler (/8)*/

		ClrBit(Timer_TCCR0,2);
		SetBit(Timer_TCCR0,1);
		ClrBit(Timer_TCCR0,0);
		/***********************************/
		/*Enabling the timer interrupt*/
		SetBit(Timer_TIMSK,1);
		/*******************************/
		/*calculations
		 * ovf time=256 us
		 * freq time=1MHz
		 * tick time=1us
		 * ovf counts=1^6/256=3,906.25‬
		 * Preload Value=256-(.25*256)=‭192‬
		 */
		/*write 200 in the OCR0 reg*/
		Timer_OCR0=copy_u8ctcValue;
	/*global interrupt enabled*/
		SetBit(Timer_SREG,7);

}
/**********************************************************************************************/
void Timer_vidIntFastPWMmode(void)
{
	/*disable force output bit*/
		ClrBit(Timer_TCCR0,7);
		/*choosing waveform -> Fast PWM*/
		SetBit(Timer_TCCR0,6);
		SetBit(Timer_TCCR0,3);
		/*enable OC pins*/
		SetBit(Timer_TCCR0,5);
		ClrBit(Timer_TCCR0,4);
		/*prescaler (/8)*/

		ClrBit(Timer_TCCR0,2);
		SetBit(Timer_TCCR0,1);
		ClrBit(Timer_TCCR0,0);
		/***********************************/
}
/************************************************************************************/
void Timer_vidIntTimer1ctcMode(u8 copy_u8ctcValue)
{
	//OC Disable
			ClrBit(Timer_TCCR1A,7);
			ClrBit(Timer_TCCR1A,6);
			ClrBit(Timer_TCCR1A,5);
			ClrBit(Timer_TCCR1A,4);
			//Force bits disabled
			ClrBit(Timer_TCCR1A,3);
			ClrBit(Timer_TCCR1A,2);
			//Mode ctc
			ClrBit(Timer_TCCR1A,1);
			ClrBit(Timer_TCCR1A,0);

			/***********************/
			//Noise Cancellation disable
		    ClrBit(Timer_TCCR1B,7);
		    //Trigger capture disable
		    ClrBit(Timer_TCCR1B,6);
		    //Reserved Pin
		    //pin5
		    //Mode CTC
		    ClrBit(Timer_TCCR1B,4);
		    SetBit(Timer_TCCR1B,3);

		    //initial value
		   Timer_OCR1A=copy_u8ctcValue;

		    //Pre scaling--/8
		    ClrBit(Timer_TCCR1B,2);
		    SetBit(Timer_TCCR1B,1);
		    ClrBit(Timer_TCCR1B,0);

		   /***************************/
		   //Timer interrupt enable
		    SetBit(Timer_TIMSK,4);

		    //Global interrupt enable
		    SetBit(Timer_SREG,7);



}
/****************************************************************************/
void Timer_vidIntTimer1NormalMode(void)
{//normal mode operation
	Timer_TCCR1A=0;
//prescaler /64
	Timer_TCCR1B=3;
}
/********************************************/
