#include "oled.h"
#include "picture.h"
#include "oledfont.h"

#include "main.h"

//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127
//[1]0 1 2 3 ... 127
//[2]0 1 2 3 ... 127
//[3]0 1 2 3 ... 127
//[4]0 1 2 3 ... 127
//[5]0 1 2 3 ... 127
//[6]0 1 2 3 ... 127
//[7]0 1 2 3 ... 127

/*
 * SSD1106是132x64，而SSD1306是128x64，1.3寸OLED是128*64像素，去了中间128位，所以起始坐标为0x2
 */

extern I2C_HandleTypeDef hi2c2;

/*
 * STM32F4的I2C库有问题，I2C地址不会自动添加读写位
 */
#define oled_addr 0x78

unsigned char oled_cmd[2] = {0x00, 0x00};
unsigned char oled_data[2] = {0x40, 0x00};

/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
    oled_cmd[1] = IIC_Command;

    if(HAL_I2C_Master_Transmit(&hi2c2, oled_addr, oled_cmd, 2, 1000) != HAL_OK) {
    	HAL_GPIO_WritePin(GPIOB, Red_Pin, GPIO_PIN_SET);
    }
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
    oled_data[1] = IIC_Data;

    if(HAL_I2C_Master_Transmit(&hi2c2, oled_addr, oled_data, 2, 1000) != HAL_OK) {
    	HAL_GPIO_WritePin(GPIOB, Red_Pin, GPIO_PIN_SET);
    }
}

//向SSD1306写入一个字节。
//dat:要写入的数据/命令
//cmd:数据/命令标志 0,表示命令;1,表示数据;
void OLED_WR_Byte(unsigned char data,unsigned char cmd)
{
    if (cmd) {
        Write_IIC_Data(data);
    } else {
        Write_IIC_Command(data);
    }
}

void OLED_Set_Pos(unsigned char x, unsigned char y)
{
    OLED_WR_Byte(0xb0+y,OLED_CMD);
    OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
    OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD);
}

//开启OLED显示
void OLED_Display_On(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
    OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
    OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

//关闭OLED显示
void OLED_Display_Off(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
    OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
    OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}

//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!
void OLED_Clear(void)
{
    unsigned char i,n;
    for(i=0;i<8;i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
        OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
        OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址
        for(n=0;n<128;n++)
            OLED_WR_Byte(0,OLED_DATA);
    } //更新显示
}

//全显函数,整个屏幕是亮的!
void OLED_On(void)
{
    unsigned char i,n;
    for(i=0;i<8;i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
        OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
        OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址
        for(n=0;n<128;n++)
            OLED_WR_Byte(1,OLED_DATA);
    } //更新显示
}

//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示
//size:选择字体 16/12
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr)
{
    unsigned char c=0,i=0;
        c=chr-' ';//得到偏移后的值
        if(x>Max_Column-1){x=0;y=y+2;}
        if(SIZE ==16)
        {
            OLED_Set_Pos(x,y);
            for(i=0;i<8;i++)
            OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
            OLED_Set_Pos(x,y+1);
            for(i=0;i<8;i++)
            OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
        } else {
            OLED_Set_Pos(x,y+1);
            for(i=0;i<6;i++)
            OLED_WR_Byte(F6x8[c][i],OLED_DATA);
        }
}

//m^n函数
unsigned int oled_pow(unsigned char m,unsigned char n)
{
    unsigned int result=1;
    while(n--)
        result*=m;
    return result;
}

//显示2个数字
//x,y :起点坐标
//len :数字的位数
//size:字体大小
//mode:模式   0,填充模式;1,叠加模式
//num:数值(0~4294967295);
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size2)
{
    unsigned char t,temp;
    unsigned char enshow=0;
    for(t=0;t<len;t++)
    {
        temp=(num/oled_pow(10,len-t-1))%10;
        if(enshow==0&&t<(len-1))
        {
            if(temp==0)
            {
                OLED_ShowChar(x+(size2/2)*t,y,' ');
                continue;
            }else enshow=1;

        }
        OLED_ShowChar(x+(size2/2)*t,y,temp+'0');
    }
}

//显示一个字符号串
void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr)
{
    unsigned char j=0;
    while (chr[j]!='\0')
    {
        OLED_ShowChar(x,y,chr[j]);
        x+=8;

        if(x>120)
        {
            x=0;y+=2;
        }
            j++;
    }
}

//显示字符串，指定长度避免数组越界
void OLED_ShowString_N(unsigned char x,unsigned char y,unsigned char *chr, int size)
{
    int j=0;
    while (j < size)
    {
        OLED_ShowChar(x,y,chr[j]);
        x+=8;

        if(x>120)
        {
            x=0;y+=2;
        }
            j++;
    }
}

//显示汉字
void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no)
{
    unsigned char t,adder=0;
    OLED_Set_Pos(x,y);
    for(t=0;t<16;t++)
    {
        OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
        adder+=1;
    }
        OLED_Set_Pos(x,y+1);
    for(t=0;t<16;t++)
    {
        OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
        adder+=1;
    }
}

/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{
 unsigned int j=0;
 unsigned char x,y;

  if(y1%8==0)
      y=y1/8;
  else
      y=y1/8+1;
    for(y=y0;y<y1;y++)
    {
        OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
        {
            OLED_WR_Byte(BMP[j++],OLED_DATA);
        }
    }
}

//void Initial_M096128x64_ssd1306(void)
void OLED_Init(void)
{
	Write_IIC_Command(0xAE);   //display off
	Write_IIC_Command(0x20);	//Set Memory Addressing Mode	
	Write_IIC_Command(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	Write_IIC_Command(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	Write_IIC_Command(0xc8);	//Set COM Output Scan Direction
	Write_IIC_Command(0x00);//---set low column address
	Write_IIC_Command(0x10);//---set high column address
	Write_IIC_Command(0x40);//--set start line address
	Write_IIC_Command(0x81);//--set contrast control register
	Write_IIC_Command(0xdf);
	Write_IIC_Command(0xa1);//--set segment re-map 0 to 127
	Write_IIC_Command(0xa6);//--set normal display
	Write_IIC_Command(0xa8);//--set multiplex ratio(1 to 64)
	Write_IIC_Command(0x3F);//
	Write_IIC_Command(0xa4);//0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	Write_IIC_Command(0xd3);//-set display offset
	Write_IIC_Command(0x00);//-not offset
	Write_IIC_Command(0xd5);//--set display clock divide ratio/oscillator frequency
	Write_IIC_Command(0xf0);//--set divide ratio
	Write_IIC_Command(0xd9);//--set pre-charge period
	Write_IIC_Command(0x22); //
	Write_IIC_Command(0xda);//--set com pins hardware configuration
	Write_IIC_Command(0x12);
	Write_IIC_Command(0xdb);//--set vcomh
	Write_IIC_Command(0x20);//0x20,0.77xVcc
	Write_IIC_Command(0x8d);//--set DC-DC enable
	Write_IIC_Command(0x14);//
	Write_IIC_Command(0xaf);//--turn on oled panel 

    OLED_Clear();
    OLED_Set_Pos(0x02,0);
}





