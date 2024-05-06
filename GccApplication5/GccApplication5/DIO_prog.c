#include "STD_types.h"
#include "BIT_math.h"
#include "DIO_Reg.h"
#include "DIO_int.h"

void DIO_voidSetPinDir(u8 DIO_u8Port, u8 DIO_u8Pin, u8 DIO_u8Dir)
{
	if(DIO_u8Port == DIO_U8_PORTA)
	{
		if(DIO_u8Dir == DIO_U8_OUTPUT)
		{
			SET_BIT(DDRA,DIO_u8Pin);
		}
		else if(DIO_u8Dir == DIO_U8_INPUT)
		{
			CLEAR_BIT(DDRA,DIO_u8Pin);
		}
        else
		{
			// error message
		}			
	}
	
	else if(DIO_u8Port == DIO_U8_PORTB)
	{
		if(DIO_u8Dir == DIO_U8_OUTPUT)
		{
			SET_BIT(DDRB,DIO_u8Pin);
		}
		else if(DIO_u8Dir == DIO_U8_INPUT)
		{
			CLEAR_BIT(DDRB,DIO_u8Pin);
		}
        else
		{
			// error message
		}			
	}

	else if(DIO_u8Port == DIO_U8_PORTC)
	{
		if(DIO_u8Dir == DIO_U8_OUTPUT)
		{
			SET_BIT(DDRC,DIO_u8Pin);
		}
		else if(DIO_u8Dir == DIO_U8_INPUT)
		{
			CLEAR_BIT(DDRC,DIO_u8Pin);
		}
        else
		{
			// error message
		}			
	}	
	
	else if(DIO_u8Port == DIO_U8_PORTD)
	{
		if(DIO_u8Dir == DIO_U8_OUTPUT)
		{
			SET_BIT(DDRD,DIO_u8Pin);
		}
		else if(DIO_u8Dir == DIO_U8_INPUT)
		{
			CLEAR_BIT(DDRD,DIO_u8Pin);
		}
        else
		{
			// error message
		}			
	}
    else
    {
	 // error message
    }	   	
}
void DIO_voidSetPinValue(u8 DIO_u8Port, u8 DIO_u8Pin, u8 DIO_u8Value)
{
	if(DIO_u8Port == DIO_U8_PORTA)
	{
		if(DIO_u8Value == DIO_U8_HIGH)
		{
			SET_BIT(PORTA,DIO_u8Pin);
		}
		else if(DIO_u8Value == DIO_U8_LOW)
		{
			CLEAR_BIT(PORTA,DIO_u8Pin);
		}
        else
		{
			// error message
		}			
	}
	
	else if(DIO_u8Port == DIO_U8_PORTB)
	{
		if(DIO_u8Value == DIO_U8_HIGH)
		{
			SET_BIT(PORTB,DIO_u8Pin);
		}
		else if(DIO_u8Value == DIO_U8_LOW)
		{
			CLEAR_BIT(PORTB,DIO_u8Pin);
		}
        else
		{
			// error message
		}			
	}

	else if(DIO_u8Port == DIO_U8_PORTC)
	{
		if(DIO_u8Value == DIO_U8_HIGH)
		{
			SET_BIT(PORTC,DIO_u8Pin);
		}
		else if(DIO_u8Value == DIO_U8_LOW)
		{
			CLEAR_BIT(PORTC,DIO_u8Pin);
		}
        else
		{
			// error message
		}			
	}	
	
	else if(DIO_u8Port == DIO_U8_PORTD)
	{
		if(DIO_u8Value == DIO_U8_HIGH)
		{
			SET_BIT(PORTD,DIO_u8Pin);
		}
		else if(DIO_u8Value == DIO_U8_LOW)
		{
			CLEAR_BIT(PORTD,DIO_u8Pin);
		}
        else
		{
			// error message
		}			
	}
    else
    {
	 // error message
    }		
}
u8 DIO_voidGtPinValue(u8 DIO_u8Port, u8 DIO_u8Pin)
{
	u8 Local_u8Result = 0;
	if(DIO_u8Port == DIO_U8_PORTA)
	{
        Local_u8Result = GET_BIT(PINA,DIO_u8Pin);		
	}
	else if(DIO_u8Port == DIO_U8_PORTB)
	{
        Local_u8Result = GET_BIT(PINB,DIO_u8Pin);		
	}
	else if(DIO_u8Port == DIO_U8_PORTC)
	{
        Local_u8Result = GET_BIT(PINC,DIO_u8Pin);		
	}	
	else if(DIO_u8Port == DIO_U8_PORTD)
	{
        Local_u8Result = GET_BIT(PIND,DIO_u8Pin);		
	}	
	else
	{
		//error message
	}
	
	return Local_u8Result;
}

void DIO_voidSetPortValue(u8 DIO_u8Port, u8 DIO_u8Value)
{
	if(DIO_u8Port == DIO_U8_PORTA)
	{
		PORTA = DIO_u8Value;
	}
	else if(DIO_u8Port == DIO_U8_PORTB)
	{
		PORTB = DIO_u8Value;
	}
	else if(DIO_u8Port == DIO_U8_PORTC)
	{
		PORTC = DIO_u8Value;
	}
	else if(DIO_u8Port == DIO_U8_PORTD)
	{
		PORTD = DIO_u8Value;
	}
}