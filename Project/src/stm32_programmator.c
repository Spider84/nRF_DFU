/**
  ******************************************************************************
  * @file    stm3210b_eval.c
  * @author  MCD Application Team
  * @version V5.0.1
  * @date    05-March-2012
  * @brief   This file provides
  *            - set of firmware functions to manage Leds, push-button and COM ports
  *            - low level initialization functions for SD card (on SPI), SPI serial
  *              flash (sFLASH) and temperature sensor (LM75)
  *          available on STM3210B-EVAL evaluation board from STMicroelectronics.    
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
  
/* Includes ------------------------------------------------------------------*/
#include "stm32_program.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup STM32_EVAL
  * @{
  */ 

/** @addtogroup STM3210B_EVAL
  * @{
  */ 
      
/** @defgroup STM3210B_EVAL_LOW_LEVEL 
  * @brief This file provides firmware functions to manage Leds, push-buttons, 
  *        COM ports, SD card on SPI, serial flash (sFLASH), serial EEPROM (sEE) 
  *        and temperature sensor (LM75) available on STM3210B-EVAL evaluation
  *        board from STMicroelectronics.
  * @{
  */ 

/** @defgroup STM3210B_EVAL_LOW_LEVEL_Private_TypesDefinitions
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM3210B_EVAL_LOW_LEVEL_Private_Defines
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM3210B_EVAL_LOW_LEVEL_Private_Macros
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup STM3210B_EVAL_LOW_LEVEL_Private_Variables
  * @{
  */ 
GPIO_TypeDef* GPIO_PORT[LEDn] = {LED1_GPIO_PORT, LED2_GPIO_PORT, LED3_GPIO_PORT,
                                 LED4_GPIO_PORT};
const uint16_t GPIO_PIN[LEDn] = {LED1_PIN, LED2_PIN, LED3_PIN,
                                 LED4_PIN};
const uint32_t GPIO_CLK[LEDn] = {LED1_GPIO_CLK, LED2_GPIO_CLK, LED3_GPIO_CLK,
                                 LED4_GPIO_CLK};

GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {WAKEUP_BUTTON_GPIO_PORT};

const uint16_t BUTTON_PIN[BUTTONn] = {WAKEUP_BUTTON_PIN};

const uint32_t BUTTON_CLK[BUTTONn] = {WAKEUP_BUTTON_GPIO_CLK};

const uint16_t BUTTON_EXTI_LINE[BUTTONn] = {WAKEUP_BUTTON_EXTI_LINE};

const uint16_t BUTTON_PORT_SOURCE[BUTTONn] = {WAKEUP_BUTTON_EXTI_PORT_SOURCE};
								 
const uint16_t BUTTON_PIN_SOURCE[BUTTONn] = {WAKEUP_BUTTON_EXTI_PIN_SOURCE};

const uint16_t BUTTON_IRQn[BUTTONn] = {WAKEUP_BUTTON_EXTI_IRQn};

USART_TypeDef* COM_USART[COMn] = {EVAL_COM1};

GPIO_TypeDef* COM_TX_PORT[COMn] = {EVAL_COM1_TX_GPIO_PORT};
 
GPIO_TypeDef* COM_RX_PORT[COMn] = {EVAL_COM1_RX_GPIO_PORT};
 
const uint32_t COM_USART_CLK[COMn] = {EVAL_COM1_CLK};

const uint32_t COM_TX_PORT_CLK[COMn] = {EVAL_COM1_TX_GPIO_CLK};
 
const uint32_t COM_RX_PORT_CLK[COMn] = {EVAL_COM1_RX_GPIO_CLK};

const uint16_t COM_TX_PIN[COMn] = {EVAL_COM1_TX_PIN};

const uint16_t COM_RX_PIN[COMn] = {EVAL_COM1_RX_PIN};


/**
  * @}
  */ 


/** @defgroup STM3210B_EVAL_LOW_LEVEL_Private_FunctionPrototypes
  * @{
  */ 

/**
  * @}
  */ 


/** @defgroup STM3210B_EVAL_LOW_LEVEL_Private_Functions
  * @{
  */ 

/**
  * @brief  Configures LED GPIO.
  * @param  Led: Specifies the Led to be configured. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void STM_EVAL_LEDInit(Led_TypeDef Led)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the GPIO_LED Clock */
  RCC_APB2PeriphClockCmd(GPIO_CLK[Led], ENABLE);

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN[Led];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIO_PORT[Led], &GPIO_InitStructure);
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4  
  * @retval None
  */
void STM_EVAL_LEDOn(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BRR = GPIO_PIN[Led];
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4 
  * @retval None
  */
void STM_EVAL_LEDOff(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BSRR = GPIO_PIN[Led];
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4  
  * @retval None
  */
void STM_EVAL_LEDToggle(Led_TypeDef Led)
{
  GPIO_PORT[Led]->ODR ^= GPIO_PIN[Led];
}

/**
  * @brief  Configures Button GPIO and EXTI Line.
  * @param  Button: Specifies the Button to be configured.
  *   This parameter can be one of following parameters:   
  *     @arg BUTTON_WAKEUP: Wakeup Push Button
  *     @arg BUTTON_TAMPER: Tamper Push Button  
  *     @arg BUTTON_KEY: Key Push Button 
  *     @arg BUTTON_RIGHT: Joystick Right Push Button 
  *     @arg BUTTON_LEFT: Joystick Left Push Button 
  *     @arg BUTTON_UP: Joystick Up Push Button 
  *     @arg BUTTON_DOWN: Joystick Down Push Button
  *     @arg BUTTON_SEL: Joystick Sel Push Button
  * @param  Button_Mode: Specifies Button mode.
  *   This parameter can be one of following parameters:   
  *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO 
  *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
  *                     generation capability  
  * @retval None
  */
void STM_EVAL_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the BUTTON Clock */
  RCC_APB2PeriphClockCmd(BUTTON_CLK[Button] | RCC_APB2Periph_AFIO, ENABLE);

  /* Configure Button pin as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = BUTTON_PIN[Button];
  GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStructure);


  if (Button_Mode == BUTTON_MODE_EXTI)
  {
    /* Connect Button EXTI Line to Button GPIO Pin */
    GPIO_EXTILineConfig(BUTTON_PORT_SOURCE[Button], BUTTON_PIN_SOURCE[Button]);

    /* Configure Button EXTI line */
    EXTI_InitStructure.EXTI_Line = BUTTON_EXTI_LINE[Button];
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;

    if(Button != BUTTON_WAKEUP)
    {
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
    }
    else
    {
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
    }
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Enable and set Button EXTI Interrupt to the lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = BUTTON_IRQn[Button];
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure); 
  }
}

/**
  * @brief  Returns the selected Button state.
  * @param  Button: Specifies the Button to be checked.
  *   This parameter can be one of following parameters:    
  *     @arg BUTTON_WAKEUP: Wakeup Push Button
  *     @arg BUTTON_TAMPER: Tamper Push Button  
  *     @arg BUTTON_KEY: Key Push Button 
  *     @arg BUTTON_RIGHT: Joystick Right Push Button 
  *     @arg BUTTON_LEFT: Joystick Left Push Button 
  *     @arg BUTTON_UP: Joystick Up Push Button 
  *     @arg BUTTON_DOWN: Joystick Down Push Button
  *     @arg BUTTON_SEL: Joystick Sel Push Button    
  * @retval The Button GPIO pin value.
  */
uint32_t STM_EVAL_PBGetState(Button_TypeDef Button)
{
  return GPIO_ReadInputDataBit(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

/**
  * @brief  Configures COM port.
  * @param  COM: Specifies the COM port to be configured.
  *   This parameter can be one of following parameters:    
  *     @arg COM1
  *     @arg COM2  
  * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure that
  *   contains the configuration information for the specified USART peripheral.
  * @retval None
  */
void STM_EVAL_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIO clock */
  RCC_APB2PeriphClockCmd(COM_TX_PORT_CLK[COM] | COM_RX_PORT_CLK[COM] | RCC_APB2Periph_AFIO, ENABLE);

  if (COM == COM1)
  {
    RCC_APB2PeriphClockCmd(COM_USART_CLK[COM], ENABLE); 
  }
  else
  {
    /* Enable the USART2 Pins Software Remapping */
    GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
    RCC_APB1PeriphClockCmd(COM_USART_CLK[COM], ENABLE);
  }

  /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = COM_TX_PIN[COM];
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(COM_TX_PORT[COM], &GPIO_InitStructure);


  /* Configure USART Rx as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = COM_RX_PIN[COM];
  GPIO_Init(COM_RX_PORT[COM], &GPIO_InitStructure);

  /* USART configuration */
  USART_Init(COM_USART[COM], USART_InitStruct);
    
  /* Enable USART */
  USART_Cmd(COM_USART[COM], ENABLE);
}

/**
  * @brief  DeInitializes the SD/SD communication.
  * @param  None
  * @retval None
  */
void SPI_LowLevel_DeInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  SPI_Cmd(SPI_SPI, DISABLE); /*!< SPI_SPI disable */
  SPI_I2S_DeInit(SPI_SPI);   /*!< DeInitializes the SPI_SPI */
  
  /*!< SPI_SPI Periph clock disable */
  RCC_APB2PeriphClockCmd(SPI_SPI_CLK, DISABLE);
  
  /*!< Configure SPI_SPI pins: SCK */
  GPIO_InitStructure.GPIO_Pin = SPI_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(SPI_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure SPI_SPI pins: MISO */
  GPIO_InitStructure.GPIO_Pin = SPI_SPI_MISO_PIN;
  GPIO_Init(SPI_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure SPI_SPI pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = SPI_SPI_MOSI_PIN;
  GPIO_Init(SPI_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure SPI_SPI_CS_PIN pin: SD Card CS pin */
  GPIO_InitStructure.GPIO_Pin = SPI_CS_PIN;
  GPIO_Init(SPI_CS_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  Initializes the SPI_SPI and CS pins.
  * @param  None
  * @retval None
  */
void SPI_LowLevel_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  SPI_InitTypeDef   SPI_InitStructure;

  /*!< SPI_SPI_CS_GPIO, SPI_SPI_MOSI_GPIO, SPI_SPI_MISO_GPIO, SPI_SPI_DETECT_GPIO
       and SPI_SPI_SCK_GPIO Periph clock enable */
  RCC_APB2PeriphClockCmd(SPI_CS_GPIO_CLK | SPI_SPI_MOSI_GPIO_CLK | SPI_SPI_MISO_GPIO_CLK | SPI_SPI_SCK_GPIO_CLK, ENABLE);

  /*!< SPI_SPI Periph clock enable */
  RCC_APB1PeriphClockCmd(SPI_SPI_CLK, ENABLE);

  
  /*!< Configure SPI_SPI pins: SCK */
  GPIO_InitStructure.GPIO_Pin = SPI_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(SPI_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure SPI_SPI pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = SPI_SPI_MOSI_PIN;
  GPIO_Init(SPI_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure SPI_SPI pins: MISO */
  GPIO_InitStructure.GPIO_Pin = SPI_SPI_MISO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
  GPIO_Init(SPI_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);
  
  /*!< Configure SPI_SPI_CS_PIN pin: SD Card CS pin */
  GPIO_InitStructure.GPIO_Pin = SPI_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(SPI_CS_GPIO_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /*!< SPI_SPI Config */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI_SPI, &SPI_InitStructure);
  
  SPI_NSSInternalSoftwareConfig(SPI_SPI, SPI_NSSInternalSoft_Set);

  SPI_Cmd(SPI_SPI, ENABLE); /*!< SPI_SPI enable */
}

/**
  * @brief  DeInitializes the peripherals used by the SPI FLASH driver.
  * @param  None
  * @retval None
  */
void sFLASH_LowLevel_DeInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /*!< Disable the sFLASH_SPI  */
  SPI_Cmd(sFLASH_SPI, DISABLE);
  
  /*!< DeInitializes the sFLASH_SPI */
  SPI_I2S_DeInit(sFLASH_SPI);
  
  /*!< sFLASH_SPI Periph clock disable */
  RCC_APB2PeriphClockCmd(sFLASH_SPI_CLK, DISABLE);
  
  /*!< Configure sFLASH_SPI pins: SCK */
  GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(sFLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure sFLASH_SPI pins: MISO */
  GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_MISO_PIN;
  GPIO_Init(sFLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure sFLASH_SPI pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_MOSI_PIN;
  GPIO_Init(sFLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure sFLASH_CS_PIN pin: sFLASH Card CS pin */
  GPIO_InitStructure.GPIO_Pin = sFLASH_CS_PIN;
  GPIO_Init(sFLASH_CS_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  Initializes the peripherals used by the SPI FLASH driver.
  * @param  None
  * @retval None
  */
void sFLASH_LowLevel_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /*!< sFLASH_SPI_CS_GPIO, sFLASH_SPI_MOSI_GPIO, sFLASH_SPI_MISO_GPIO 
       and sFLASH_SPI_SCK_GPIO Periph clock enable */
  RCC_APB2PeriphClockCmd(sFLASH_CS_GPIO_CLK | sFLASH_SPI_MOSI_GPIO_CLK | sFLASH_SPI_MISO_GPIO_CLK |
                         sFLASH_SPI_SCK_GPIO_CLK, ENABLE);

  /*!< sFLASH_SPI Periph clock enable */
  RCC_APB2PeriphClockCmd(sFLASH_SPI_CLK, ENABLE);
  
  /*!< Configure sFLASH_SPI pins: SCK */
  GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(sFLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure sFLASH_SPI pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_MOSI_PIN;
  GPIO_Init(sFLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure sFLASH_SPI pins: MISO */
  GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_MISO_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
  GPIO_Init(sFLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);
  
  /*!< Configure sFLASH_CS_PIN pin: sFLASH Card CS pin */
  GPIO_InitStructure.GPIO_Pin = sFLASH_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(sFLASH_CS_GPIO_PORT, &GPIO_InitStructure);
}


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
