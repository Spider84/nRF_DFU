/*
 * nrf_if.h
 *
 *  Created on: 14 мая 2015 г.
 *      Author: User
 */

#ifndef PROJECT_INC_NRF_IF_H_
#define PROJECT_INC_NRF_IF_H_

#include "stm32f10x.h"

uint16_t NRF_If_Init(void);
uint16_t NRF_If_Erase (uint32_t SectorAddress);
uint16_t NRF_If_Write (uint32_t SectorAddress, uint32_t DataLength);
uint8_t *NRF_If_Read (uint32_t SectorAddress, uint32_t DataLength);

#endif /* PROJECT_INC_NRF_IF_H_ */
