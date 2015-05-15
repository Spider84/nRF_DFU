/*
 * cbuff.h
 *
 *  Created on: 13 мая 2015 г.
 *      Author: User
 */

#ifndef PROJECT_INC_CBUFF_H_
#define PROJECT_INC_CBUFF_H_

#include "platform_config.h"

#define BUFSIZE 128

typedef struct {
	uint8_t buf[BUFSIZE];
	uint8_t *pIn, *pOut, *pEnd;
	uint8_t full;
} _buf;


void buf_init(_buf *buf);
int32_t buf_put(_buf *buf, uint8_t c);
int32_t buf_get(_buf *buf, uint8_t *pc);

#endif /* PROJECT_INC_CBUFF_H_ */
