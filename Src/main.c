/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2015 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "dcmi.h"
#include "dma.h"
#include "dma2d.h"
#include "i2c.h"
#include "ltdc.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"

/* USER CODE BEGIN Includes */
#include "tvp5150.h"
#include "svga050.h"
#include "graph.h"
#include "itg3200.h"
#include "graph.h"
#include "hmc5883.h"
#include "adxl345.h"
#include "compas.h"
#include "clinometer.h"
#include "guage.h"


/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
char bufStr[50] = "";
const char *directions[17]={"N","NNE","NE","ENE","E","ESE","SE","SSE","S","SSW","SW","WSW","W","WNW","NW","NNW","N"};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
  ITG_XYZ_StructTypeDef ixyz;
  uint32_t cur_tick, tmp_tick;
  HMC_ID_StructTypeDef hres;
  uint8_t r, temp;
  int32_t tmp;
  float angl;

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_DCMI_Init();
  MX_DMA2D_Init();
  MX_FMC_Init();
  MX_I2C1_Init();
  MX_LTDC_Init();
  MX_USART1_UART_Init();

  /* USER CODE BEGIN 2 */
	SDRAM_Init(&hsdram1);
	//if (SDRAM_Init(&hsdram1)) GPIO_TOGGLE(GPIOG, GPIO_PIN_14);

	SVGA_Init();
	//ILI9341_Init();
	GRPH_Init();
	
	HMC_Init(HMC_MR_CMM, HMC_DR_15, HMC_MM_Normal, HMC_GS_4_0, HMC_SS_1);
	ITG_Init(ITG_DLPF_20_1, 0, ITG_CLK_GyroX);
	ADXL_Init();

	HAL_LTDC_SetAlpha(&hltdc, 255, 0);
	HAL_LTDC_SetAlpha(&hltdc, 0, 1);
	
	DMA2DGRPH_Fill();

	DrawCompas(22, 297, 20, 0, 0);
	DrawClinometer(64, 297, 20, 0, 0);
	DrawGuageAbsolut(88, 297, 20, 100, 0, GRPH_COLOR_RED);	

	//GRPH_SetXY(100, 150);
	//GRPH_Puts(str);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	cur_tick = HAL_GetTick();
	if (cur_tick - tmp_tick > 200){

		r = ITG_GetChipAddr();
		ITG_GetXYZ(&ixyz);
		temp = ITG_GetTemperature();
		temp = ITG_ConvTemp(temp);
		sprintf(bufStr, "%02x %6d; %6d; %6d; %3d", r, ixyz.X, ixyz.Y, ixyz.Z, temp);		
		GRPH_SetXY(2, 3);
		GRPH_Puts(bufStr);
			
			
		HMC_GetId(&hres);
		HMC_GetXYZ(&ixyz);
		sprintf(bufStr, "%c%c%c %5d; %6d; %6d", hres.VALA, hres.VALB, hres.VALC, ixyz.X, ixyz.Y, ixyz.Z);		
		GRPH_SetXY(2, 14);
		GRPH_Puts(bufStr);
    		DrawCompas(22, 297, 20, ixyz.X, ixyz.Y);
						
		angl = 270 + atan2(ixyz.Y, ixyz.X) * 180 /3.14;
		if (angl > 360) angl -= 360;
		tmp = (angl + 11)/22.5;
		sprintf(bufStr, "%4.1f %s      ", angl, directions[tmp]);		
		GRPH_SetXY(2, 180);
		GRPH_Puts(bufStr);

		r = ADXL_GetDeviceId();
		ADXL_GetXYZ(&ixyz);
		sprintf(bufStr, "%x %6d; %6d; %6d", r, ixyz.X, ixyz.Y, ixyz.Z);		
		GRPH_SetXY(2, 38);
		GRPH_Puts(bufStr);
		DrawClinometer(64, 297, 20, ixyz.Y, ixyz.Y);
			
			
		GPIO_TOGGLE(GPIOG, GPIO_PIN_13);
		tmp_tick = cur_tick;
	}
		
	//HAL_Delay(100);
		

  }
  /* USER CODE END s3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 301;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  HAL_PWREx_ActivateOverDrive();

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1
                              |RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 170;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_4;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
