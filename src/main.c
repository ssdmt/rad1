/* create by ssdmt 17.09.2018, EKB
   Emmit protocol for koraen radar detector */

// I use most:

// $@    the file name of the target
// $<    the name of the first prerequisite (i.e., dependency)
// $^    the names of all prerequisites (i.e., dependencies)
// $(@D)    the directory part of the target
// $(@F)    the file part of the target
// $(<D)    the directory part of the first prerequisite (i.e., dependency)
// $(<F)    the file part of the first prerequisite (i.e., dependency)


#include <stm8l15x.h>

void TIM1_isr (void) __interrupt (23);

void main(void)
{
	int i,j;
	
	__asm__("sim"); //disable all interrupt
	
	CLK_DeInit();
	CLK_LSEConfig(DISABLE);	
    CLK_HSEConfig(DISABLE);
    CLK_LSICmd(DISABLE);
    CLK_HSICmd(ENABLE);
	
	CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
	CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1); //hsi 16MHz
	 	
	// TIM1 config/run
	CLK_PeripheralClockConfig(CLK_Peripheral_TIM1, ENABLE);
	TIM1_DeInit();
	TIM1_TimeBaseInit( (uint16_t)16, TIM1_CounterMode_Down,
										(uint16_t)1000,  0); // 2_time/sec
	TIM1_ITConfig(TIM1_IT_Update, ENABLE);
	TIM1_Cmd(ENABLE);
	
	GPIO_Init(GPIOE, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Fast);
	
	__asm__("rim"); //enable all interrupt
	
	while (1);
	// {
		// GPIO_ToggleBits( GPIOE, GPIO_Pin_7 );
		// for(j=0; j < 10; j++) {
			// for(i=0; i < 32000; i++);
		// }
	// }
}

void TIM1_isr (void) __interrupt (23) // 2_time/sec
{
	if (TIM1_GetFlagStatus(TIM1_FLAG_Update))
    {
        GPIO_ToggleBits( GPIOE, GPIO_Pin_7 );
        TIM1_ClearFlag(TIM1_FLAG_Update);
    }
}