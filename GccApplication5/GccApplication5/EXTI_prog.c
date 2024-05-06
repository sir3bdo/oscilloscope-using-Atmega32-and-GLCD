/*****************************************/
/*	Author : Khaled Mohsen				 */
/*	Date   : 1-7-2022   		   		 */
/*	Version: 0.1				         */
/*	File   : EXTI_prog.c	             */
/*****************************************/
#include "STD_types.h"
#include "BIT_MATH.h"
#include "EXTI_int.h"
#include "EXTI_private.h"
#include "EXTI_config.h"
#include "GIE_int.h"

void EXTI0_voidInit(void)
{
	#if EXTI0_u8_ISC == EXTI0_u8_LOW_LEVEL
	CLEAR_BIT(MCUCR,0);
	CLEAR_BIT(MCUCR,1);
	#elif EXTI0_u8_ISC == EXTI0_u8_RISING
	SET_BIT(MCUCR,0);
	SET_BIT(MCUCR,1);	
	#elif EXTI0_u8_ISC == EXTI0_u8_FALLING
	CLEAR_BIT(MCUCR,0);
	SET_BIT(MCUCR,1);	
	#elif EXTI0_u8_ISC == EXTI0_u8_ANY_CHANGE
	SET_BIT(MCUCR,0);
	CLEAR_BIT(MCUCR,1);	
	#endif
	
	EXTI0_voidDisable(); // Disable PIE
	GIE_voidDisable(); // Disable GIE
	EXTI0_voidClearFlag(); // clear flag
}
void EXTI0_voidEnable(void)
{
	SET_BIT(GICR , 6);
}
void EXTI0_voidDisable(void)
{
	CLEAR_BIT(GICR , 6);
}
void EXTI0_voidClearFlag(void)
{
	SET_BIT(GIFR , 6);
}