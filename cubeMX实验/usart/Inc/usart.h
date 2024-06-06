
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

void MX_USART1_UART_Init(void);

void USART1_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

