

void system_clk_set(void){ 
    ErrorStatus HSEStartUpStatus;
    RCC_DeInit();
 
    RCC_HSEConfig(RCC_HSE_ON );    //���ⲿʱ��
 
    HSEStartUpStatus = RCC_WaitForHSEStartUp();   // �ȴ��ⲿʱ�����ȶ�
 
  if(HSEStartUpStatus == SUCCESS)     
  {
    FLASH_SetLatency(FLASH_Latency_5);   
    FLASH_PrefetchBufferCmd(ENABLE);       //flashʱ������
    RCC_PLLCmd(DISABLE);  //��ֹ���໷
    RCC_HCLKConfig(RCC_SYSCLK_Div1);   //HCLK��Ƶ
    RCC_PCLK2Config(RCC_HCLK_Div1);   //PCLK2��Ƶ
    RCC_PCLK1Config(RCC_HCLK_Div4);    //PCLK1��Ƶ
    RCC_PLLConfig(RCC_PLLSource_HSE, 8, 336, 2, 7);    //sysc  lk = 168MHZ  
    RCC_PLLCmd(ENABLE); //�������໷
 
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){      //�ȴ����໷ʹ��
    
    }
 
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  //����PLLʱ��Ϊϵͳʱ��
 
    while(RCC_GetSYSCLKSource() != 0x08)       //�ȴ�
       { 
       }
     }
    #if(__FPU_PRESENT == 1)&&(__FPU_USED == 1)
			SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  //����FPU
		#endif

}