/**
  ******************************************************************************
  * @file    Templates_LL/Src/main.c
  * @author  MCD Application Team
  * @brief   Main program body through the LL API
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
#include "stm32f1xx_ll_rcc.h" // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_utils.h"   // utile dans la fonction SystemClock_Config
#include "stm32f1xx_ll_system.h" // utile dans la fonction SystemClock_Config
#include "bat.h"
#include "Chrono.h"


void  SystemClock_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */

	int x,y,z;
int main(void)
{

  /* Configure the system clock to 72 MHz */
  SystemClock_Config();

  /* Add your application code here */
  // Configuration chronom�tre
	Chrono_Conf(TIM3);
	
	// Lancement chronom�tre
	Chrono_Start();
	
	BAT_init();

	
	
//2.2 manipulation de bits au niveau des registres peripheriques
//voir page 754 ref manuel stm32
/*SPI1->CR1 = 0xFFFF;
SPI1->CR1 &= ~(1<<11); 
SPI1->CR1 |= (1<<1);
//voir page 832 ref manuel stm32
USART1->CR2 = 0xFFFF;
USART1->CR2 &= ~(3<<12);
USART1->CR2 |= (2<<12);*/

  
  /* Infinite loop */
	x=0;
	y=0;
	z=0;
	
  while (1)
  {
  z =  BAT_level();
	x = BAT_verifyLevel();
	
  }
}

// Bato droit x=1477 y=2166
//Bato peu pench� x=1411 y=2151 
//Bato full pench� x=1183 (1251)  y=2047 (2086)
//Bato full pench� autre sens x=1702 (1698) y=2124 (2125) 





/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            PLLMUL                         = 9
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
  /* Set FLASH latency */
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);

  /* Enable HSE oscillator */
	// ********* Commenter la ligne ci-dessous pour MCBSTM32 *****************
	// ********* Conserver la ligne si Nucl�o*********************************
  LL_RCC_HSE_EnableBypass();
  LL_RCC_HSE_Enable();
  while(LL_RCC_HSE_IsReady() != 1)
  {
  };

  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);

  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  };

  /* Sysclk activation on the main PLL */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  };

  /* Set APB1 & APB2 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  /* Set systick to 1ms in using frequency set to 72MHz */
  //LL_Init1msTick(72000000); !! d�commenter que si l'IT est r�cup�r�e

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(72000000);
}



/* ==============   BOARD SPECIFIC CONFIGURATION CODE END      ============== */

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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
