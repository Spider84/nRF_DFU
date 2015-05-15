/*
 * cbuff.c
 *
 *  Created on: 13 мая 2015 г.
 *      Author: User
 */
#include "cbuff.h"

// init
void buf_init(_buf *buf)
{
	buf->pIn = buf->pOut = buf->buf;       // init to any slot in buffer
	buf->pEnd = &(buf->buf[BUFSIZE]);   // past last valid slot in buffer
    buf->full = 0;               // buffer is empty
}

// add char 'c' to buffer
int32_t buf_put(_buf *buf, uint8_t c)
{
    if (buf->pIn == buf->pOut  &&  buf->full)
        return 0;           // buffer overrun

    *(buf->pIn)++ = c;             // insert c into buffer
    if (buf->pIn >= buf->pEnd)        // end of circular buffer?
    	buf->pIn = buf->buf;          // wrap around

    if (buf->pIn == buf->pOut)        // did we run into the output ptr?
    	buf->full = 1;           // can't add any more data into buffer
    return 1;               // all OK
}

// get a char from circular buffer
int32_t buf_get(_buf *buf, uint8_t *pc)
{
    if (buf->pIn == buf->pOut  &&  !buf->full)
        return 0;           // buffer empty  FAIL

    *pc = *buf->pOut++;              // pick up next char to be returned
    if (buf->pOut >= buf->pEnd)       // end of circular buffer?
    	buf->pOut = buf->buf;         // wrap around

    buf->full = 0;               // there is at least 1 slot
    return 1;               // *pc has the data to be returned
}

