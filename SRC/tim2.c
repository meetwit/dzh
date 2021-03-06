#include "tim2.h"
#include "usart1.h"
#include "usart2.h"
#include "usart3.h"

u32 heartbeat=0;
/***************************************************************************
函数名：TIM2_IRQHandler()
参	数：
返回值：无
说	明：通用定时器2初始化
2017年11月16日20:03:15
作	者：关焕懿
***************************************************************************/
void init_tim2(u16 enter_ms){
	
	RCC -> APB1ENR |= 1<<0;
	TIM2 -> PSC =7200-1;
	TIM2 -> ARR =enter_ms*10;
	//定时时间长度为10ms   ARR/10(ms)
	
	
	TIM2 -> DIER |=1<<0;//模块级中断使能
	NVIC_EnableIRQ(TIM2_IRQn);
	
	TIM2 -> CR1 |= (1<<0);//打开定时器

}	

void open_tim(void){
	TIM2 -> CR1 |= (1<<0);//打开定时器
}

void close_tim(void){
	TIM2 -> CR1 &= ~(1<<0);
}

/***************************************************************************
函数名：TIM2_IRQHandler()
形	参：无
返回值：无
功	能：通用寄存器2，每xMs中断一次
作	者：关焕懿
时	间：2017年11月16日20:03:15
***************************************************************************/
void TIM2_IRQHandler(){

	if(Rx_Tm--){
		if(Rx_Tm == 1){
			Rx_End = 1;
		}
	}
	if(Rx_Tm2--){
		if(Rx_Tm2 == 1){
			Rx_End2 = 1;
		}
	}
	if(Rx_Tm3--){
		if(Rx_Tm3 == 1){
			Rx_End3 = 1;
		}
	}
	heartbeat++;
		//清中断
	TIM2 -> SR =0;
	
}


