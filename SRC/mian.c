#include "stm32f10x.h"
#include "tim2.h"
#include "usart1.h"
#include "usart2.h"
#include "usart3.h"
#include "stdio.h" 
#include "math.h" 


#include "delay.h" 
#include "dht11.h" 
#include "adc.h" 

#define tim_hz 200			//设定定时器2的中断频率HZ

void show_dth11(float show_hz){
	static u32 last_hb=0;
	static u8 temperature;  	    
	static u8 humidity;  
	if((heartbeat-last_hb)>(int)(tim_hz/show_hz)){
		close_tim();
			DHT11_Read_Data(&temperature,&humidity);				//读取温湿度值	
		open_tim();
		if((temperature==0)&&(humidity==0)){
			printf("dht11 still init...\r\n");
		}else{				    
			printf("temperature=%d,humidity=%d\r\n",temperature,humidity);	//显示温度	,显示湿度
		}
			last_hb = heartbeat;
	}  		
}

void show_fish(float show_hz){
	static u32 last_hb=0;
	static u16 fish;  	 
		if((heartbeat-last_hb)>(int)(tim_hz/show_hz)){
			close_tim();
			fish = Get_Adc(7);
			open_tim();
			
			printf("fish=%d\r\n",fish);
			
			last_hb = heartbeat;
		} 
}

void show_test(float show_hz){
	static u32 last_hb=0;
	 
	if((heartbeat-last_hb)>(int)(tim_hz/show_hz)){
		printf("show_test\r\n\r\n\r\n");
			last_hb = heartbeat;
	} 
}



int main(){
	
	/*定时器2初始化*/
	init_tim2(1000/tim_hz);			//定时器2的中断时间间隔，单位ms
	
	/*串口初始化，波特率为115200*/
	usart_init(115200);				//串口1
	usart2_init(115200);			//串口2
	usart3_init(115200);			//串口3
	
	delay_init(72);
	Adc_Init();
	
	printf("stm32 systern start\r\n");
	
	while(DHT11_Init())	//DHT11初始化	
	{
		printf("DHT11 Error\r\n");
		delay_ms(500);
	}	
	
	while(1){
		
		show_dth11(1);
		show_fish(1);
		show_test(1);
		Task_Pc();
		Task_Pc2();
		Task_Pc3();

	}

}







