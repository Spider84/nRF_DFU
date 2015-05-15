/*
 * nrf_if.c
 *
 *  Created on: 14 мая 2015 г.
 *      Author: User
 */

#include "hw_config.h"
#include "nrf_if.h"
#include "dfu_mal.h"

void NRF_If_SetProg(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_10);
}

void NRF_If_ResetProg(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_10);
}

void NRF_If_SetCS(void)
{
	GPIO_ResetBits(SPI_CS_GPIO_PORT,SPI_CS_PIN);
}

void NRF_If_ResetCS(void)
{
	GPIO_SetBits(SPI_CS_GPIO_PORT,SPI_CS_PIN);
}

uint8_t NRF_If_SendByte(uint8_t byte)
{
	/*!< Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(SPI_SPI, SPI_I2S_FLAG_TXE) == RESET);
	/*!< Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(SPI_SPI, byte);
	/*!< Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(SPI_SPI, SPI_I2S_FLAG_RXNE) == RESET);
    /*!< Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData(SPI_SPI);
}

uint16_t NRF_If_Init(void)
{
  SPI_LowLevel_Init();

  NRF_If_ResetCS();
  NRF_If_ResetProg();

  return MAL_OK;
}

static inline void NRF_Delay_100ms(void)
{
	for (uint32_t i=0;i<0x67669;i++);
}

static inline void NRF_Delay_10ms(void)
{
	for (uint32_t i=0;i<0xA570;i++);
}

uint8_t NRF_If_WREN(void)
{
	NRF_If_SetCS();
	NRF_If_SendByte(0x06); //WREN
	NRF_If_ResetCS();
	return 1;
}

uint8_t NRF_If_WRDIS(void)
{
	NRF_If_SetCS();
	NRF_If_SendByte(0x04); //WRDIS
	NRF_If_ResetCS();
	return 1;
}

uint8_t NRF_If_GetRDSR(void)
{
	uint8_t rdsr=0xFF;

	NRF_If_SetCS();
	NRF_If_SendByte(0x05); //RDSR
	rdsr = NRF_If_SendByte(0xFF);
	NRF_If_ResetCS();
	return rdsr;
}

void NRF_If_ErasePage(uint8_t page)
{
	NRF_If_SetCS();
	NRF_If_SendByte(0x52); //ERASE PAGE
	NRF_If_SendByte(page); //PAGE
	NRF_If_ResetCS();
}

uint16_t NRF_If_Erase(uint32_t SectorAddress)
{
	uint16_t r_addr = SectorAddress & 0x3FFF;
	uint8_t sector = r_addr/0x200;
	uint8_t rdsr = 0xFF;

	STM_EVAL_LEDOn(LED3);

	NRF_If_SetProg();
	NRF_If_WREN();
	for (uint8_t timeout=0;timeout<100;timeout++)
	{
		//NRF_Delay_10ms();
		rdsr = NRF_If_GetRDSR();
		if (rdsr & 0x10) continue;
		if (rdsr & 0x20) break;
		else if (timeout>=99) return MAL_FAIL;
	}

	NRF_If_ErasePage(sector);

	for (uint8_t timeout=0;timeout<100;timeout++) {
		NRF_Delay_10ms();
		rdsr = NRF_If_GetRDSR();
		if (rdsr & 0x10) continue;
		if (!(rdsr & 0x20)) break;
		if (timeout>=99) return MAL_FAIL;
	}

	NRF_If_ResetProg();

	STM_EVAL_LEDOff(LED3);
	return MAL_OK;
}

uint16_t NRF_If_Write(uint32_t SectorAddress, uint32_t DataLength)
{
	uint16_t w_addr = SectorAddress & 0x3FFF;
	uint8_t *pBuffer = &MAL_Buffer[0];
	uint8_t pages = (((uint16_t)DataLength) >> 10);

	if (((uint16_t)DataLength)-(pages<<10)) {
		pages++;
	}

	STM_EVAL_LEDOn(LED2);

	NRF_If_SetProg();
	for (uint8_t i=0;i<pages;i++) {
		uint16_t wLen = ((uint16_t)DataLength)-(i<<10);
		if (wLen>1024) wLen=1024;

		NRF_If_WREN();
		for (uint8_t timeout=0;timeout<100;timeout++)
		{
			uint8_t rdsr = NRF_If_GetRDSR();
			if (rdsr & 0x10) continue;
			if (rdsr & 0x20) break;
			else if (timeout>=99) goto fail;
		}

		NRF_If_SetCS();
		NRF_If_SendByte(0x02); //PROGRAM
		NRF_If_SendByte(w_addr>>8);
		NRF_If_SendByte(w_addr & 0xFF);

		w_addr+=wLen;

		while (wLen--) NRF_If_SendByte(*pBuffer++);

		NRF_If_ResetCS();

		for (uint8_t timeout=0;timeout<100;timeout++) {
				NRF_Delay_10ms();
				uint8_t rdsr = NRF_If_GetRDSR();
				if (rdsr & 0x10) continue;
				if (!(rdsr & 0x20)) break;
				if (timeout>=99) goto fail;
		}
	}
	NRF_If_ResetProg();
	STM_EVAL_LEDOff(LED2);
	return MAL_OK;
fail:
	NRF_If_ResetProg();
	STM_EVAL_LEDOff(LED2);
	return MAL_FAIL;
}

uint8_t *NRF_If_Read(uint32_t SectorAddress, uint32_t DataLength)
{
  uint16_t r_addr = SectorAddress & 0x3FFF;
  uint8_t *pBuffer = MAL_Buffer;

  STM_EVAL_LEDOn(LED4);

  NRF_If_SetProg();
  NRF_If_SetCS();
  NRF_If_SendByte(0x03); //READ
  NRF_If_SendByte(r_addr>>8);
  NRF_If_SendByte(r_addr & 0xFF);

  while (DataLength--) {
	  *pBuffer = NRF_If_SendByte(0xFF);
	  pBuffer++;
  }
  NRF_If_ResetCS();
  NRF_If_ResetProg();

  STM_EVAL_LEDOff(LED4);

  return MAL_Buffer;
}
