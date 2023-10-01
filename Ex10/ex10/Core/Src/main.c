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
int led_state[12] = {1,1,1,1,1,1,1,1,1,1,1,1};// state array of 12 led (1 is turn off , 0 is turn on)

void display_clock(){
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,led_state[0]);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,led_state[1]);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,led_state[2]);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,led_state[3]);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,led_state[4]);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,led_state[5]);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,led_state[6]);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,led_state[7]);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,led_state[8]);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_13,led_state[9]);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_14,led_state[10]);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,led_state[11]);
}

void clearAllClock(){
	for (int i = 0; i < 12; i++) {
		led_state[i] = 1;
	}
	display_clock(); // Update the display
}

void setNumberOnClock(int num){
	if (num >= 0 && num < 12) {
		led_state[num] = 0;
		display_clock(); // Update the display
	}

//	led_state[num%12] = 0;
//	display_clock();
}

void clearNumberOnClock(int num) {
	if (num >= 0 && num < 12) {
		led_state[num] = 1;
		display_clock(); // Update the display
	}
}



// Function to display the clock
void displayClock(int hours, int minutes, int seconds){
    // Clear the clock
    clearAllClock();

    // Display hours, minutes, and seconds
    setNumberOnClock(hours);   // Display hours on one LED
    setNumberOnClock(minutes); // Display minutes on another LED
    setNumberOnClock(seconds); // Display seconds on another LED
}

// Function to increment time and restart at 00:00 after 12 hours
int hours = 0;
int minutes = 0;
int seconds = 0;
int timeCounter_second = 0;
int timeCounter_minutes = 0;
void incrementTime(int *hours, int *minutes, int *seconds){

	timeCounter_second ++;

	if(timeCounter_second == 5){
		timeCounter_second = 0;
		(*seconds)++;

		if (*seconds >= 12){
			*seconds = 0;
			timeCounter_minutes ++;

			if(timeCounter_minutes == 5){
				timeCounter_minutes = 0;
				(*minutes)++;

				if (*minutes >= 12){
					*minutes = 0;
					(*hours)++;

					if (*hours >= 12){
						*hours = 0;
					}

				}

			}

		}

	}

}


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
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  displayClock(hours, minutes, seconds);
	  incrementTime(&hours, &minutes, &seconds);

	  HAL_Delay(1000);

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
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA3 PA4 PA5 PA6
                           PA7 PA8 PA9 PA10
                           PA11 PA12 PA13 PA14
                           PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
