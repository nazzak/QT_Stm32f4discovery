/**
 ******************************************************************************
 * @file    main.c
 * @author  Nazim SAIBI
 * @version V1.0
 * @date    01-September-2017
 * @brief   LEDs handler with UART and Qt application in non blocking mode (IT)
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"

void SystemClock_Config(void);

/* UART handler declaration */
UART_HandleTypeDef UartHandle;	//Declare a UART_HandleTypeDef handle structure.
volatile ITStatus UartReady = RESET;

/* Buffer used for Tx and Rx */
uint8_t aTxBuffer[4], aRxBuffer[4];

/* Private function prototypes -----------------------------------------------*/
static void Error_Handler(void);
static int16_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
static void RunningLight(void);
static void LedHandler(void);
void HAL_UART_MspInit(UART_HandleTypeDef *huart);


int main(void) {

	/* STM32F4xx HAL library initialization:
	 - Configure the Flash prefetch, instruction and Data caches
	 - Configure the Systick to generate an interrupt each 1 msec
	 - Set NVIC Group Priority to 4
	 - Global MSP (MCU Support Package) initialization
	 */
	HAL_Init();

	//SystemClock_Config();

	/* Configure LED3, LED4, LED5 and LED6 */
	BSP_LED_Init(LED3); BSP_LED_Init(LED4); BSP_LED_Init(LED5); BSP_LED_Init(LED6);

	/* my request */
	uint8_t RUNNINGLIGHT[] = "2222";

	/*##-1- Configure the UART peripheral ######################################*/
	/* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	/* UART1 configured as follow:
	 - Word Length = 8 Bits
	 - Stop Bit = One Stop bit
	 - Parity = None
	 - BaudRate = 115200 baud
	 - Hardware flow control disabled (RTS and CTS signals) */

	UartHandle.Instance = USART2;
	UartHandle.Init.BaudRate = 115200;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits = UART_STOPBITS_1;
	UartHandle.Init.Parity = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&UartHandle) != HAL_OK) {			//page 943
		Error_Handler();
	}

	//reset LEDs
	BSP_LED_Off(LED3); BSP_LED_Off(LED4); BSP_LED_Off(LED5); BSP_LED_Off(LED6);

	/* Reset transmission flag */
	UartReady = RESET;

	/* Infinite loop */
	while (1) {
		/*##-4- Put UART peripheral in reception process ###########################*/
		if (HAL_UART_Receive_IT(&UartHandle, (uint8_t *) aRxBuffer, 4)
				!= HAL_OK) {
			Error_Handler();
		}

		/*##-5- Wait for the end of the transfer ###################################*/
		while (UartReady != SET) {
		}

		/* Reset transmission flag */
		UartReady = RESET;

		if (Buffercmp((uint8_t*) RUNNINGLIGHT, (uint8_t*) aRxBuffer, 4) == -1) {
			RunningLight();
		}

		LedHandler();

		if (HAL_UART_Transmit_IT(&UartHandle, (uint8_t*) aTxBuffer, 4)
				!= HAL_OK) {
			Error_Handler();
		}

		while (UartReady != SET) {
		}

		UartReady = RESET;
	}
}

/**
 * UART MSP Initialization
 *        This function configures the hardware resources used in this example:
 *           - Peripheral's clock enable
 *           - Peripheral's GPIO Configuration
 *           - NVIC configuration for UART interrupt request enable
 * huart: UART handle pointer
 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart) {
	GPIO_InitTypeDef GPIO_InitStruct;

	/* Enable USART2 clock */
	__HAL_RCC_USART2_CLK_ENABLE();
	/* Enable GPIO TX/RX clock */
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/* UART TX GPIO pin configuration  */
	GPIO_InitStruct.Pin = GPIO_PIN_2;		//page 47 (STM32F407 datasheet)
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;  //or : GPIO_NOPULL
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;	//page 408

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* UART RX GPIO pin configuration  */
	GPIO_InitStruct.Pin = GPIO_PIN_3;		//page 47 (STM32F407 datasheet)

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* NVIC for USART2 */
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 1); //Configure the USARTx interrupt priority.
	HAL_NVIC_EnableIRQ(USART2_IRQn);	//Enable the NVIC USART IRQ handle
}

/**
 * Compares two buffers.
 * pBuffer1, pBuffer2: buffers to be compared.
 * BufferLength: buffer's length
 * 0  : pBuffer1 identical to pBuffer2
 * >0 : pBuffer1 differs from pBuffer2
 */
static int16_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2,
		uint16_t BufferLength) {
	while (BufferLength--) {
		if ((*pBuffer1) != *pBuffer2) {
			return BufferLength;
		}
		pBuffer1++;
		pBuffer2++;
	}

	return -1;
}

/**
 * Activate the running light
 */
static void RunningLight(void) {
	BSP_LED_Off(LED3); BSP_LED_Off(LED4); BSP_LED_Off(LED5); BSP_LED_Off(LED6);
	for(int i=0;i<4;++i)
	{
	HAL_Delay(50); BSP_LED_On(i); HAL_Delay(50); BSP_LED_Off(i);
	}
	aTxBuffer[0] =  aTxBuffer[1] =  aTxBuffer[2] =  aTxBuffer[3] = '0';
}

/**
 * LEDs handler
 */
static void LedHandler(void) {
	if (aRxBuffer[0] == '1') {
		BSP_LED_On(LED3);
		aTxBuffer[0] = '1';
	} else if (aRxBuffer[0] == '0') {
		BSP_LED_Off(LED3);
		aTxBuffer[0] = '0';
	}

	if (aRxBuffer[1] == '1') {
		BSP_LED_On(LED4);
		aTxBuffer[1] = '1';
	} else if (aRxBuffer[1] == '0') {
		BSP_LED_Off(LED4);
		aTxBuffer[1] = '0';
	}

	if (aRxBuffer[2] == '1') {
		BSP_LED_On(LED5);
		aTxBuffer[2] = '1';
	} else if (aRxBuffer[2] == '0') {
		BSP_LED_Off(LED5);
		aTxBuffer[2] = '0';
	}

	if (aRxBuffer[3] == '1') {
		BSP_LED_On(LED6);
		aTxBuffer[3] = '1';
	} else if (aRxBuffer[3] == '0') {
		BSP_LED_Off(LED6);
		aTxBuffer[3] = '0';
	}
}

/**
 * Tx Transfer completed callback
 * UartHandle: UART handle.
 * This example shows a simple way to report end of IT Tx transfer, and
 *         you can add your own implementation.
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle) {
	/* Set transmission flag: transfer complete */
	UartReady = SET;
}

/**
 * Rx Transfer completed callback
 * UartHandle: UART handle
 * This example shows a simple way to report end of IT Rx transfer, and
 *         you can add your own implementation.
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle) {
	/* Set transmission flag: transfer complete */
	UartReady = SET;
}

/**
 * UART error callbacks
 * UartHandle: UART handle
 * This example shows a simple way to report transfer error, and you can
 * add your own implementation.
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle) {
	/* Turn LED3 on: Transfer error in reception/transmission process */
	BSP_LED_On(LED3);
}

/**
 * This function is executed in case of error occurrence.
 */
static void Error_Handler(void) {
	/* Turn LED4 on */
	BSP_LED_On(LED4);
	for(;;);
}



/**
 * UART MSP De-Initialization
 *        This function frees the hardware resources used in this example:
 *          - Disable the Peripheral's clock
 *          - Revert GPIO and NVIC configuration to their default state
 * huart: UART handle pointer
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart) {
	/*##-1- Reset peripherals ##################################################*/
	__HAL_RCC_USART2_FORCE_RESET();
	__HAL_RCC_USART2_RELEASE_RESET();

	/*##-2- Disable peripherals and GPIO Clocks #################################*/
	/* Configure UART Tx as alternate function  */
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2);
	/* Configure UART Rx as alternate function  */
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_3);

	/*##-3- Disable the NVIC for UART ##########################################*/
	HAL_NVIC_DisableIRQ(USART2_IRQn);
}

/**
 * Example of Clock setting, but not used in this program
 */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  // Enable Power Control clock
  __PWR_CLK_ENABLE();

  // The voltage scaling allows optimizing the power consumption when the
  // device is clocked below the maximum system frequency, to update the
  // voltage scaling value regarding system frequency refer to product
  // datasheet.
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  // Enable HSE Oscillator and activate PLL with HSE as source
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;

  // This assumes the HSE_VALUE is a multiple of 1MHz. If this is not
  // your case, you have to recompute these PLL constants.
  RCC_OscInitStruct.PLL.PLLM = (HSE_VALUE/1000000u);
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  // Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
  // clocks dividers
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK
      | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}
