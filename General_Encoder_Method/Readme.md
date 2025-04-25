# SIQ-编码器驱动

​	重点注意：需要定时器提供时基，建议搭配mubiltbutton使用，需要知道时基使用方法，需要理解学会什么是编码器模式。

### 硬件信息

| 型号       | 电路实物                                                     | 原理图参考                                                   |
| ---------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| SIQ-02FVS3 | <img src="D:\1_STM32_Bsp\11_BSP_SIQ-02FVS3\BSP-SIQ\Encoder\img\电路图实物.png" style="zoom:30%;" /> | <img src="D:\1_STM32_Bsp\11_BSP_SIQ-02FVS3\BSP-SIQ\Encoder\img\原理图参考.jpg" style="zoom:33%;" /> |

​	本库的定时器编码器驱动，适用于所有的AB相编码器，通过配置Cubemx，选择tim3，编码器模式，15滤波，单边沿计数，后配置tim4中断，给编码器中断提供一个10ms的时基，就可使用。返回3种键值：EncoderNum=0 不转动 ，  EncoderNum=1向右，  EncoderNum=2向左。

### Cubemx配置

#### 	编码器读取配置

![](D:\1_STM32_Bsp\11_BSP_SIQ-02FVS3\BSP-SIQ\Encoder\img\cubemx1.jpg)

![](D:\1_STM32_Bsp\11_BSP_SIQ-02FVS3\BSP-SIQ\Encoder\img\cubemx2.jpg)

#### 	tim4时基函数配置

![](D:\1_STM32_Bsp\11_BSP_SIQ-02FVS3\BSP-SIQ\Encoder\img\tim4.jpg)

### 使用方法

```c
	//在main函数中，初始化编码器。
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
	//时基中断开启
	HAL_TIM_Base_Start_IT(&htim4);

	
	//重定义定时器回调函数（10ms回调编码器函数一次）
	void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
	{
 	 /* USER CODE BEGIN Callback 0 */

   	 	if (htim == (&htim4))
    	{
             if (++Encoder_count >= 10)
			{
				Encoder_Handler();
                 //编码器处理
				Encoder_count = 0;
		
			}
		}
	}
//之后在encoder.c中，找到两个回调函数，即可编写自己的功能了

	
void Encoder_Foreward_CallBack(void)
{
    EncoderNum = 1;
		//功能编写...
		if(EncoderNum==1)
		count--;
    
}
void Encoder_Reverse_CallBack(void)
{
    EncoderNum = 2;
    	//功能编写...
		if(EncoderNum==2)
		count++;

}

```

