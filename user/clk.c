

void system_clk_set(void){ 
    ErrorStatus HSEStartUpStatus;
    RCC_DeInit();
 
    RCC_HSEConfig(RCC_HSE_ON );    //打开外部时钟
 
    HSEStartUpStatus = RCC_WaitForHSEStartUp();   // 等待外部时钟至稳定
 
  if(HSEStartUpStatus == SUCCESS)     
  {
    FLASH_SetLatency(FLASH_Latency_5);   
    FLASH_PrefetchBufferCmd(ENABLE);       //flash时钟设置
    RCC_PLLCmd(DISABLE);  //禁止锁相环
    RCC_HCLKConfig(RCC_SYSCLK_Div1);   //HCLK分频
    RCC_PCLK2Config(RCC_HCLK_Div1);   //PCLK2分频
    RCC_PCLK1Config(RCC_HCLK_Div4);    //PCLK1分频
    RCC_PLLConfig(RCC_PLLSource_HSE, 8, 336, 2, 7);    //sysc  lk = 168MHZ  
    RCC_PLLCmd(ENABLE); //开启锁相环
 
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){      //等待锁相环使能
    
    }
 
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  //设置PLL时钟为系统时钟
 
    while(RCC_GetSYSCLKSource() != 0x08)       //等待
       { 
       }
     }
    #if(__FPU_PRESENT == 1)&&(__FPU_USED == 1)
			SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  //开启FPU
		#endif

}