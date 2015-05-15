/**
  ******************************************************************************
  * @file    stm3210b_eval.h
  * @author  MCD Application Team
  * @version V5.0.1
  * @date    05-March-2012
  * @brief   This file contains definitions for STM3210B_EVAL's Leds, push-buttons
  *          COM ports, SD Card (on SPI), sFLASH (on SPI) and Temperature sensor 
  *          LM75 (on I2C) hardware resources.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32_PROGRAM_H
#define __STM32_PROGRAM_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup Utilities
  * @{
  */

/** @addtogroup STM32_EVAL
  * @{
  */
    
/** @addtogroup STM3210B_EVAL
  * @{
  */ 

/** @addtogroup STM3210B_EVAL_LOW_LEVEL
  * @{
  */
  
/** @defgroup STM3210B_EVAL_LOW_LEVEL_Exported_Types
  * @{
  */
typedef enum 
{
  LED1 = 0,
  LED2 = 1,
  LED3 = 2,
  LED4 = 3
} Led_TypeDef;

typedef enum 
{  
  BUTTON_WAKEUP = 0
} Button_TypeDef;

typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;


typedef enum 
{
  COM1 = 0
} COM_TypeDef;

/**
  * @}
  */

/** @addtogroup STM3210B_EVAL_LOW_LEVEL_LED
  * @{
  */
#define LEDn                             4
#define LED1_PIN                         GPIO_Pin_6
#define LED1_GPIO_PORT                   GPIOC
#define LED1_GPIO_CLK                    RCC_APB2Periph_GPIOC  
  
#define LED2_PIN                         GPIO_Pin_7
#define LED2_GPIO_PORT                   GPIOC
#define LED2_GPIO_CLK                    RCC_APB2Periph_GPIOC  

#define LED3_PIN                         GPIO_Pin_8  
#define LED3_GPIO_PORT                   GPIOC
#define LED3_GPIO_CLK                    RCC_APB2Periph_GPIOC  
  
#define LED4_PIN                         GPIO_Pin_9
#define LED4_GPIO_PORT                   GPIOC
#define LED4_GPIO_CLK                    RCC_APB2Periph_GPIOC  

/**
  * @}
  */ 
  
/** @addtogroup STM3210B_EVAL_LOW_LEVEL_BUTTON
  * @{
  */  
#define BUTTONn                          1

/**
 * @brief Wakeup push-button
 */
#define WAKEUP_BUTTON_PIN                GPIO_Pin_0
#define WAKEUP_BUTTON_GPIO_PORT          GPIOA
#define WAKEUP_BUTTON_GPIO_CLK           RCC_APB2Periph_GPIOA
#define WAKEUP_BUTTON_EXTI_LINE          EXTI_Line0
#define WAKEUP_BUTTON_EXTI_PORT_SOURCE   GPIO_PortSourceGPIOA
#define WAKEUP_BUTTON_EXTI_PIN_SOURCE    GPIO_PinSource0
#define WAKEUP_BUTTON_EXTI_IRQn          EXTI0_IRQn 


/** @addtogroup STM3210B_EVAL_LOW_LEVEL_COM
  * @{
  */
#define COMn                             1

/**
 * @brief Definition for COM port1, connected to USART1
 */ 
#define EVAL_COM1                        USART1
#define EVAL_COM1_CLK                    RCC_APB2Periph_USART1
#define EVAL_COM1_TX_PIN                 GPIO_Pin_9
#define EVAL_COM1_TX_GPIO_PORT           GPIOA
#define EVAL_COM1_TX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define EVAL_COM1_RX_PIN                 GPIO_Pin_10
#define EVAL_COM1_RX_GPIO_PORT           GPIOA
#define EVAL_COM1_RX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define EVAL_COM1_IRQn                   USART1_IRQn

/**
  * @}
  */ 


#define SPI_SPI                       SPI2
#define SPI_SPI_CLK                   RCC_APB1Periph_SPI2
#define SPI_SPI_SCK_PIN               GPIO_Pin_13                 /* PB.13 */
#define SPI_SPI_SCK_GPIO_PORT         GPIOB                       /* GPIOB */
#define SPI_SPI_SCK_GPIO_CLK          RCC_APB2Periph_GPIOB
#define SPI_SPI_MISO_PIN              GPIO_Pin_14                 /* PB.14 */
#define SPI_SPI_MISO_GPIO_PORT        GPIOB                       /* GPIOB */
#define SPI_SPI_MISO_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SPI_SPI_MOSI_PIN              GPIO_Pin_15                 /* PB.16 */
#define SPI_SPI_MOSI_GPIO_PORT        GPIOB                       /* GPIOB */
#define SPI_SPI_MOSI_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SPI_CS_PIN                    GPIO_Pin_12                 /* PB.12 */
#define SPI_CS_GPIO_PORT              GPIOB                       /* GPIOB */
#define SPI_CS_GPIO_CLK               RCC_APB2Periph_GPIOB

/** @addtogroup STM3210B_EVAL_LOW_LEVEL_M25P_FLASH_SPI
  * @{
  */
/**
  * @brief  M25P FLASH SPI Interface pins
  */  
#define sFLASH_SPI                       SPI1
#define sFLASH_SPI_CLK                   RCC_APB2Periph_SPI1
#define sFLASH_SPI_SCK_PIN               GPIO_Pin_5                  /* PA.05 */
#define sFLASH_SPI_SCK_GPIO_PORT         GPIOA                       /* GPIOA */
#define sFLASH_SPI_SCK_GPIO_CLK          RCC_APB2Periph_GPIOA
#define sFLASH_SPI_MISO_PIN              GPIO_Pin_6                  /* PA.06 */
#define sFLASH_SPI_MISO_GPIO_PORT        GPIOA                       /* GPIOA */
#define sFLASH_SPI_MISO_GPIO_CLK         RCC_APB2Periph_GPIOA
#define sFLASH_SPI_MOSI_PIN              GPIO_Pin_7                  /* PA.07 */
#define sFLASH_SPI_MOSI_GPIO_PORT        GPIOA                       /* GPIOA */
#define sFLASH_SPI_MOSI_GPIO_CLK         RCC_APB2Periph_GPIOA
#define sFLASH_CS_PIN                    GPIO_Pin_4                  /* PA.04 */
#define sFLASH_CS_GPIO_PORT              GPIOA                       /* GPIOA */
#define sFLASH_CS_GPIO_CLK               RCC_APB2Periph_GPIOA 

/**
  * @}
  */

/** @defgroup STM3210B_EVAL_LOW_LEVEL_Exported_Functions
  * @{
  */ 
void STM_EVAL_LEDInit(Led_TypeDef Led);
void STM_EVAL_LEDOn(Led_TypeDef Led);
void STM_EVAL_LEDOff(Led_TypeDef Led);
void STM_EVAL_LEDToggle(Led_TypeDef Led);
void STM_EVAL_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode);
uint32_t STM_EVAL_PBGetState(Button_TypeDef Button);
void STM_EVAL_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct);
void sFLASH_LowLevel_DeInit(void);
void sFLASH_LowLevel_Init(void); 
void SPI_LowLevel_Init(void);
void SPI_LowLevel_DeInit(void);
 

/**
  * @}
  */ 
    
#ifdef __cplusplus
}
#endif
  
#endif /* __STM32_PROGRAM_H */
/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */  

/**
  * @}
  */    

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
