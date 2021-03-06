/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
#include <string.h>
#include "gpio.h"
/* USER CODE END 0 */

UART_HandleTypeDef hlpuart1;
UART_HandleTypeDef huart1;

/* LPUART1 init function */

void MX_LPUART1_UART_Init(void)
{

  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 1000000;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_RXOVERRUNDISABLE_INIT|UART_ADVFEATURE_DMADISABLEONERROR_INIT;
  hlpuart1.AdvancedInit.OverrunDisable = UART_ADVFEATURE_OVERRUN_DISABLE;
  hlpuart1.AdvancedInit.DMADisableonRxError = UART_ADVFEATURE_DMA_DISABLEONRXERROR;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&hlpuart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&hlpuart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }

}
/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 1000000;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_RXOVERRUNDISABLE_INIT|UART_ADVFEATURE_DMADISABLEONERROR_INIT;
  huart1.AdvancedInit.OverrunDisable = UART_ADVFEATURE_OVERRUN_DISABLE;
  huart1.AdvancedInit.DMADisableonRxError = UART_ADVFEATURE_DMA_DISABLEONRXERROR;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==LPUART1)
  {
  /* USER CODE BEGIN LPUART1_MspInit 0 */

  /* USER CODE END LPUART1_MspInit 0 */
    /* LPUART1 clock enable */
    __HAL_RCC_LPUART1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**LPUART1 GPIO Configuration    
    PA2     ------> LPUART1_TX
    PA3     ------> LPUART1_RX 
    */
    GPIO_InitStruct.Pin = LPUART1_TX_Pin|LPUART1_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF12_LPUART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* LPUART1 interrupt Init */
    HAL_NVIC_SetPriority(LPUART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LPUART1_IRQn);
  /* USER CODE BEGIN LPUART1_MspInit 1 */

  /* USER CODE END LPUART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
  
    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**USART1 GPIO Configuration    
    PC4     ------> USART1_TX
    PC5     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==LPUART1)
  {
  /* USER CODE BEGIN LPUART1_MspDeInit 0 */

  /* USER CODE END LPUART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LPUART1_CLK_DISABLE();
  
    /**LPUART1 GPIO Configuration    
    PA2     ------> LPUART1_TX
    PA3     ------> LPUART1_RX 
    */
    HAL_GPIO_DeInit(GPIOA, LPUART1_TX_Pin|LPUART1_RX_Pin);

    /* LPUART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(LPUART1_IRQn);
  /* USER CODE BEGIN LPUART1_MspDeInit 1 */

  /* USER CODE END LPUART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PC4     ------> USART1_TX
    PC5     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_4|GPIO_PIN_5);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
//UART0 - system UART - UART1
//UART1 - debug UART - LPUART1

#define UART0 huart1

/* !!! NASLEDNJO VRSTICO MORAMO VSTAVITI v funkcijo "void USARTx_IRQHandler(void)" ki se nahaja v filu "stm32xxxx_it.c", vse ostalo pa je potrebno zakomentirati.
				===================>>> extern void Uart_ISR(UART_HandleTypeDef *huart); <<<===================
*/

ring_buffer rx_buffer0 = { { 0 }, 0, 0, 0};
ring_buffer tx_buffer0 = { { 0 }, 0, 0, 0};


ring_buffer *_rx_buffer0;
ring_buffer *_tx_buffer0;

void Ringbuf0_Init(void)
{
  _rx_buffer0 = &rx_buffer0;
  _tx_buffer0 = &tx_buffer0;

//TODO: Enabling this interrupt disables TIMER3 CH2 PWM. Figure out why!
  /* Incilizacija "UART Error" prekinitve: (Frame error, noise error, overrun error) */
//  __HAL_UART_ENABLE_IT(&UART0, UART_IT_ERR);

  /* Incilizacija "UART Data Register not empty" prekinitve */
  __HAL_UART_ENABLE_IT(&UART0, UART_IT_RXNE);
}

void UART0_Init()
{
	  UART0.Instance = USART1;						//Izberemo UART kanal
	  UART0.Init.BaudRate = 115200;				//Izberemo BAUD rate
	  UART0.Init.WordLength = UART_WORDLENGTH_8B;	//Nastavimo Data bite
	  UART0.Init.StopBits = UART_STOPBITS_1;		//Nastavimo Stop bite
	  UART0.Init.Parity = UART_PARITY_NONE;		//nastavimo pariteto
	  UART0.Init.Mode = UART_MODE_TX_RX;
	  UART0.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	  UART0.Init.OverSampling = UART_OVERSAMPLING_16;

}

void store_char(unsigned char c, ring_buffer *buffer)
{
  int i = (unsigned int)(buffer->head + 1) % UART_BUFFER_SIZE;

  if(i != buffer->tail) {
    buffer->buffer[buffer->head] = c;
    buffer->head = i;
    buffer->count++;
  }
}

int UART0_DataReady(void)
{
	return (uint16_t)(UART_BUFFER_SIZE + _rx_buffer0->head - _rx_buffer0->tail) % UART_BUFFER_SIZE;
}

int UART0_SendStr(const char *s)
{
	int i;
	for (i=0; *s; i++)
	{
		if (UART0_put(*s++) != UART_OK) return i;
	}
	return i;
}

int UART0_SendBytes(const char *s, int num)
{
	int i;
	for (i=0; i<num; i++)
	{
		if (UART0_put(*s++) != UART_OK) return i;
	}
	return i;
}

UART_Status_t UART0_put(const char c)
{
	if (c>=0)
		{
			int i = (_tx_buffer0->head + 1) % UART_BUFFER_SIZE;

			//Če je output buffer poln javimo napako
			if(i == _tx_buffer0->tail) return UART_EOF;

			_tx_buffer0->buffer[_tx_buffer0->head] = (uint8_t)c;
			_tx_buffer0->head = i;
			_tx_buffer0->count++;
			__HAL_UART_ENABLE_IT(&UART0, UART_IT_TXE); // Omogočimo UART transmission interrupt
		}
		return UART_OK;
}

UART_Status_t UART0_GetByte(char *data)
{

  //Če head ni pread tail, ni novih znakov
  if(_rx_buffer0->head == _rx_buffer0->tail)
  {
    return UART_EOF;
  }
  else
  {
    *data = _rx_buffer0->buffer[_rx_buffer0->tail];
    _rx_buffer0->tail = (unsigned int)(_rx_buffer0->tail + 1) % UART_BUFFER_SIZE;
    _rx_buffer0->count--;
    return UART_OK;
  }
}

int UART0_numTxBytes()
{
	return _tx_buffer0->count;
}

int UART0_numRxBytes()
{
	return _rx_buffer0->count;
}

void UART_ISR(UART_HandleTypeDef *huart, ring_buffer* rxBuf, ring_buffer* txBuf)
{
	  uint32_t isrflags   = READ_REG(huart->Instance->ISR);
	  uint32_t cr1its     = READ_REG(huart->Instance->CR1);

    /* if DR is not empty and the Rx Int is enabled */
    if (((isrflags & USART_ISR_RXNE) != RESET) && ((cr1its & USART_CR1_RXNEIE) != RESET))
    {
    	 /******************
    	    	      *  @note   PE (Parity error), FE (Framing error), NE (Noise error), ORE (Overrun
    	    	      *          error) and IDLE (Idle line detected) flags are cleared by software
    	    	      *          sequence: a read operation to USART_SR register followed by a read
    	    	      *          operation to USART_DR register.
    	    	      * @note   RXNE flag can be also cleared by a read to the USART_DR register.
    	    	      * @note   TC flag can be also cleared by software sequence: a read operation to
    	    	      *          USART_SR register followed by a write operation to USART_DR register.
    	    	      * @note   TXE flag is cleared only by a write to the USART_DR register.

    	 *********************/
		huart->Instance->ISR;                       /* Read status register */
        unsigned char c = huart->Instance->RDR;     /* Read data register */
        store_char (c, rxBuf);  // store data in buffer
    }

    /*If interrupt is caused due to Transmit Data Register Empty */
    else if (((isrflags & USART_ISR_TXE) != RESET) && ((cr1its & USART_CR1_TXEIE) != RESET))
    {

    	if(txBuf->head == txBuf->tail)
    	    {
    	      // Buffer empty, so disable interrupts
    	      __HAL_UART_DISABLE_IT(huart, UART_IT_TXE);
    	      LED7_Off();

    	    }

    	 else
    	    {
    	      // There is more data in the output buffer. Send the next byte
    	      unsigned char c = txBuf->buffer[txBuf->tail];
    	      txBuf->tail = (txBuf->tail + 1) % UART_BUFFER_SIZE;
    	      txBuf->count--;
    	      /******************
    	      *  @note   PE (Parity error), FE (Framing error), NE (Noise error), ORE (Overrun
    	      *          error) and IDLE (Idle line detected) flags are cleared by software
    	      *          sequence: a read operation to USART_SR register followed by a read
    	      *          operation to USART_DR register.
    	      * @note   RXNE flag can be also cleared by a read to the USART_DR register.
    	      * @note   TC flag can be also cleared by software sequence: a read operation to
    	      *          USART_SR register followed by a write operation to USART_DR register.
    	      * @note   TXE flag is cleared only by a write to the USART_DR register.

    	      *********************/

    	      huart->Instance->ISR;
    	      huart->Instance->TDR = c;

    	    }
    }
}





#define UART1 hlpuart1

/* !!! NASLEDNJO VRSTICO MORAMO VSTAVITI v funkcijo "void USARTx_IRQHandler(void)" ki se nahaja v filu "stm32xxxx_it.c", vse ostalo pa je potrebno zakomentirati.
        ===================>>> extern void Uart_ISR(UART_HandleTypeDef *huart); <<<===================
*/

ring_buffer rx_buffer1 = { { 0 }, 0, 0, 0};
ring_buffer tx_buffer1 = { { 0 }, 0, 0, 0};


ring_buffer *_rx_buffer1;
ring_buffer *_tx_buffer1;

void Ringbuf1_Init(void)
{
  _rx_buffer1 = &rx_buffer1;
  _tx_buffer1 = &tx_buffer1;

//TODO: Enabling this interrupt disables TIMER3 CH2 PWM. Figure out why!
  /* Incilizacija "UART Error" prekinitve: (Frame error, noise error, overrun error) */
//  __HAL_UART_ENABLE_IT(&UART1, UART_IT_ERR);

  /* Incilizacija "UART Data Register not empty" prekinitve */
  __HAL_UART_ENABLE_IT(&UART1, UART_IT_RXNE);
}

void UART1_Init()
{
    UART1.Instance = LPUART1;            //Izberemo UART kanal
    UART1.Init.BaudRate = 115200;       //Izberemo BAUD rate
    UART1.Init.WordLength = UART_WORDLENGTH_8B; //Nastavimo Data bite
    UART1.Init.StopBits = UART_STOPBITS_1;    //Nastavimo Stop bite
    UART1.Init.Parity = UART_PARITY_NONE;   //nastavimo pariteto
    UART1.Init.Mode = UART_MODE_TX_RX;
    UART1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UART1.Init.OverSampling = UART_OVERSAMPLING_16;
}

int UART1_DataReady(void)
{
  return (uint16_t)(UART_BUFFER_SIZE + _rx_buffer1->head - _rx_buffer1->tail) % UART_BUFFER_SIZE;
}

int UART1_SendStr(const char *s)
{
  int i;
  for (i=0; *s; i++)
  {
    if (UART1_put(*s++) != UART_OK) return i;
  }
  return i;
}

int UART1_SendBytes(const char *s, int num)
{
  int i;
  for (i=0; i<num; i++)
  {
    if (UART1_put(*s++) != UART_OK) return i;
  }
  return i;
}

UART_Status_t UART1_put(const char c)
{
  if (c>=0)
    {
      int i = (_tx_buffer1->head + 1) % UART_BUFFER_SIZE;

      //Če je output buffer poln javimo napako
      if(i == _tx_buffer1->tail) return UART_EOF;

      _tx_buffer1->buffer[_tx_buffer1->head] = (uint8_t)c;
      _tx_buffer1->head = i;
      _tx_buffer1->count++;
      __HAL_UART_ENABLE_IT(&UART1, UART_IT_TXE); // Omogočimo UART transmission interrupt
    }
    return UART_OK;
}

UART_Status_t UART1_GetByte(char *data)
{

  //Če head ni pread tail, ni novih znakov
  if(_rx_buffer1->head == _rx_buffer1->tail)
  {
    return UART_EOF;
  }
  else
  {
    *data = _rx_buffer1->buffer[_rx_buffer1->tail];
    _rx_buffer1->tail = (unsigned int)(_rx_buffer1->tail + 1) % UART_BUFFER_SIZE;
    _rx_buffer1->count--;
    return UART_OK;
  }
}

int UART1_numTxBytes()
{
  return _tx_buffer1->count;
}

int UART1_numRxBytes()
{
  return _rx_buffer1->count;
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
