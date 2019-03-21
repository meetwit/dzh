#ifndef __TIM2_H
#define __TIM2_H 

#include "stm32f10x.h"

extern u32 heartbeat;

void open_tim(void);
void close_tim(void);
void init_tim2(u16 enter_ms);	

#endif



