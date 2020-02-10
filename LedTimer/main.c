#define SRAM_END  0x20020000
#define STACK_TOP SRAM_END


#define RCC_APB1ENR 0x40023840
#define TIM6 0x40001000
#define TIM6_PSC 0x28
#define TIM6_ARR 0x2C
#define TIM6_DIER 0x0C
#define TIM6_CR1 0x00
#define TIM6_SR 0x10

#define NVIC_ISER 0xE000E100

#define RCC_AHB1ENR 0x40023830
#define GPIOD 0x40020C00

#define MODER_OFFSET 0x0
#define ODR_OFFSET 0x14

#define ul unsigned long

ul i = 0;

static void IntDefaultHandler(void)
{
    	while(1)
    	{
	}
}


void TIM6_DAC_IRQHandler(void)
{
	*(ul*)(TIM6 + TIM6_SR) &= 0x0;

    	if (i == 0) *(ul*)(GPIOD + ODR_OFFSET) = 0x1000;
    	else if(i == 1) *(ul*)(GPIOD + ODR_OFFSET) = 0x3000;
    	else if(i == 2) *(ul*)(GPIOD + ODR_OFFSET) = 0x7000;
    	else if(i == 3) *(ul*)(GPIOD + ODR_OFFSET) = 0xF000;
    	else if(i == 4) *(ul*)(GPIOD + ODR_OFFSET) = 0x0;

    	++i;

    	if(i == 5) i = 0;
}

int main(void)
{	

	*(ul*)(RCC_AHB1ENR) |= 1 << 3; // тактирование d-port
	++i; ++i; ++i; i = 0;
	*(ul*)(GPIOD + MODER_OFFSET) |= 0x55000000; // диоды на вход

	*(ul*)(RCC_APB1ENR) |= 1 << 4; //тактирование TIM6
	++i; ++i; ++i; i = 0;

	//настройка tim6
	*(ul*)(TIM6 + TIM6_PSC) = 24000 - 1;
	*(ul*)(TIM6 + TIM6_ARR) = 1000;
	*(ul*)(TIM6 + TIM6_DIER) |= 0x1;

	*(ul*)(NVIC_ISER + 0x04) = 1 << 22; //разрешение прерываний на TIM6
	*(ul*)(TIM6 + TIM6_CR1) |= 0x1; // старт таймера

  	while (1) 
	{
	}
}



ul* vector_table[] __attribute__((section (".vector_table"))) = 
{
    (ul*) STACK_TOP,                         // The initial stack pointer
    (ul*) main,        	                     // The reset handler
    IntDefaultHandler,                       // The NMI handler
    IntDefaultHandler,                       // The hard fault handler
    IntDefaultHandler,                       // MPU Fault Handler
    IntDefaultHandler,                       // Bus Fault Handler
    IntDefaultHandler,                       // Usage Fault Handler
    IntDefaultHandler,                       // Reserved
    IntDefaultHandler,                       // Reserved
    IntDefaultHandler,                       // Reserved
    IntDefaultHandler,                       // Reserved
    IntDefaultHandler,                       // SVCall Handler
    IntDefaultHandler,                       // Debug Monitor Handler
    IntDefaultHandler,                       // Reserved
    IntDefaultHandler,                       // PendSV Handler
    IntDefaultHandler,                       // SysTick Handler //External Interrupts
    IntDefaultHandler,                      // Window WatchDog                                        
    IntDefaultHandler,                      // PVD through EXTI Line detection                        
    IntDefaultHandler,                      // Tamper and TimeStamps through the EXTI line            
    IntDefaultHandler,                      // RTC Wakeup through the EXTI line                       
    IntDefaultHandler,                      // FLASH                                           
    IntDefaultHandler,                      // RCC                                             
    IntDefaultHandler,                      // EXTI Line0                                             
    IntDefaultHandler,                      // EXTI Line1                                             
    IntDefaultHandler,                      // EXTI Line2                                             
    IntDefaultHandler,                      // EXTI Line3                                             
    IntDefaultHandler,                      // EXTI Line4                                             
    IntDefaultHandler,                      // DMA1 Stream 0                                   
    IntDefaultHandler,                      // DMA1 Stream 1                                   
    IntDefaultHandler,                      // DMA1 Stream 2                                   
    IntDefaultHandler,                      // DMA1 Stream 3                                   
    IntDefaultHandler,                      // DMA1 Stream 4                                   
    IntDefaultHandler,                      // DMA1 Stream 5                                   
    IntDefaultHandler,                      // DMA1 Stream 6                                   
    IntDefaultHandler,                      // ADC1, ADC2 and ADC3s                            
    IntDefaultHandler,                      // CAN1 TX                                                
    IntDefaultHandler,                      // CAN1 RX0                                               
    IntDefaultHandler,                      // CAN1 RX1                                               
    IntDefaultHandler,                      // CAN1 SCE                                               
    IntDefaultHandler,                      // External Line[9:5]s                                    
    IntDefaultHandler,                      // TIM1 Break and TIM9                   
    IntDefaultHandler,                      // TIM1 Update and TIM10                 
    IntDefaultHandler,                      // TIM1 Trigger and Commutation and TIM11
    IntDefaultHandler,                      // TIM1 Capture Compare                                   
    IntDefaultHandler,                      // TIM2                                            
    IntDefaultHandler,                      // TIM3                                            
    IntDefaultHandler,                      // TIM4                                            
    IntDefaultHandler,                      // I2C1 Event                                             
    IntDefaultHandler,                      // I2C1 Error                                             
    IntDefaultHandler,                      // I2C2 Event                                             
    IntDefaultHandler,                      // I2C2Error                                               
    IntDefaultHandler,                      // SPI1                                            
    IntDefaultHandler,                      // SPI2                                            
    IntDefaultHandler,                      // USART1                                          
    IntDefaultHandler,                      // USART2                                          
    IntDefaultHandler,                      // USART3                                          
    IntDefaultHandler,                      // External Line[15:10]s                                  
    IntDefaultHandler,                      // RTC Alarm (A and B) through EXTI Line                  
    IntDefaultHandler,                      // USB OTG FS Wakeup through EXTI line                        
    IntDefaultHandler,                      // TIM8 Break and TIM12                  
    IntDefaultHandler,                      // TIM8 Update and TIM13                 
    IntDefaultHandler,                      // TIM8 Trigger and Commutation and TIM14
    IntDefaultHandler,                      // TIM8 Capture Compare                                   
    IntDefaultHandler,                      // DMA1 Stream7                                           
    IntDefaultHandler,                      // FSMC                                            
    IntDefaultHandler,                      // SDIO                                            
    IntDefaultHandler,                      // TIM5                                            
    IntDefaultHandler,                      // SPI3                                            
    IntDefaultHandler,                      // UART4                                           
    IntDefaultHandler,                      // UART5                                           
    TIM6_DAC_IRQHandler,		    // TIM6 and DAC1&2 underrun errors
    IntDefaultHandler,                      // TIM7                   
    IntDefaultHandler,                      // DMA2 Stream 0                                   
    IntDefaultHandler,                      // DMA2 Stream 1                                   
    IntDefaultHandler,                      // DMA2 Stream 2                                   
    IntDefaultHandler,                      // DMA2 Stream 3                                   
    IntDefaultHandler,                      // DMA2 Stream 4                                   
    IntDefaultHandler,                      // Ethernet                                        
    IntDefaultHandler,                      // Ethernet Wakeup through EXTI line                      
    IntDefaultHandler,                      // CAN2 TX                                                
    IntDefaultHandler,                      // CAN2 RX0                                               
    IntDefaultHandler,                      // CAN2 RX1                                               
    IntDefaultHandler,                      // CAN2 SCE                                               
    IntDefaultHandler,                      // USB OTG FS                                      
    IntDefaultHandler,                      // DMA2 Stream 5                                   
    IntDefaultHandler,                      // DMA2 Stream 6                                   
    IntDefaultHandler,                      // DMA2 Stream 7                                   
    IntDefaultHandler,                      // USART6                                           
    IntDefaultHandler,                      // I2C3 event                                             
    IntDefaultHandler,                      // I2C3 error                                             
    IntDefaultHandler,                      // USB OTG HS End Point 1 Out                      
    IntDefaultHandler,                      // USB OTG HS End Point 1 In                       
    IntDefaultHandler,                      // USB OTG HS Wakeup through EXTI                         
    IntDefaultHandler,                      // USB OTG HS                                      
    IntDefaultHandler,                      // DCMI                                            
    IntDefaultHandler,                      // CRYP crypto                                     
    IntDefaultHandler,                      // Hash and Rng
    IntDefaultHandler                      // FPU         
};


