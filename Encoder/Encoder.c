#include "Encoder.h"
#include "tim.h"
//#include "BEEPER.h"

extern uint8_t EncoderNum;//用户定义自变量，可以在main/操作系统.c函数里提前定义后引用；


//若已经配置过定时器，不需要额外在定义句柄
//TIM_HandleTypeDef htim3;
//TIM_HandleTypeDef htim4;

//下述注释的代码，使用cubemx配置时hal库可自动生成的，若已经配置过定时器，需要注释。若未注释则不需要。


/* tick_clock init function   tim4与中断配置，1ms一次中断*/
void tick_clock_init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 1680-1;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 100;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */
	HAL_TIM_Base_Start_IT(&htim4);
  /* USER CODE END TIM4_Init 2 */

}

////初始化Encoder的基础函数
//void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef* tim_encoderHandle)
//{

//  GPIO_InitTypeDef GPIO_InitStruct = {0};
//  if(tim_encoderHandle->Instance==TIM3)
//  {
//  /* USER CODE BEGIN TIM3_MspInit 0 */

//  /* USER CODE END TIM3_MspInit 0 */
//    /* TIM3 clock enable */
//    __HAL_RCC_TIM3_CLK_ENABLE();

//    __HAL_RCC_GPIOB_CLK_ENABLE();
//    /**TIM3 GPIO Configuration
//    PB4     ------> TIM3_CH1
//    PB5     ------> TIM3_CH2
//    */
//    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//  /* USER CODE BEGIN TIM3_MspInit 1 */

//  /* USER CODE END TIM3_MspInit 1 */
//  }
//}
////TIM4中断的配置流程
//void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
//{

//  if(tim_baseHandle->Instance==TIM4)
//  {
//  /* USER CODE BEGIN TIM4_MspInit 0 */

//  /* USER CODE END TIM4_MspInit 0 */
//    /* TIM4 clock enable */
//    __HAL_RCC_TIM4_CLK_ENABLE();

//    /* TIM4 interrupt Init */
//    HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
//    HAL_NVIC_EnableIRQ(TIM4_IRQn);
//  /* USER CODE BEGIN TIM4_MspInit 1 */

//  /* USER CODE END TIM4_MspInit 1 */
//  }
//}
////删除编码器的对应引脚关系
//void HAL_TIM_Encoder_MspDeInit(TIM_HandleTypeDef* tim_encoderHandle)
//{

//  if(tim_encoderHandle->Instance==TIM3)
//  {
//  /* USER CODE BEGIN TIM3_MspDeInit 0 */

//  /* USER CODE END TIM3_MspDeInit 0 */
//    /* Peripheral clock disable */
//    __HAL_RCC_TIM3_CLK_DISABLE();

//    /**TIM3 GPIO Configuration
//    PB4     ------> TIM3_CH1
//    PB5     ------> TIM3_CH2
//    */
//    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_4|GPIO_PIN_5);

//  /* USER CODE BEGIN TIM3_MspDeInit 1 */

//  /* USER CODE END TIM3_MspDeInit 1 */
//  }
//}


////下面函数的作用是删除tim4与其中断配置的初始化
//void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
//{

//  if(tim_baseHandle->Instance==TIM4)
//  {
//  /* USER CODE BEGIN TIM4_MspDeInit 0 */

//  /* USER CODE END TIM4_MspDeInit 0 */
//    /* Peripheral clock disable */
//    __HAL_RCC_TIM4_CLK_DISABLE();

//    /* TIM4 interrupt Deinit */
//    HAL_NVIC_DisableIRQ(TIM4_IRQn);
//  /* USER CODE BEGIN TIM4_MspDeInit 1 */

//  /* USER CODE END TIM4_MspDeInit 1 */
//  }
//}


void Encoder_Init(void)
{
	//此处使用tim3定时器的编码器模式。
	/* USER CODE BEGIN TIM3_Init 0 */
	
  /* USER CODE END TIM3_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 15;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 15;
  if (HAL_TIM_Encoder_Init(&htim3, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */
	__HAL_TIM_SET_COUNTER(&htim3,32768);//设置为重装载系数的一半
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);//开启tim3的编码器模式，并打开所有通道
	//初始化结束，但是仍然需要一个时基来监测编码器的状态来进行调控。
	//此处我使用的是tim4中断，1ms为基础，计数十次方便调试，和增加其他需要时基的库。
  /* USER CODE END TIM3_Init 2 */
}

/**
 * @brief 读取CE11的值
 * @param  无
 * @retval 返回差值
 */
static int16_t Encoder_ReadValue(void)
{
    int16_t value = 0;

    value = (int16_t)(__HAL_TIM_GetCounter(&htim3) - 32768);
    __HAL_TIM_SET_COUNTER(&htim3, 32768);

    return value;
}

/**
 * @brief 应用层函数（在主函数中调用）
 * @param  无
 * @retval 正转返回1/反转返回2/无状态返回0
 */
uint8_t Encoder_GetNum(void)
{
    int8_t Encoder_Num = 0;
    static uint8_t Encoder_ReturnNum1, Encoder_ReturnNum2;

    /* 读取输入值 */
    Encoder_Num = Encoder_ReadValue();
    /* 没有输入就返回0 */
    if (Encoder_Num == 0)
        return 0;
    // else
    //     printf("Encoder:%d\r\n", Encoder_Num);

    if (Encoder_Num > 0)
    {
        Encoder_ReturnNum1 += Encoder_Num;
    }
    else
    {
        Encoder_ReturnNum2 += (-Encoder_Num);
    }

    if (Encoder_ReturnNum1 >= 2)
    {
        Encoder_ReturnNum1 = 0;
        Encoder_ReturnNum2 = 0;
        //Beeper_Perform(BEEPER_KEYPRESS);//蜂鸣器反馈
        return 1;
    }
    else if (Encoder_ReturnNum2 >= 2 || (Encoder_ReturnNum1 == 1 && Encoder_ReturnNum2 == 1))
    {
        Encoder_ReturnNum1 = 0;
        Encoder_ReturnNum2 = 0;
        //Beeper_Perform(BEEPER_KEYPRESS);//蜂鸣器反馈
        return 2;
    }
    else
        return 0;
}

extern uint8_t EncoderNum;
void Encoder_Foreward_CallBack(void);
void Encoder_Reverse_CallBack(void);

/**
 * @brief 应用层函数（在主函数中调用）
 * @param  无
 * @retval 正转/反转会触发CallBack
 */
void Encoder_Handler(void)
{
    int8_t Encoder_Num = 0;
    static uint8_t Encoder_ReturnNum1, Encoder_ReturnNum2;

    /* 读取输入值 */
    Encoder_Num = Encoder_ReadValue();
    /* 没有输入就返回0 */
    if (Encoder_Num == 0)
        return ;
    // else
    //     printf("Encoder:%d\r\n", Encoder_Num);

    if (Encoder_Num > 0)
    {
        Encoder_ReturnNum1 += Encoder_Num;
    }
    else
    {
        Encoder_ReturnNum2 += (-Encoder_Num);
    }

    if (Encoder_ReturnNum1 >= 2)
    {
        Encoder_ReturnNum1 = 0;
        Encoder_ReturnNum2 = 0;
        Encoder_Foreward_CallBack();
    }
    else if (Encoder_ReturnNum2 >= 2 || (Encoder_ReturnNum1 == 1 && Encoder_ReturnNum2 == 1))
    {
        Encoder_ReturnNum1 = 0;
        Encoder_ReturnNum2 = 0;
        Encoder_Reverse_CallBack();
    }
}


void Encoder_Foreward_CallBack(void)
{
    EncoderNum = 1;
    //Beeper_Perform(BEEPER_KEYPRESS);//蜂鸣器反馈
}
void Encoder_Reverse_CallBack(void)
{
    EncoderNum = 2;
    //Beeper_Perform(BEEPER_KEYPRESS);//蜂鸣器反馈
}
