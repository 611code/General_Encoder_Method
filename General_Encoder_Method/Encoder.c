#include "Encoder.h"

uint8_t encode_mode;
//extern uint8_t count;
/**
 * @brief 读取SIQ的值
 * @param  无
 * @retval 返回差值
 */
static int16_t Encoder_ReadValue(void)
{
    int16_t value = 0;

    value = (int16_t)(__HAL_TIM_GetCounter(&htim3) - 32768);
    __HAL_TIM_SetCounter(&htim3, 32768);

    return value;
}

/**
* @brief 应用层函数（时基调用）
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
        
        return 1;
    }
    else if (Encoder_ReturnNum2 >= 2 || (Encoder_ReturnNum1 == 1 && Encoder_ReturnNum2 == 1))
    {
        Encoder_ReturnNum1 = 0;
        Encoder_ReturnNum2 = 0;
        
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
		if(EncoderNum==1)
		{
		count--;
		}
	
    
}
void Encoder_Reverse_CallBack(void)
{
    EncoderNum = 2;
    	if(EncoderNum==2)
		{
		
		count++;
		}
}
//时基函数
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//  /* USER CODE BEGIN Callback 0 */

//    if (htim == (&htim4))
//    {
//		 if (++Encoder_count >= 10)
//		{
//			Encoder_Handler();
//			Encoder_count = 0;
//		
//		}
//	}
//}
