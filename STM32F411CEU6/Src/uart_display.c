#include "uart_display.h"

extern UART_HandleTypeDef huart6;

uint8_t uart_multibyte_send(uint8_t data[], uint8_t num)
{
//    uint8_t i;
//
//    for (i = 0; i < num; i++ ) {
//        EUSCI_A_UART_transmitData(EUSCI_A0_BASE, data[i]);
//    }

	HAL_UART_Transmit(&huart6, (uint8_t *)data, num, 0xFFFF);

    return 0;
}
