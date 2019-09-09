#include "gy_30.h"
#include "oled.h"
#include "uart_display.h"

static uint8_t GY30_DATA[2] = {0x00,0x00};
static unsigned char gy_30_title[] = "\t\nCurrent lx is :";

extern I2C_HandleTypeDef hi2c3;
#define GY30_I2C	&hi2c3

void gy_30_send_command(uint8_t command)
{
	HAL_I2C_Master_Transmit(GY30_I2C, GY_30_ADDR, &command, 1, 200);
}

uint16_t gy_30_read_data(void)
{
	HAL_I2C_Master_Receive(GY30_I2C, GY_30_ADDR, GY30_DATA, 2, 200);
	return ((GY30_DATA[0] << 8) | GY30_DATA[1]);
}

void gy_30_display(uint16_t lx)
{
	uint8_t symbol[6] = {0x0};
	symbol[5] = ' ';
	symbol[4] = lx / 1 % 10 + '0';
	symbol[3] = lx / 10 % 10 + '0';
	symbol[2] = lx / 100 % 10 + '0';
	symbol[1] = lx / 1000 % 10 + '0';
	symbol[0] = lx / 10000 % 10 + '0';

	uart_multibyte_send(gy_30_title, sizeof(gy_30_title));

	for(int i = 0; i < 5; i++) {
		if(symbol[i] != '0') {
			uart_multibyte_send(&symbol[i], 5-i);
			break;
		}
		else
			uart_multibyte_send(&symbol[5], 1);
	}

}

void gy_30_test(void)
{
	uint16_t lx;

	gy_30_send_command(ONE_RIME_H_MODE);
	HAL_Delay(160);
	lx = gy_30_read_data();
	gy_30_display(lx);
}
