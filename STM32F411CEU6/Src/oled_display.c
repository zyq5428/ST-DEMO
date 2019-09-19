#include "oled.h"

#include "bmp.h"

#include "stm32f4xx_hal.h"

/*******************************Main*******************************/
void oled_display_memu(void)
{
	unsigned char Humidity_Unit[5] = "%RH";
	unsigned char Light_Unit[5] = "Lx";
    OLED_Init();
    HAL_Delay(10);

    OLED_ShowCHinese(14,0,0);//温
    OLED_ShowCHinese(42,0,1);//湿
    OLED_ShowCHinese(72,0,2);//度
    OLED_ShowCHinese(100,0,3);//计

    OLED_ShowCHinese(2,2,0);//温
    OLED_ShowCHinese(22,2,2);//度
//	OLED_ShowString(56,2,":");
//	OLED_ShowString(48,2,"26.50");
    OLED_ShowCHinese(100,2,4);//℃

    OLED_ShowCHinese(2,4,1);//湿
    OLED_ShowCHinese(22,4,2);//度
//	OLED_ShowString(56,4,":");
//	OLED_ShowString(48,4,"78.23");
    OLED_ShowString(98,4,Humidity_Unit);

    OLED_ShowCHinese(2,6,5);//湿
    OLED_ShowCHinese(22,6,6);//度
//	OLED_ShowString(56,5,":");
//	OLED_ShowString(48,5,"78.23");
    OLED_ShowString(98,6,Light_Unit);

//    delay_s(1);
//
//    OLED_ShowString(0,2,"0.96' OLED TEST");
//
//    OLED_ShowString(20,4,"2014/05/01");
//    OLED_ShowString(0,6,"ASCII:");
//    OLED_ShowString(63,6,"CODE:");
//    OLED_ShowChar(48,6,t);//��ʾASCII�ַ�
//    t++;
//    if(t>'~')t=' ';
//    OLED_ShowNum(103,6,t,3,16);//��ʾASCII�ַ�����ֵ
//
//
//    delay_ms(50);
//    OLED_Clear();
//    delay_ms(50);
////        OLED_DrawBMP(0,0,128,8,BMP1);  //ͼƬ��ʾ(ͼƬ��ʾ���ã����ɵ��ֱ�ϴ󣬻�ռ�ý϶�ռ䣬FLASH�ռ�8K��������)
//    delay_ms(50);
//    OLED_DrawBMP(0,0,128,8,gImage_128x64);
//    delay_ms(50);
}

