/*
 * Timer_interface.h
 *
 *  Created on: Sep 14, 2019
 *      Author: Mariam
 */

#ifndef TIMER_REGS_H_
#define TIMER_REGS_H_

#define Timer_TCNT0  *((volatile u8*)(0x52))
#define Timer_TCCR0  *((volatile u8*)(0x53))
#define Timer_OCR0   *((volatile u8*)(0x5C))
#define Timer_TIMSK  *((volatile u8*)(0x59))
#define Timer_OCR1A	*((volatile u16*)(0x4A))
#define Timer_TCCR1A *((volatile u8*)(0x4F))
#define Timer_TCCR1B *((volatile u8*)(0x4E))
#define Timer_SREG   *((volatile u8*)(0x5F))
#endif /* TIMER_REGS_H_ */
