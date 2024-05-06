
#include <avr/pgmspace.h>
#ifndef GLCD_H_
#define GLCD_H_

#define Data_Port			PORTA	
#define Command_Port		PORTC	
#define Data_Port_Dir		DDRA	
#define Command_Port_Dir	DDRC	

#define RS					PC0
#define RW					PC1
#define EN					PC2
#define CS1					PC3
#define CS2					PC4
#define RST					PC5

#define TotalPage			8
void GLCD_String_send(int page_no, char str[])	;
void GLCD_Command(char Command);
void GLCD_Data(char Data);
void GLCD_Init();
void GLCD_ClearAll();
void GLCD_Stringleft(int page_no, char str[]);
void GLCD_Stringright(int page_no, char str[]);
void GLCD_String(const char* image);
void GLCD_white_screen();
void GLCD_graph(char page_no, char str[]);
void GLCD_String_send2(char page_no, char str[]);
#endif /* GLCD_H_ */