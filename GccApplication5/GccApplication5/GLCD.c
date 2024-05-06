#define F_CPU 8000000UL				/* Define CPU clock Frequency 8MHz */
#include <avr/io.h>					/* Include AVR std. library file */
#include <util/delay.h>				/* Include defined delay header file */
#include <stdio.h>					/* Include standard i/o library file */
#include "Font_Header.h"
#include "GLCD.h"

#define Data_Port			PORTA	/* Define data port for GLCD */
#define Command_Port		PORTC	/* Define command port for GLCD */
#define Data_Port_Dir		DDRA	/* Define data port for GLCD */
#define Command_Port_Dir	DDRC	/* Define command port for GLCD */

#define RS					PC0		/* Define control pins */
#define RW					PC1
#define EN					PC2
#define CS1					PC3
#define CS2					PC4
#define RST					PC5

#define TotalPage			8
unsigned int add1=0;
unsigned int add2=0;
unsigned int add3=0;
void GLCD_Command(char Command)		/* GLCD command function */
{
	Data_Port = Command;			/* Copy command on data pin */
	Command_Port &= ~(1 << RS);		/* Make RS LOW to select command register */
	Command_Port &= ~(1 << RW);		/* Make RW LOW to select write operation */
	Command_Port |=  (1 << EN);		/* Make HIGH to LOW transition on Enable pin */
	_delay_us(5);
	Command_Port &= ~(1 << EN);
	_delay_us(5);
}

void GLCD_Data(char Data)			/* GLCD data function */
{
	Data_Port = Data;				/* Copy data on data pin */
	Command_Port |=  (1 << RS);		/* Make RS HIGH to select data register */
	Command_Port &= ~(1 << RW);		/* Make RW LOW to select write operation */
	Command_Port |=  (1 << EN);		/* Make HIGH to LOW transition on Enable pin */
	_delay_us(5);
	Command_Port &= ~(1 << EN);
	_delay_us(5);
}

void GLCD_Init()					/* GLCD initialize function */
{
	Data_Port_Dir = 0xFF;
	Command_Port_Dir = 0xFF;
	/* Select both left & right half of display & Keep reset pin high */
	Command_Port |= (1 << CS1) | (1 << CS2) | (1 << RST);
	_delay_ms(20);
	GLCD_Command(0x3E);				/* Display OFF */
	GLCD_Command(0x40);				/* Set Y address (column=0) */
	GLCD_Command(0xB8);				/* Set x address (page=0) */
	GLCD_Command(0xC0);				/* Set z address (start line=0) */
	GLCD_Command(0x3F);				/* Display ON */
}

void GLCD_ClearAll()				/* GLCD all display clear function */
{
	int i,j;
	/* Select both left & right half of display */
	Command_Port |= (1 << CS1) | (1 << CS2);
	for(i = 0; i < TotalPage; i++)
	{
		GLCD_Command((0xB8) + i);	/* Increment page each time after 64 column */
		for(j = 0; j < 64; j++)
		{
			GLCD_Data(0);			/* Write zeros to all 64 column */
		}
	}
	GLCD_Command(0x40);				/* Set Y address (column=0) */
	GLCD_Command(0xB8);				/* Set x address (page=0) */
}

void GLCD_Stringright(int page_no, char str[])			/* GLCD string write function */
{
	unsigned int i, column;
	unsigned int Page = ((0xB8) + page_no);
	unsigned int Y_address = 0;
	float Page_inc = 0.5;
	if(add1!=Page){
		GLCD_Command(0x40);	
	}
	add1=Page;
	Command_Port |= (1 << CS1);						
	Command_Port &= ~(1 << CS2);
	
	GLCD_Command(Page);
	for(i = 0; str[i] != 0; i++)					/* Print each char in string till null */
	{
		if (Y_address > (1024-(((page_no)*128)+FontWidth))) /* Check Whether Total Display get overflowed */
		break;										/* If yes then break writing */
		if (str[i]!=32)								/* Check whether character is not a SPACE */
		{
			for (column=1; column<=FontWidth; column++)
			{
				if ((Y_address+column)==(128*((int)(Page_inc+0.5))))	/* If yes then check whether it overflow from right side of display */
				{
					if (column == FontWidth)		/* Also check and break if it overflow after 5th column */
					break;
					GLCD_Command(0x40);				/* If not 5th and get overflowed then change Y address to START column */
					Y_address = Y_address + column;	/* Increment Y address count by column no. */
					Command_Port ^= (1 << CS1);		/* If yes then change segment controller to display on other half of display */
					Command_Port ^= (1 << CS2);
					GLCD_Command(Page + Page_inc);	/* Execute command for page change */
					Page_inc = Page_inc + 0.5;		/* Increment Page No. by half */
				}
			}
		}
		if (Y_address>(1024-(((page_no)*128)+FontWidth)))   /* Check Whether Total Display get overflowed */
		break;										/* If yes then break writing */
		if((font[((str[i]-32)*FontWidth)+4])==0 || str[i]==32)/* Check whether character is SPACE or character last column is zero */
		{
			for(column=0; column<FontWidth; column++)
			{
				GLCD_Data(font[str[i]-32][column]);	/* If yes then then print character */
				if((Y_address+1)%64==0)				/* check whether it gets overflowed  from either half of side */
				{
					Command_Port ^= (1 << CS1);		/* If yes then change segment controller to display on other half of display */
					Command_Port ^= (1 << CS2);
					GLCD_Command((Page+Page_inc));	/* Execute command for page change */
					Page_inc = Page_inc + 0.5;		/* Increment Page No. by half */
				}
				Y_address++;						/* Increment Y_address count per column */
			}
		}
		else										/* If character is not SPACE or character last column is not zero */
		{
			for(column=0; column<FontWidth; column++)
			{
				GLCD_Data(font[str[i]-32][column]); /* Then continue to print hat char */
				if((Y_address+1)%64==0)				/* check whether it gets overflowed  from either half of side */
				{
					Command_Port ^= (1 << CS1);		/* If yes then change segment controller to display on other half of display */
					Command_Port ^= (1 << CS2);
					GLCD_Command((Page+Page_inc));	/* Execute command for page change */
					Page_inc = Page_inc + 0.5;		/* Increment Page No. by half */
				}
				Y_address++;						/* Increment Y_address count per column */
			}
			GLCD_Data(0);							/* Add one column of zero to print next character next of zero */
			Y_address++;							/* Increment Y_address count for last added zero */
			if((Y_address)%64 == 0)					/* check whether it gets overflowed  from either half of side */
			{
				Command_Port ^= (1 << CS1);			/* If yes then change segment controller to display on other half of display */
				Command_Port ^= (1 << CS2);
				GLCD_Command((Page+Page_inc));		/* Execute command for page change */
				Page_inc = Page_inc + 0.5;			/* Increment Page No. by half */
			}
		}
	}
									
}

void GLCD_Stringleft(int page_no, char str[])			/* GLCD string write function */
{
	unsigned int i, column;
	unsigned int Page = ((0xB8) + page_no);
	unsigned int Y_address = 0;
	float Page_inc = 0.5;
	if(add2!=Page){
		GLCD_Command(0x40);
	}
	add2=Page;
	Command_Port |= (1 << CS2);						/* Select first Left half of display */
	Command_Port &= ~(1 << CS1);
	
	GLCD_Command(Page);
	for(i = 0; str[i] != 0; i++)					/* Print each char in string till null */
	{
		if (Y_address > (1024-(((page_no)*128)+FontWidth))) /* Check Whether Total Display get overflowed */
		break;										/* If yes then break writing */
		if (str[i]!=32)								/* Check whether character is not a SPACE */
		{
			for (column=1; column<=FontWidth; column++)
			{
				if ((Y_address+column)==(128*((int)(Page_inc+0.5))))	/* If yes then check whether it overflow from right side of display */
				{
					if (column == FontWidth)		/* Also check and break if it overflow after 5th column */
					break;
					GLCD_Command(0x40);				/* If not 5th and get overflowed then change Y address to START column */
					Y_address = Y_address + column;	/* Increment Y address count by column no. */
					Command_Port ^= (1 << CS1);		/* If yes then change segment controller to display on other half of display */
					Command_Port ^= (1 << CS2);
					GLCD_Command(Page + Page_inc);	/* Execute command for page change */
					Page_inc = Page_inc + 0.5;		/* Increment Page No. by half */
				}
			}
		}
		if (Y_address>(1024-(((page_no)*128)+FontWidth)))   /* Check Whether Total Display get overflowed */
		break;										/* If yes then break writing */
		if((font[((str[i]-32)*FontWidth)+4])==0 || str[i]==32)/* Check whether character is SPACE or character last column is zero */
		{
			for(column=0; column<FontWidth; column++)
			{
				GLCD_Data(font[str[i]-32][column]);	/* If yes then then print character */
				if((Y_address+1)%64==0)				/* check whether it gets overflowed  from either half of side */
				{
					Command_Port ^= (1 << CS1);		/* If yes then change segment controller to display on other half of display */
					Command_Port ^= (1 << CS2);
					GLCD_Command((Page+Page_inc));	/* Execute command for page change */
					Page_inc = Page_inc + 0.5;		/* Increment Page No. by half */
				}
				Y_address++;						/* Increment Y_address count per column */
			}
		}
		else										/* If character is not SPACE or character last column is not zero */
		{
			for(column=0; column<FontWidth; column++)
			{
				GLCD_Data(font[str[i]-32][column]); /* Then continue to print hat char */
				if((Y_address+1)%64==0)				/* check whether it gets overflowed  from either half of side */
				{
					Command_Port ^= (1 << CS1);		/* If yes then change segment controller to display on other half of display */
					Command_Port ^= (1 << CS2);
					GLCD_Command((Page+Page_inc));	/* Execute command for page change */
					Page_inc = Page_inc + 0.5;		/* Increment Page No. by half */
				}
				Y_address++;						/* Increment Y_address count per column */
			}
			GLCD_Data(0);							/* Add one column of zero to print next character next of zero */
			Y_address++;							/* Increment Y_address count for last added zero */
			if((Y_address)%64 == 0)					/* check whether it gets overflowed  from either half of side */
			{
				Command_Port ^= (1 << CS1);			/* If yes then change segment controller to display on other half of display */
				Command_Port ^= (1 << CS2);
				GLCD_Command((Page+Page_inc));		/* Execute command for page change */
				Page_inc = Page_inc + 0.5;			/* Increment Page No. by half */
			}
		}
	}
									/* Set Y address (column=0) */
}
void GLCD_String(const char* image)	/* GLCD string write function */
{
	int column,page,page_add=0xB8,k=0;
	float page_inc=0.5;
	char byte;

	Command_Port |= (1 << CS2);		/* Select first Left half of display */
	Command_Port &= ~(1 << CS1);	
	GLCD_Command((page_add+4));
	//GLCD_Command(0x40);	
	for(page=8;page<16;page++)		/* Print 16 pages i.e. 8 page of each half of display */
	{
		for(column=0;column<64&&image[column+k]!=0;column++)
		{
			
			byte = pgm_read_byte(&image[k+column]);
			GLCD_Data(byte);		/* Print 64 column of each page */
		}
		Command_Port ^= (1 << CS1);	/* If yes then change segment controller */
		Command_Port ^= (1 << CS2);
		GLCD_Command((page_add+page_inc+4));/* Increment page address */
		page_inc=page_inc+0.5;
		k=k+64;						/* Increment pointer */
	}
	GLCD_Command(0x40);				/* Set Y address (column=0) */
	GLCD_Command(0xB8);				/* Set x address (page=0) */
}

void GLCD_String_send(int page_no, char str[])			/* GLCD string write function */
{  
		unsigned int i;
		unsigned int Page = ((0xB8) + page_no);
		static int num1=0;
		float Page_inc = 0.5;
		if(add3!=Page){
			GLCD_Command(0x40);
		}
		add3=Page;
		Command_Port |= (1 << CS2);						/* Select first Left half of display */
		Command_Port &= ~(1 << CS1);
		GLCD_Command(Page);
		if(num1==0){GLCD_Command(0x40);}
			
		for(i = 0; i<5; i++)					/* Print each char in string till null */
		{
			
			if(num1%128==1){
				Command_Port ^= (1 << CS1);	/* If yes then change segment controller */
				Command_Port ^= (1 << CS2);
				GLCD_Command(Page+Page_inc);/* Increment page address */
				Page_inc=Page_inc+0.5;
			}
			num1++;
			GLCD_Data(str[i]);
		}
}
void GLCD_String_send2(char page_no, char str[])			/* GLCD string write function */
{
	unsigned int i;
	unsigned int Page = ((0xB8) + page_no);
	static int num=0;
	float Page_inc = 0.5;
	
	Command_Port |= (1 << CS1);						
	Command_Port &= ~(1 << CS2);
	GLCD_Command(Page);
	if(num==0){GLCD_Command(0x40);}
	
	for(i = 0; i<5; i++)					/* Print each char in string till null */
	{
		
		if(num%128==1){
			Command_Port ^= (1 << CS1);	/* If yes then change segment controller */
			Command_Port ^= (1 << CS2);
			GLCD_Command(Page+Page_inc);/* Increment page address */
			Page_inc=Page_inc+0.5;
		}
		num++;
		GLCD_Data(str[i]);
	}
}
void GLCD_white_screen()	/* GLCD string write function */
{
	int column,page,page_add=0xB8,k=0;
	float page_inc=0.5;
	

	Command_Port |= (1 << CS2);		/* Select first Left half of display */
	Command_Port &= ~(1 << CS1);
	GLCD_Command((page_add));
	//GLCD_Command(0x40);
	for(page=0;page<16;page++)		/* Print 16 pages i.e. 8 page of each half of display */
	{
		for(column=0;column<64;column++)
		{
			
			GLCD_Data(0x00);		/* Print 64 column of each page */
		}
		Command_Port ^= (1 << CS1);	/* If yes then change segment controller */
		Command_Port ^= (1 << CS2);
		GLCD_Command((page_add+page_inc));/* Increment page address */
		page_inc=page_inc+0.5;
		k=k+64;						/* Increment pointer */
	}
	GLCD_Command(0x40);				/* Set Y address (column=0) */
	GLCD_Command(0xB8);				/* Set x address (page=0) */
}

