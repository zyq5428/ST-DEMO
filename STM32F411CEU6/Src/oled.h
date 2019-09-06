#ifndef	__OLED_H
#define	__OLED_H

#include "stm32f4xx_hal.h"

void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);


//typedef  unsigned char unsigned char
//typedef  unsigned int unsigned int
#define OLED_CMD  0 //д����
#define OLED_DATA 1 //д����


#define SIZE 16
#define XLevelL     0x02
#define XLevelH     0x10
#define Max_Column  128
#define Max_Row     64
#define Brightness  0xFF
#define X_WIDTH     128
#define Y_WIDTH     64


//OLED�����ú���
void OLED_reset(void);
void OLED_WR_Byte(unsigned char data,unsigned char cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
//void Initial_M096128x64_ssd1306();
void OLED_Init(void);
void OLED_Clear(void);
void OLED_On(void);
void OLED_DrawPoint(unsigned char x,unsigned char y,unsigned char t);
void OLED_Fill(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char dot);
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr);
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size2);
void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr);
void OLED_ShowString_N(unsigned char x,unsigned char y,unsigned char *chr, int size);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);




#endif
