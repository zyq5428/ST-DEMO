#include "oled.h"

#include "bmp.h"

#include "stm32f4xx_hal.h"

/*******************************Main*******************************/
void oled_display_memu(void)
{
	unsigned char Humidity_Unit[5] = "%RH";
    OLED_Init();
    HAL_Delay(10);

    OLED_ShowCHinese(14,0,0);//温
    OLED_ShowCHinese(42,0,1);//湿
    OLED_ShowCHinese(72,0,2);//度
    OLED_ShowCHinese(100,0,3);//计

    OLED_ShowCHinese(2,3,0);//温
    OLED_ShowCHinese(22,3,2);//度
//        OLED_ShowString(56,3,":");
//    OLED_ShowString(48,3,"26.50");
    OLED_ShowCHinese(100,3,4);//℃

    OLED_ShowCHinese(2,5,1);//湿
    OLED_ShowCHinese(22,5,2);//度
//        OLED_ShowString(56,5,":");
//    OLED_ShowString(48,5,"78.23");
    OLED_ShowString(98,5,Humidity_Unit);
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

