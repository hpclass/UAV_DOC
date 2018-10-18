闫刚
2017-01-27
STM32F4网络MAC的DMA接收和发送过程

1.发送
 uint32_t ETH_Prepare_Transmit_Descriptors(u16 FrameLength)  
if ((ETH->DMASR & ETH_DMASR_TBUS) != (u32)RESET)
  /* When Tx Buffer unavailable flag is set: clear it and resume transmission */
  if ((ETH->DMASR & ETH_DMASR_TBUS) != (u32)RESET)
  {
    /* Clear TBUS ETHERNET DMA flag */
    ETH->DMASR = ETH_DMASR_TBUS;
    
/* Resume DMA transmission*/
    ETH->DMATPDR = 0;
    启动网络的传输，再触发DMA记录的数量.
   }
发送数据：先填充发送描述符链表，清除上一次发送的完成的DMA发送完成标志位.

2.接收
FrameTypeDef ETH_Get_Received_Frame(void)
无论通过标志位还是其他方式，确定完全接收数据完成，才能调用这个函数，返回数据包的首地址.
 
FrameTypeDef ETH_Get_Received_Frame_interrupt(void)
中断方式已经确定收到数据，但是循环查询的接收描述符，找到1个接收到数据的缓冲区就退出.
    
uint32_t ETH_CheckFrameReceived(void)
    查询接收数据包是否完成，简单包的第1个描述符，直到数据填充给最后1个描述符，返回接收完成指针.  记录接收的数据全过程。无论是中断还是查询，都会修改

中断接收:
   方案1：
void ETH_IRQHandler(void)
    	->while(ETH_CheckFrameReceived())     
          判断数据是否接收完成
   	  ->FrameTypeDef ETH_Get_Received_Frame(void) 
         返回数据包的缓冲区头指针
   方案2：
         void ETH_IRQHandler(void)
->FrameTypeDef ETH_Get_Received_Frame_interrupt(void) 
中断方式从处理DMA_RX_FRAME_infos->Seg_Coun和返回指针



static struct pbuf * low_level_input(struct netif *netif)
  frame = ETH_Get_Received_Frame();  
数据拷贝完成，就可以重

