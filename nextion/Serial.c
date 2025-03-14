#include "Serial.h"
#include "../util/Utilities.h"
#include "usart.h"

unsigned char rxBuff[64];
char rxHead, rxTail;
/**
  * @brief  Rx Transfer completed callback
  * @param  UartHandle: UART handle
  * @retval None
  */
 volatile uint32_t RxCounter = 0 ;
 void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
 {
     if(UartHandle == &huart4)
     {
        RxCounter++;
         rxBuff[rxHead++] = (unsigned char)(huart4.Instance->RDR & 0xFF); // read the received data
         if (rxHead == sizeof(rxBuff))
         {
             rxHead = 0;
         }
     }
     HAL_UART_Receive_IT(&huart4, (uint8_t *)rxBuff, 1); // start the interrupt
 }


void Serial_Init(long baudrate)
{
	baudrate = baudrate;
	//MX_UART4_Init();
    HAL_UART_Receive_IT(&huart4, (uint8_t *)rxBuff, 1); // start the interrupt
}

unsigned char Serial_Write(unsigned char c)
{
	HAL_StatusTypeDef retval;
	retval =HAL_UART_Transmit(&huart4, &c, 1 , HAL_MAX_DELAY);

	if( HAL_OK == retval)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

unsigned char Serial_Read()
{
    unsigned char c;
    if (rxTail < rxHead)
    {
        c = rxBuff[rxTail++];
        if (rxTail == rxHead)
        {
            rxHead = 0;
            rxTail = 0;
        }
    }
    else
    {
        rxHead = 0;
        rxTail = 0;
        c = -1;
    }
    return c;
}

unsigned char Serial_Available()
{
    return rxHead - rxTail;
}

unsigned char Serial_ReadBytes(char *buf, unsigned char len)
{
    unsigned char cnt = 0;
    if (len < rxHead - rxTail)
    {
        ArrayCopy(buf, &rxBuff[rxTail], len);
        rxTail += len;
        cnt = len;
    }
    else if (len == rxHead - rxTail)
    {
        ArrayCopy(buf, &rxBuff[rxTail], len);
        rxTail = 0;
        rxHead = 0;
        cnt = len;
    }
    else
    {
        ArrayCopy(buf, &rxBuff[rxTail], rxHead - rxTail);
        cnt = rxHead - rxTail;
        rxTail = 0;
        rxHead = 0;
    }
    return cnt;
}

void Serial_Print(unsigned char *txt)
{
    HAL_StatusTypeDef retval;
    short i = strlen((char *)txt);
    retval = HAL_UART_Transmit(&huart4, txt, i, HAL_MAX_DELAY);
}
