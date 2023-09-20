/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

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

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */

  int time_delay_RED = 500;
  int time_delay_YELLOW = 200;
  int time_delay_GREEN = 300;

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 0);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);

  int count_1 = time_delay_RED;
  int count_2 = time_delay_GREEN;
  int status_1 = 1;
  int status_2 = 6;

  /*
   * STATUS 1: RED -> YELLOW -> GREEN
   * 	RED: 	1 - PIN 5
   * 	YELLOW: 2 - PIN 6
   * 	GREEN: 	3 - PIN 7
   *
   * STATUS 2: GREEN -> YELLOW -> RED
   * 	RED: 	4 - PIN 9
   * 	YELLOW: 5 - PIN 10
   * 	GREEN: 	6 - PIN 11
   * */

  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(status_1 == 1){
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);

		  if(status_2 == 6){
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 1);
			  count_2 --;
			  if(count_2 == 0){
				  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, 0);
				  status_2 = 5;
				  count_2 = time_delay_YELLOW;
			  }
		  }
		  else if(status_2 == 5){
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 1);
			  count_2 --;
			  if(count_2 == 0){
				  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, 0);
				  status_2 = 4;
				  count_2 = time_delay_RED;
			  }
		  }

		  count_1 --;

		  if(count_1 == 0){
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
			  status_1 = 2;
			  count_1 = time_delay_YELLOW;
		  }
	  }


	  if(status_2 == 4){
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 1);

		  if(status_1 == 2){
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
			  count_1 --;
			  if(count_1 == 0){
				  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);
				  status_1 = 3;
				  count_1 = time_delay_GREEN;
			  }
		  }
		  else if(status_1 == 3){
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
			  count_1 --;
			  if(count_1 == 0){
				  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
				  status_1 = 1;
				  count_1 = time_delay_RED;
			  }
		  }

		  count_2 --;

		  if(count_2 == 0){
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, 0);
			  status_2 = 6;
			  count_2 = time_delay_GREEN;
		  }
	  }




	  HAL_Delay(10);
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_RED_1_Pin|LED_YELLOW_1_Pin|LED_GREEN_1_Pin|LED_LED_2_Pin
                          |LED_YELLOW_2_Pin|LED_GREEN_2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_RED_1_Pin LED_YELLOW_1_Pin LED_GREEN_1_Pin LED_LED_2_Pin
                           LED_YELLOW_2_Pin LED_GREEN_2_Pin */
  GPIO_InitStruct.Pin = LED_RED_1_Pin|LED_YELLOW_1_Pin|LED_GREEN_1_Pin|LED_LED_2_Pin
                          |LED_YELLOW_2_Pin|LED_GREEN_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
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
