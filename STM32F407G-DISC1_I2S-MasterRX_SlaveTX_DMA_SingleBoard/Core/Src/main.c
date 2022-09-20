/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdio.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define numdata  300

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2S_HandleTypeDef hi2s2;
I2S_HandleTypeDef hi2s3;
DMA_HandleTypeDef hdma_spi2_rx;
DMA_HandleTypeDef hdma_spi3_tx;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

uint16_t send_data2[numdata], errorcode, have_error, num_error = 0;
uint16_t receive_data2[numdata];

uint16_t send_data1[numdata];
uint16_t receive_data1[numdata];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2S2_Init(void);
static void MX_I2S3_Init(void);
/* USER CODE BEGIN PFP */

#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

/* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_I2S2_Init();
  MX_I2S3_Init();
  /* USER CODE BEGIN 2 */

	printf("Starting >> STM32F407G-DISC1_SPI-MasterRX_SlaveTX_DMA_SingleBoard \n");
	printf("before HAL_SPI_TransmitReceive_DMA \n");

//	// fill data to be transmitted (optional)
//	for(uint16_t cntr = 0; cntr < numdata; cntr++)
//		send_data2[cntr] = cntr;

	// fill data to be transmitted
	for(uint16_t cntr = 0; cntr < numdata; cntr++)
		send_data1[cntr] = cntr;

	// print data to be transmitted
	printf("send_data1 Buffer \n");
	for(uint16_t cntr = 0; cntr < numdata; cntr++)
		printf("%d = %d \n", cntr, send_data1[cntr]);

//	// print data to be transmitted (optional)
//	printf("send_data2 Buffer \n");
//	for(uint16_t cntr = 0; cntr < numdata; cntr++)
//		printf("%d = %d \n", cntr, send_data2[cntr]);

	// print data before receive
	printf("receive_data1 Buffer \n");
	for(uint16_t cntr = 0; cntr < numdata; cntr++)
		printf("%d = %d \n", cntr, receive_data1[cntr]);

//	// print data before receive (optional)
//	printf("receive_data2 Buffer \n");
//	for(uint16_t cntr = 0; cntr < numdata; cntr++)
//		printf("%d = %d \n", cntr, receive_data2[cntr]);

	// this is for SPI slave transmit to prepare to transmit
	// it will not transmit immediately because it is a slave
	HAL_I2S_Transmit_DMA(&hi2s3, send_data1, numdata);

	// this is for SPI master receive
	// it will  transmit immediately because it is the master
	HAL_I2S_Receive_DMA(&hi2s2, receive_data1, numdata);

	printf("after HAL_SPI_TransmitReceive_DMA \n");

	// need this much delay becoz when checking and comparing the for loop below, the DMA is not yet finished
	HAL_Delay(8);

	// check if transmitted data is equal to received data
	for(uint16_t cntr = 0; cntr < numdata; cntr++)
	{
		if (send_data1[cntr] != receive_data1[cntr])
			num_error++;
	}
//	if (have_error == 1)
//	{
//		errorcode = 1;
//		have_error = 0;
//	}


//	for(uint16_t cntr = 0; cntr < numdata; cntr++)
//	{
//		if (!(send_data1[cntr] == receive_data1[cntr]))
//			have_error = 1;
//	}
//	if (have_error == 1)
//	{
//		errorcode = errorcode + 2;
//		have_error = 1;
//	}

	printf("receive_data1 Buffer \n");
	for(uint16_t cntr = 0; cntr < numdata; cntr++)
		printf("%d = %d \n", cntr, receive_data1[cntr]);

//	printf("receive_data2 Buffer \n");
//	for(uint16_t cntr = 0; cntr < numdata; cntr++)
//		printf("%d = %d \n", cntr, receive_data2[cntr]);

	HAL_Delay(100);

	printf("num_error = %d \n", num_error);
	printf("Ending >> STM32F407G-DISC1_SPI-MasterRX_SlaveTX_DMA_SingleBoard \n");

	if (have_error)
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, SET);
	else
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, SET);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 210;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
  PeriphClkInitStruct.PLLI2S.PLLI2SN = 192;
  PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2S2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2S2_Init(void)
{

  /* USER CODE BEGIN I2S2_Init 0 */

  /* USER CODE END I2S2_Init 0 */

  /* USER CODE BEGIN I2S2_Init 1 */

  /* USER CODE END I2S2_Init 1 */
  hi2s2.Instance = SPI2;
  hi2s2.Init.Mode = I2S_MODE_MASTER_RX;
  hi2s2.Init.Standard = I2S_STANDARD_PHILIPS;
  hi2s2.Init.DataFormat = I2S_DATAFORMAT_16B;
  hi2s2.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
  hi2s2.Init.AudioFreq = I2S_AUDIOFREQ_16K;
  hi2s2.Init.CPOL = I2S_CPOL_HIGH;
  hi2s2.Init.ClockSource = I2S_CLOCK_PLL;
  hi2s2.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;
  if (HAL_I2S_Init(&hi2s2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2S2_Init 2 */

  /* USER CODE END I2S2_Init 2 */

}

/**
  * @brief I2S3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2S3_Init(void)
{

  /* USER CODE BEGIN I2S3_Init 0 */

  /* USER CODE END I2S3_Init 0 */

  /* USER CODE BEGIN I2S3_Init 1 */

  /* USER CODE END I2S3_Init 1 */
  hi2s3.Instance = SPI3;
  hi2s3.Init.Mode = I2S_MODE_SLAVE_TX;
  hi2s3.Init.Standard = I2S_STANDARD_PHILIPS;
  hi2s3.Init.DataFormat = I2S_DATAFORMAT_16B;
  hi2s3.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
  hi2s3.Init.AudioFreq = I2S_AUDIOFREQ_16K;
  hi2s3.Init.CPOL = I2S_CPOL_HIGH;
  hi2s3.Init.ClockSource = I2S_CLOCK_PLL;
  hi2s3.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;
  if (HAL_I2S_Init(&hi2s3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2S3_Init 2 */

  /* USER CODE END I2S3_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);
  /* DMA1_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PB10 */
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : PB4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the LPUART1 and Loop until the end of transmission */
	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);

	return ch;
}

//void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
//{
//	UNUSED(hspi);
//
//	printf("HAL_SPI_RxCpltCallback \n");
//}
//
//void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *hspi)
//{
//	UNUSED(hspi);
//
//	printf("HAL_SPI_RxHalfCpltCallback \n");
//}
//
//void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
//{
//	UNUSED(hspi);
//
//	printf("HAL_SPI_TxCpltCallback \n");
//}
//
//void HAL_SPI_TxHalfCpltCallback(SPI_HandleTypeDef *hspi)
//{
//	UNUSED(hspi);
//
//	printf("HAL_SPI_TxHalfCpltCallback \n");
//}
//
//void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
//{
//	UNUSED(hspi);
//
//	printf("HAL_SPI_TxRxCpltCallback \n");
//}
//
//void HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *hspi)
//{
//	UNUSED(hspi);
//
//	printf("HAL_SPI_TxRxHalfCpltCallback \n");
//}
//
//void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
//{
//	UNUSED(hspi);
//
//	printf("HAL_SPI_ErrorCallback : Error code %d \n", hspi->ErrorCode);
//
//}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	printf("Error_Handler \n");
	__disable_irq();
	while (1)
	{
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
