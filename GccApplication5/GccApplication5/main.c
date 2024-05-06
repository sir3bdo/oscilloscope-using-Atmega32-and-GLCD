#define F_CPU 8000000UL	
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <util/delay.h>
#include "STD_types.h"
#include "BIT_math.h"
#include "DIO_Reg.h"
#include "DIO_int.h"
#include "Timer0_int.h"
#include "EXTI_int.h"
#include "GIE_int.h"
#include "GLCD.h"
#include "image.h"
#include "string1.h"
#include <avr/interrupt.h>
//****************************
volatile u16 Read_1 = 0;
volatile u16 Read_2 = 0;
volatile u16 Read_3 = 0;
volatile u16 Num_OV = 0;
volatile u8 counter=0;
//****************************
ISR(TIMER0_OVF_vect){
	Num_OV++;
	if(DIO_voidGtPinValue(DIO_U8_PORTD, 5) == 0)
	{
	DIO_voidSetPinValue(DIO_U8_PORTD,DIO_U8_PIN5,DIO_U8_HIGH);
	}
	else
	{
	DIO_voidSetPinValue(DIO_U8_PORTD,DIO_U8_PIN5,DIO_U8_LOW);
	}
}
//****************************
int main(void)
{
	GLCD_Init();
	GLCD_ClearAll();
	DIO_voidSetPinDir(DIO_U8_PORTD,DIO_U8_PIN5,DIO_U8_OUTPUT);
	DIO_voidSetPinValue(DIO_U8_PORTD,DIO_U8_PIN5,DIO_U8_HIGH);
	u8 Copy_u8Val=0;
	EXTI0_voidInit();
	EXTI0_voidEnable();
	GIE_voidEnable();	
	f32 frequancy = 0;
	f32 Duty_Cycle = 0;
	f32 time= 0 ;
	Timer0_vidInit();
	Timer_vidSetTimerCounts(Copy_u8Val);
	Timer_vidEnableInterrupt();
//****************************
		s8 freq1[10];		
		s8 duty1[10];
		s8 TIME1[10];
//****************************
		while(DIO_voidGtPinValue(DIO_U8_PORTD, 5) == 1);
		if(counter!=2){
		Read_1=Timer_u8GetTimerCounts()+Num_OV*256;
		counter++;
		}
		//****************************
		Num_OV=0;		
		while(DIO_voidGtPinValue(DIO_U8_PORTD, 5) == 0);
		if(counter!=2){
		Read_2=Timer_u8GetTimerCounts()+Num_OV*256;	
		counter++;	
		}	
		//****************************	
		frequancy = (float)(1.0 / ( ((float)Read_2 + Read_1)*1000 * (8.0 / 8000000.0)));
		ftoa(frequancy,freq1,1);
		Duty_Cycle =(float)Read_1* 100.0/(Read_2 + Read_1);
		ftoa(Duty_Cycle,duty1,1);
		time=((float)1.0/frequancy)*1000.0;
		ftoa(time,TIME1,1);		
		//****************************			
		if(counter==2){
			
			GLCD_white_screen();
			GLCD_Stringleft(0,"F=");
			GLCD_Stringleft(0,freq1);
			GLCD_Stringleft(0,"KHZ");
			GLCD_Stringright(0,"  ");
			GLCD_Stringright(0,"D=");
			GLCD_Stringright(0,duty1);
			GLCD_Stringright(0,"%");
			//GLCD_Stringleft(1," ");
			GLCD_Stringleft(1,"T=");
			GLCD_Stringleft(1,TIME1);
			GLCD_Stringleft(1,"ms");
		//******************************						
			GLCD_String_send(4,LOW);
			GLCD_String_send(4,LOW);
			GLCD_String_send(4,STARTHIGH);
			GLCD_String_send(4,UPPER);
			GLCD_String_send(4,UPPER);
			GLCD_String_send(4,STARTLOW);
			GLCD_String_send(4,LOW);
			GLCD_String_send(4,LOW);
			GLCD_String_send(4,STARTHIGH);
			GLCD_String_send(4,UPPER);
			GLCD_String_send(4,UPPER);
			GLCD_String_send(4,STARTLOW);
			GLCD_String_send(4,LOW);
		//**********************************	
			GLCD_String_send2(4,LOW);
			GLCD_String_send2(4,STARTHIGH);
			GLCD_String_send2(4,UPPER);
			GLCD_String_send2(4,UPPER);
			GLCD_String_send2(4,STARTLOW);
			GLCD_String_send2(4,LOW);
			GLCD_String_send2(4,LOW);
			GLCD_String_send2(4,STARTHIGH);
			GLCD_String_send2(4,UPPER);
			GLCD_String_send2(4,UPPER);
			GLCD_String_send2(4,STARTLOW);
			GLCD_String_send2(4,LOW);
			GLCD_String_send2(4,LOW);			
			_delay_ms(1000);
			
		}
		_delay_ms(5000);
		Num_OV=0;
		while(1);
	
	return 0;
	
}