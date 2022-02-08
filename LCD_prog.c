/*
 * LCD_prog.c
 *
 *  Created on: Aug 24, 2019
 *      Author: Mariam
 */
#include"std_types.h"
#include"Bit_calc.h"
#include<util/delay.h>

#include"DIO_interface.h"
#include"LCD_interface.h"
#include"LCD_conf.h"

#define lcd_Clear           0b00000001          /* replace all characters with ASCII 'space'                       */
#define lcd_EntryMode       0b00000110          // shift cursor from left to right on read/write
#define lcd_DisplayOn       0b00001111          // display on, cursor off, don't blink character
#define lcd_FunctionSet8bit 0b00111000          // 8-bit data, 2-line display, 5 x 7 font

LCD_ArrExtraChar[]= {	1, 1, 2, 4, 4, 8, 16, 16,
						16, 16, 8, 4, 4, 2, 1, 1,

					   4,10, 4, 14, 21, 4, 10, 17,
					   0, 0, 0, 0,0,0,0,0,
					   0, 0, 0, 0,0,0,0,0,
					   0, 0, 0, 0,0,0,0,0,
					   0, 0, 0, 0,0,0,0,0,
					   0, 0, 0, 0,0,0,0,0
						};

void LCD_vidWriteCommand (u8 Copy_u8PortValue)
{
	/*Enable will be written on it using PORTC Pin B0  setted to low*/
	 DIO_vidSetPinValue(LCD_Ctr_Port, LCD_En, LOW);

/*RS will be written on it using PORT B Pin B1 setted to low as it is command */
	 	 DIO_vidSetPinValue(LCD_Ctr_Port,LCD_RS,LOW);
/*Read/Write will be written on it using PORT B Pin B2 setted to low as we will write on the lcd*/
	 	DIO_vidSetPinValue(LCD_Ctr_Port, LCD_RW, LOW);
/*Set the wanted command*/
	 	DIO_vidSetPortValue(PORTD, Copy_u8PortValue);
/*Enable pulse*/
	  DIO_vidSetPinValue(LCD_Ctr_Port, LCD_En, HIGH);
	 	 _delay_ms(30);
	 	 DIO_vidSetPinValue(LCD_Ctr_Port, LCD_En, LOW);



	}
/*********************************************************************************************/
void LCD_vidIntitalize(void)
{
	_delay_ms(30);
	LCD_vidWriteCommand(0b00111000);
	_delay_ms(1);
	LCD_vidWriteCommand(0b00001111);
	_delay_ms(1);
	LCD_vidWriteCommand(0b00000001);
	_delay_ms(2);
	LCD_vidWriteCommand(0b00000110);
	_delay_ms(1);


}
/*************************************************************************************************/
void LCD_vidWriteData (u8 Copy_u8PortData)
{/*Enable will be written on it using PORTC Pin B0  setted to low*/
	 DIO_vidSetPinValue(LCD_Ctr_Port, LCD_En, LOW);

/*RS will be written on it using PORT B Pin B1 setted to low as it is DATA */
	 	 DIO_vidSetPinValue(LCD_Ctr_Port, LCD_RS, HIGH);
/*Read/Write will be written on it using PORT B Pin B2 setted to low as we will write on the lcd*/
	 	DIO_vidSetPinValue(LCD_Ctr_Port, LCD_RW, LOW);
/*Set the wanted Data*/
	 	DIO_vidSetPortValue(PORTD, Copy_u8PortData);
/*Enable pulse*/
	 	 DIO_vidSetPinValue(LCD_Ctr_Port, LCD_En, HIGH);
	 	 _delay_ms(10);
	 	 DIO_vidSetPinValue(LCD_Ctr_Port, LCD_En, LOW);
}
/**********************************************************************************************/
void LCD_vidWriteString (u8* Copy_u8PortString,u8 u8Index)

{/*writing bit by bit when accessing the array of the string*/
	u8 Local_u8Iteration;/*to count the number of iterations till the index*/
	for(Local_u8Iteration=0;Local_u8Iteration<u8Index;Local_u8Iteration++)
	{
		LCD_vidWriteData(Copy_u8PortString[Local_u8Iteration]);
	}
}
/*************************************************************************************************/
void LCD_vidWriteString3 (u8* Copy_u8PortString)
{u8 Local_u8Iteration2=0;
	while(Copy_u8PortString[Local_u8Iteration2]!='\0')
	{
		LCD_vidWriteData(Copy_u8PortString[Local_u8Iteration2]);
		Local_u8Iteration2++;
	}

}
/************************************************************************************************/
void LCD_vidWriteString2 (u8* Copy_u8PortString)
{u8 Local_u8Iteration2;
	while(*Copy_u8PortString !='\0')
	{
		LCD_vidWriteData(*Copy_u8PortString);
		Copy_u8PortString ++;
	}
}
/****************************************************************************************************/
void GoToXY(u8 x, u8 y)
{if (((x>=0) && (x<16)) && ((y>=0)&&(y<2)))
	{u8 Local_Address=128|(x+(y*64));
	LCD_vidWriteCommand(Local_Address);
	}
}
/****************************************************************************************************/
void LCD_vidClearScreen(void)
{LCD_vidWriteCommand(0x01);
_delay_ms(2);

	}
/***************************************************************************************************/
void LCD_vidWriteExtraChar(u8 X, u8 Y)
{	u8 Local_u8iteration;
	//u8 Local_u8iteration2;
//Go to CGRAM
	LCD_vidWriteCommand(0x40);
//drawing the char
for(Local_u8iteration=0;Local_u8iteration<64;Local_u8iteration++)
{
	 LCD_vidWriteData(LCD_ArrExtraChar[Local_u8iteration]);
}
//Go to DDRAM
LCD_vidWriteCommand(0x80);
GoToXY(X,Y);
/*
for(Local_u8iteration=0;Local_u8iteration<=7;Local_u8iteration++)
{
	 LCD_vidWriteData(Local_u8iteration);
	 _delay_ms(5);
}*/
//sin wave


	 _delay_ms(5);
//7amoksha
/*for(Local_u8iteration=0;Local_u8iteration<16;Local_u8iteration++)
{
	GoToXY(Local_u8iteration+1,Y^=1);
	 LCD_vidWriteData(2);
	 _delay_ms(1000);
	 LCD_vidClearScreen();



	/* for(Local_u8iteration=0;Local_u8iteration<16;Local_u8iteration+=4)
	 {	GoToXY(Local_u8iteration,1);
	 	 LCD_vidWriteData(0);
	 	 GoToXY(Local_u8iteration+3,1);
	 	 LCD_vidWriteData(1);
	 	 GoToXY(Local_u8iteration+1,0);
	 	 LCD_vidWriteData(0);
	 	 GoToXY(Local_u8iteration+2,0);
	 	 LCD_vidWriteData(1);

	 	}
	 _delay_ms(1000);
	 LCD_vidClearScreen();*/


}


