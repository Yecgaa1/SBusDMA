## SBus+HAL+DMA库

首先是cubemx配置时，如图

![image-20210524211615145](https://raw.githubusercontent.com/xutongxin1/xutongxin1.github.io/master/asset/%E6%97%A5%E5%BF%97/image-20210524211615145.png)

注意波特率，字节长，校验，停止位，最后有一个只接收（Sbus是单向协议

DMA

![image-20210524211847831](https://raw.githubusercontent.com/xutongxin1/xutongxin1.github.io/master/asset/%E6%97%A5%E5%BF%97/image-20210524211847831.png)

NVIC

![image-20210524211905625](https://raw.githubusercontent.com/xutongxin1/xutongxin1.github.io/master/asset/%E6%97%A5%E5%BF%97/image-20210524211905625.png)

然后把文件复制到对应地方

然后在main.c中加入以下代码

```c
uint8_t USART2_RX_BUF[USART_REC_LEN]; //接收缓冲
uint16_t USART2_RX_STA = 0; 
uint8_t aRxBuffer1[100],Sbus_flag=0;
HAL_StatusTypeDef status=HAL_ERROR;
SBUS_CH_Struct SBUS_CH;
__HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE); //启动串口收完数据后的闲时中断
HAL_UART_Receive_DMA(&huart2,aRxBuffer1,100);//打开第一次接收
```

为了可以正常引用，main.h添加

```c
#define USART_REC_LEN 100
extern uint8_t USART2_RX_BUF[100],aRxBuffer1[100],Sbus_flag;
extern uint16_t USART2_RX_STA;
```

在stm32f1xx_it.c**修改**

```c
void USART2_IRQHandler(void)//这个代码本身就有
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */
    if(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_IDLE)!=RESET)
    {
        while(1) {
            USART2_RX_BUF[USART2_RX_STA] = aRxBuffer1[0];
            if (USART2_RX_STA == 0 && USART2_RX_BUF[USART2_RX_STA] != 0x0F) {
                HAL_UART_Receive_DMA(&huart2, aRxBuffer1, 100);
                break; //帧头不对，继续接收
            }
            USART2_RX_STA++;
            if (USART2_RX_STA > USART_REC_LEN) USART2_RX_STA = 0;  ///接收数据错误,重新开始接收
            if (USART2_RX_BUF[0] == 0x0F && USART2_RX_BUF[24] == 0x00 && USART2_RX_STA == 25)    //接受完一帧
            {
                update_sbus(USART2_RX_BUF);
                memset(&USART2_RX_BUF,0,100);
                /*for (int i = 0; i < 25; i++)        //清空缓存
                    USART2_RX_BUF[i] = 0;*/
                USART2_RX_STA = 0;
                Sbus_flag=1;
            }
            HAL_UART_Receive_DMA(&huart2,aRxBuffer1,100);
            break;
        }
    }
  /* USER CODE END USART2_IRQn 1 */
}
```

## 贡献人

xtx

wjl
