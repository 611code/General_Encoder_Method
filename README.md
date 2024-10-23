# General_Encoder_Method
提供类似multi_button类似方法的一种编码器控制的板级支持包，响应迅速可搭配multi_button使用；
本库的定时器编码器驱动，适用于所有的AB相旋转式编码器。
通过配置Cubemx，选择tim3，编码器模式，15滤波，单边沿计数，后配置tim4中断，给编码器中断提供一个10ms的时基，在中断中调用处理函数即可。
返回3种键值：EncoderNum=0 不转动 ， EncoderNum=1向右， EncoderNum=2向左。


重点注意：需要定时器提供时基，建议搭配mubiltbutton使用，需要理解学会什么是编码器模式。
均可通过cubemx一键配置，代码重点部分应该关注中断处的处理函数。
