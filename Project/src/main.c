/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Virtual Com Port Demo main file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
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
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_prop.h"
#include "usb_pwr.h"
#include "dfu_mal.h"

/* Private typedef -----------------------------------------------------------*/
typedef  void (*pFunction)(void);
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
uint8_t DeviceState;
uint8_t DeviceStatus[6];
pFunction Jump_To_Application;
uint32_t JumpAddress;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : main.
* Description    : Main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int main(void) {
	Set_System();

	STM_EVAL_LEDInit(LED1);
	STM_EVAL_LEDInit(LED2);
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);

	STM_EVAL_LEDOff(LED1);
	STM_EVAL_LEDOff(LED2);
	STM_EVAL_LEDOff(LED3);
	STM_EVAL_LEDOff(LED4);

	STM_EVAL_PBInit(BUTTON_WAKEUP, BUTTON_MODE_EXTI);

	/* Enter DFU mode */
	DeviceState = STATE_dfuERROR;
	DeviceStatus[0] = STATUS_ERRFIRMWARE;
	DeviceStatus[4] = DeviceState;

	Set_System();
	Set_USBClock();
	USB_Init();

	/* Main loop */
	while (1) {
	}
}
#ifdef USE_FULL_ASSERT
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
