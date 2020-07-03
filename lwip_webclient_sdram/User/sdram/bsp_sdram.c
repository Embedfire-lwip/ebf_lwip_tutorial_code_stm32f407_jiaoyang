/**
  ******************************************************************************
  * @file    bsp_sdram.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   sdramӦ�ú����ӿ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F407 ������  
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./sdram/bsp_sdram.h"  

static SRAM_HandleTypeDef  SRAM_Handler;
static FMC_NORSRAM_TimingTypeDef Timing;

/**
  * @brief  Initializes SRAM MSP.
  */
 void FSMC_SRAM_MspInit(void)
{
//  static DMA_HandleTypeDef dmaHandle;
  GPIO_InitTypeDef GPIO_Init_Structure;
//  SRAM_HandleTypeDef *hsram = & SRAM_Handler;
    
  /* Enable FMC clock */
  __HAL_RCC_FSMC_CLK_ENABLE();
  
//  /* Enable chosen DMAx clock */
//  __SRAM_DMAx_CLK_ENABLE();

  /* Enable GPIOs clock */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  
  /* Common GPIO configuration */
  GPIO_Init_Structure.Mode      = GPIO_MODE_AF_PP;
  GPIO_Init_Structure.Pull      = GPIO_PULLUP;
  GPIO_Init_Structure.Speed     = GPIO_SPEED_HIGH;
  GPIO_Init_Structure.Alternate = GPIO_AF12_FSMC;
  
  /* GPIOD configuration */
  GPIO_Init_Structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_8     |\
                              GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 |\
                              GPIO_PIN_14 | GPIO_PIN_15;
   
  HAL_GPIO_Init(GPIOD, &GPIO_Init_Structure);

  /* GPIOE configuration */  
  GPIO_Init_Structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7     |\
                              GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 |\
                              GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOE, &GPIO_Init_Structure);
  
  /* GPIOF configuration */  
  GPIO_Init_Structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4     |\
                              GPIO_PIN_5 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  HAL_GPIO_Init(GPIOF, &GPIO_Init_Structure);
  
  /* GPIOG configuration */  
  GPIO_Init_Structure.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2| GPIO_PIN_3 | GPIO_PIN_4     |\
                              GPIO_PIN_5 | GPIO_PIN_12;
  
  HAL_GPIO_Init(GPIOG, &GPIO_Init_Structure);  
  

//  /* Configure common DMA parameters */
//  dmaHandle.Init.Channel             = SRAM_DMAx_CHANNEL;
//  dmaHandle.Init.Direction           = DMA_MEMORY_TO_MEMORY;
//  dmaHandle.Init.PeriphInc           = DMA_PINC_ENABLE;
//  dmaHandle.Init.MemInc              = DMA_MINC_ENABLE;
//  dmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
//  dmaHandle.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
//  dmaHandle.Init.Mode                = DMA_NORMAL;
//  dmaHandle.Init.Priority            = DMA_PRIORITY_HIGH;
//  dmaHandle.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;         
//  dmaHandle.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
//  dmaHandle.Init.MemBurst            = DMA_MBURST_INC8;
//  dmaHandle.Init.PeriphBurst         = DMA_PBURST_INC8; 
//  
//  dmaHandle.Instance = SRAM_DMAx_STREAM;
//  
//   /* Associate the DMA handle */
//  __HAL_LINKDMA(hsram, hdma, dmaHandle);
//  
//  /* Deinitialize the stream for new transfer */
//  HAL_DMA_DeInit(&dmaHandle);
//  
//  /* Configure the DMA stream */
//  HAL_DMA_Init(&dmaHandle);
//    
//  /* NVIC configuration for DMA transfer complete interrupt */
//  HAL_NVIC_SetPriority(SRAM_DMAx_IRQn, 0x0F, 0);
//  HAL_NVIC_EnableIRQ(SRAM_DMAx_IRQn);   
}


/**
  * @brief  Initializes the SRAM device.
  * @retval SRAM status
  */
void FSMC_SRAM_Init(void)
{ 
   SRAM_Handler.Instance = FMC_NORSRAM_DEVICE;
   SRAM_Handler.Extended = FMC_NORSRAM_EXTENDED_DEVICE;
  
  /* SRAM device configuration */  
  Timing.AddressSetupTime      = 0x00;
  Timing.AddressHoldTime       = 0x00;
  Timing.DataSetupTime         = 0x08;
  Timing.BusTurnAroundDuration = 0x00;
  Timing.CLKDivision           = 0x00;
  Timing.DataLatency           = 0x00;
  Timing.AccessMode            = FSMC_ACCESS_MODE_A;
 
  SRAM_Handler.Init.NSBank=FSMC_NORSRAM_BANK4;     					        //ʹ��NE4
	SRAM_Handler.Init.DataAddressMux=FSMC_DATA_ADDRESS_MUX_DISABLE; 	//��ַ/�����߲�����
	SRAM_Handler.Init.MemoryType=FSMC_MEMORY_TYPE_SRAM;   				    //SRAM
	SRAM_Handler.Init.MemoryDataWidth=FSMC_NORSRAM_MEM_BUS_WIDTH_16; 	//16λ���ݿ��
	SRAM_Handler.Init.BurstAccessMode=FSMC_BURST_ACCESS_MODE_DISABLE; //�Ƿ�ʹ��ͻ������,����ͬ��ͻ���洢����Ч,�˴�δ�õ�
	SRAM_Handler.Init.WaitSignalPolarity=FSMC_WAIT_SIGNAL_POLARITY_LOW;//�ȴ��źŵļ���,����ͻ��ģʽ����������
	SRAM_Handler.Init.WaitSignalActive=FSMC_WAIT_TIMING_BEFORE_WS;   	//�洢�����ڵȴ�����֮ǰ��һ��ʱ�����ڻ��ǵȴ������ڼ�ʹ��NWAIT
	SRAM_Handler.Init.WriteOperation=FSMC_WRITE_OPERATION_ENABLE;    	//�洢��дʹ��
	SRAM_Handler.Init.WaitSignal=FSMC_WAIT_SIGNAL_DISABLE;           	//�ȴ�ʹ��λ,�˴�δ�õ�
	SRAM_Handler.Init.ExtendedMode=FSMC_EXTENDED_MODE_DISABLE;        	//��дʹ����ͬ��ʱ��
	SRAM_Handler.Init.AsynchronousWait=FSMC_ASYNCHRONOUS_WAIT_DISABLE;	//�Ƿ�ʹ��ͬ������ģʽ�µĵȴ��ź�,�˴�δ�õ�
	SRAM_Handler.Init.WriteBurst=FSMC_WRITE_BURST_DISABLE;           	  //��ֹͻ��д
	SRAM_Handler.Init.ContinuousClock=FSMC_CONTINUOUS_CLOCK_SYNC_ASYNC;
  
//  sramHandle.Init.NSBank             = FSMC_NORSRAM_BANK2;
//  sramHandle.Init.DataAddressMux     = FSMC_DATA_ADDRESS_MUX_DISABLE;
//  sramHandle.Init.MemoryType         = FSMC_MEMORY_TYPE_SRAM;
//  sramHandle.Init.MemoryDataWidth    = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
//  sramHandle.Init.BurstAccessMode    = FSMC_BURST_ACCESS_MODE_DISABLE;
//  sramHandle.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
//  sramHandle.Init.WrapMode           = FSMC_WRAP_MODE_DISABLE;
//  sramHandle.Init.WaitSignalActive   = FSMC_WAIT_TIMING_BEFORE_WS;
//  sramHandle.Init.WriteOperation     = FSMC_WRITE_OPERATION_ENABLE;
//  sramHandle.Init.WaitSignal         = FSMC_WAIT_SIGNAL_DISABLE;
//  sramHandle.Init.ExtendedMode       = FSMC_EXTENDED_MODE_DISABLE;
//  sramHandle.Init.AsynchronousWait   = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
//  sramHandle.Init.WriteBurst         = SRAM_WRITEBURST;
    
  /* SRAM controller initialization */
  FSMC_SRAM_MspInit();
  HAL_SRAM_Init(& SRAM_Handler, &Timing, &Timing);
//  if(HAL_SRAM_Init(&sramHandle, &Timing, &Timing) != HAL_OK)
//  {
//    return SRAM_ERROR;
//  }
//  else
//  {
//    return SRAM_OK;
//  }
}


















//static FMC_SDRAM_CommandTypeDef Command;
//SDRAM_HandleTypeDef hsdram1;
//#define sdramHandle hsdram1
///**
//  * @brief  �ӳ�һ��ʱ��
//  * @param  �ӳٵ�ʱ�䳤��
//  * @retval None
//  */
//static void SDRAM_delay(__IO uint32_t nCount)
//{
//  __IO uint32_t index = 0; 
//  for(index = (100000 * nCount); index != 0; index--)
//  {
//  }
//}

///**
//  * @brief  ��ʼ������SDRAM��IO
//  * @param  ��
//  * @retval ��
//  */
//static void SDRAM_GPIO_Config(void)
//{		
//  GPIO_InitTypeDef GPIO_InitStructure;
//  
//  /* ʹ��SDRAM��ص�GPIOʱ�� */

//  /*��ַ�ź���*/
//  FMC_A0_GPIO_CLK;  FMC_A1_GPIO_CLK;  FMC_A2_GPIO_CLK;
//  FMC_A3_GPIO_CLK;FMC_A4_GPIO_CLK;FMC_A5_GPIO_CLK;
//  FMC_A6_GPIO_CLK; FMC_A7_GPIO_CLK; FMC_A8_GPIO_CLK;
//  FMC_A9_GPIO_CLK; FMC_A10_GPIO_CLK;FMC_A11_GPIO_CLK; 
//  /*�����ź���*/
//  FMC_D0_GPIO_CLK; FMC_D1_GPIO_CLK ; FMC_D2_GPIO_CLK ; 
//  FMC_D3_GPIO_CLK ; FMC_D4_GPIO_CLK ; FMC_D5_GPIO_CLK ;
//  FMC_D6_GPIO_CLK; FMC_D7_GPIO_CLK ; FMC_D8_GPIO_CLK ;
//  FMC_D9_GPIO_CLK ;FMC_D10_GPIO_CLK; FMC_D11_GPIO_CLK;
//  FMC_D12_GPIO_CLK; FMC_D13_GPIO_CLK; FMC_D14_GPIO_CLK;
//  FMC_D15_GPIO_CLK;  
//  /*�����ź���*/
//  FMC_CS_GPIO_CLK ; FMC_BA0_GPIO_CLK; FMC_BA1_GPIO_CLK ;
//  FMC_WE_GPIO_CLK ; FMC_RAS_GPIO_CLK ; FMC_CAS_GPIO_CLK;
//  FMC_CLK_GPIO_CLK ; FMC_CKE_GPIO_CLK; FMC_UDQM_GPIO_CLK;
//  FMC_LDQM_GPIO_CLK;


//  
//  /*-- GPIO ���� -----------------------------------------------------*/

//  /* ͨ�� GPIO ���� */       
//  GPIO_InitStructure.Mode      = GPIO_MODE_AF_PP;//����Ϊ���ù���
//  GPIO_InitStructure.Pull      = GPIO_PULLUP;
//  GPIO_InitStructure.Speed     = GPIO_SPEED_FAST;
//  GPIO_InitStructure.Alternate = GPIO_AF12_FMC;
//  
//  
//  /*��ַ�ź��� �����������*/
//  GPIO_InitStructure.Pin = FMC_A0_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A0_GPIO_PORT, &GPIO_InitStructure);
//  
//  GPIO_InitStructure.Pin = FMC_A1_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A1_GPIO_PORT, &GPIO_InitStructure);
//  
//  GPIO_InitStructure.Pin = FMC_A2_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A2_GPIO_PORT, &GPIO_InitStructure);
//  
//  GPIO_InitStructure.Pin = FMC_A3_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A3_GPIO_PORT, &GPIO_InitStructure);
//  
//  GPIO_InitStructure.Pin = FMC_A4_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A4_GPIO_PORT, &GPIO_InitStructure);
//  
//  GPIO_InitStructure.Pin = FMC_A5_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A5_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_A6_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A6_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_A7_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A7_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_A8_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A8_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_A9_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A9_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_A10_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A10_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_A11_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_A11_GPIO_PORT, &GPIO_InitStructure);

//  
//  
//  /*�����ź��� �����������*/
//  GPIO_InitStructure.Pin = FMC_D0_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D0_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D1_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D1_GPIO_PORT, &GPIO_InitStructure);

//    
//  GPIO_InitStructure.Pin = FMC_D2_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D2_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D3_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D3_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D4_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D4_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D5_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D5_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D6_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D6_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D7_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D7_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D8_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D8_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D9_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D9_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D10_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D10_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D11_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D11_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D12_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D12_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D13_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D13_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D14_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D14_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_D15_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_D15_GPIO_PORT, &GPIO_InitStructure);

//  
//  /*�����ź���*/
//  GPIO_InitStructure.Pin = FMC_CS_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_CS_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_BA0_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_BA0_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_BA1_GPIO_PIN;
//  HAL_GPIO_Init(FMC_BA1_GPIO_PORT, &GPIO_InitStructure);

//    
//  GPIO_InitStructure.Pin = FMC_WE_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_WE_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_RAS_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_RAS_GPIO_PORT, &GPIO_InitStructure);

//    
//  GPIO_InitStructure.Pin = FMC_CAS_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_CAS_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_CLK_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_CLK_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_CKE_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_CKE_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_UDQM_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_UDQM_GPIO_PORT, &GPIO_InitStructure);

//  
//  GPIO_InitStructure.Pin = FMC_LDQM_GPIO_PIN; 
//  HAL_GPIO_Init(FMC_LDQM_GPIO_PORT, &GPIO_InitStructure);

//		
//}

///**
//  * @brief  ��SDRAMоƬ���г�ʼ������
//  * @param  None. 
//  * @retval None.
//  */
//static void SDRAM_InitSequence(void)
//{
//  uint32_t tmpr = 0;
//  
///* Step 3 --------------------------------------------------------------------*/
//  /* ������������ṩ��SDRAM��ʱ�� */
//  Command.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
//  Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
//  Command.AutoRefreshNumber = 1;
//  Command.ModeRegisterDefinition = 0;
///* Send the command */
//  HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);

//  /* Step 2: Insert 100 us minimum delay */ 
//  /* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
//  SDRAM_delay(1);
//    
///* Step 5 --------------------------------------------------------------------*/
//  /* ������������е�bankԤ��� */ 
//  Command.CommandMode = FMC_SDRAM_CMD_PALL;
//  Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
//  Command.AutoRefreshNumber = 1;
//  Command.ModeRegisterDefinition = 0;
///* Send the command */
//  HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);   
//  
///* Step 6 --------------------------------------------------------------------*/
//  /* ��������Զ�ˢ�� */   
//  Command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
//  Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
//  Command.AutoRefreshNumber = 4;
//  Command.ModeRegisterDefinition = 0;
// /* Send the command */
//  HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);
//  
///* Step 7 --------------------------------------------------------------------*/
//  /* ����sdram�Ĵ������� */
//  tmpr = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_2          |
//                   SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
//                   SDRAM_MODEREG_CAS_LATENCY_3           |
//                   SDRAM_MODEREG_OPERATING_MODE_STANDARD |
//                   SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
//  
//  /* �����������SDRAM�Ĵ��� */
//  Command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
//  Command.CommandTarget = FMC_COMMAND_TARGET_BANK;
//  Command.AutoRefreshNumber = 1;
//  Command.ModeRegisterDefinition = tmpr;
//  /* Send the command */
//  HAL_SDRAM_SendCommand(&sdramHandle, &Command, SDRAM_TIMEOUT);
//  
///* Step 8 --------------------------------------------------------------------*/

//  /* ����ˢ�¼����� */
//  /* (15.62 us x Freq) - 20 */
//	  /* Step 6: Set the refresh rate counter */
//  /* Set the device refresh rate */
//  HAL_SDRAM_ProgramRefreshRate(&sdramHandle, 1386); 
////  FMC_SetRefreshCount(1386);
////  /* ������������*/
////  while(FMC_GetFlagStatus(FMC_BANK_SDRAM, FMC_FLAG_Busy) != RESET)
////  {
////  }
//}


///**
//  * @brief  ��ʼ������ʹ��SDRAM��FMC��GPIO�ӿڣ�
//  *         ��������SDRAM��д����ǰ��Ҫ������
//  * @param  None
//  * @retval None
//  */
//void SDRAM_Init(void)
//{
//  //FMC_SDRAMInitTypeDef  FMC_SDRAMInitStructure;
////  FMC_SDRAMTimingInitTypeDef  FMC_SDRAMTimingInitStructure; 
//  
//  /* ����FMC�ӿ���ص� GPIO*/
//  SDRAM_GPIO_Config();
//  
//  /* ʹ�� FMC ʱ�� */
//	__HAL_RCC_FMC_CLK_ENABLE();
////  RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FMC, ENABLE);
// 
////  /* ���� FMC ��ز��� ---------------------------------------------------------*/
////  /* SDCLK�� 90 Mhz (HCLK/2 :180Mhz/2) */
////  /* TMRD: 2 Clock cycles */
////  FMC_SDRAMTimingInitStructure.FMC_LoadToActiveDelay    = 2;      
////  /* TXSR: min=70ns (7x11.11ns) */
////  FMC_SDRAMTimingInitStructure.FMC_ExitSelfRefreshDelay = 7;
////  /* TRAS: min=42ns (4x11.11ns) max=120k (ns) */
////  FMC_SDRAMTimingInitStructure.FMC_SelfRefreshTime      = 4;
////  /* TRC:  min=70 (7x11.11ns) */        
////  FMC_SDRAMTimingInitStructure.FMC_RowCycleDelay        = 7;         
////  /* TWR:  min=1+ 7ns (1+1x11.11ns) */
////  FMC_SDRAMTimingInitStructure.FMC_WriteRecoveryTime    = 2;      
////  /* TRP:  20ns => 2x11.11ns */
////  FMC_SDRAMTimingInitStructure.FMC_RPDelay              = 2;                
////  /* TRCD: 20ns => 2x11.11ns */
////  FMC_SDRAMTimingInitStructure.FMC_RCDDelay             = 2;

/////* FMC SDRAM �������� */
////  FMC_SDRAMInitStructure.FMC_Bank = FMC_BANK_SDRAM;
////  /* �е�ַ�߿��: [7:0] */
////  FMC_SDRAMInitStructure.FMC_ColumnBitsNumber = FMC_ColumnBits_Number_8b;
////  /* �е�ַ�߿��: [11:0] */
////  FMC_SDRAMInitStructure.FMC_RowBitsNumber = FMC_RowBits_Number_12b;
////  /* �����߿�� */
////  FMC_SDRAMInitStructure.FMC_SDMemoryDataWidth = SDRAM_MEMORY_WIDTH;
////  /* SDRAM�ڲ�bank����*/
////  FMC_SDRAMInitStructure.FMC_InternalBankNumber = FMC_InternalBank_Number_4;
////  /* CASǱ���� */
////  FMC_SDRAMInitStructure.FMC_CASLatency = SDRAM_CAS_LATENCY; 
////  /* ��ֹд����*/
////  FMC_SDRAMInitStructure.FMC_WriteProtection = FMC_Write_Protection_Disable;
////  /* SDCLKʱ�ӷ�Ƶ���ӣ�SDCLK = HCLK/SDCLOCK_PERIOD*/
////  FMC_SDRAMInitStructure.FMC_SDClockPeriod = SDCLOCK_PERIOD; 
////  /* ͻ����ģʽ����*/  
////  FMC_SDRAMInitStructure.FMC_ReadBurst = SDRAM_READBURST;
////  /* ���ӳ����� */
////  FMC_SDRAMInitStructure.FMC_ReadPipeDelay = FMC_ReadPipe_Delay_1;
////  /* SDRAMʱ����� */
////  FMC_SDRAMInitStructure.FMC_SDRAMTimingStruct = &FMC_SDRAMTimingInitStructure;
////  
////  /* FMC SDRAM bank initialization */
////  FMC_SDRAMInit(&FMC_SDRAMInitStructure); 
//  FMC_SDRAM_TimingTypeDef SdramTiming;

//  /** Perform the SDRAM1 memory initialization sequence
//  */
//  hsdram1.Instance = FMC_SDRAM_DEVICE;
//  /* hsdram1.Init */
//  hsdram1.Init.SDBank = FMC_SDRAM_BANK2;
//  hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
//  hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
//  hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
//  hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
//  hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
//  hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
//  hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
//  hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_DISABLE;
//  hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_1;
//  /* SdramTiming */
//  SdramTiming.LoadToActiveDelay = 2;
//  SdramTiming.ExitSelfRefreshDelay = 7;
//  SdramTiming.SelfRefreshTime = 4;
//  SdramTiming.RowCycleDelay = 7;
//  SdramTiming.WriteRecoveryTime = 2;
//  SdramTiming.RPDelay = 2;
//  SdramTiming.RCDDelay = 2;

//  HAL_SDRAM_Init(&hsdram1, &SdramTiming);  
//  /* FMC SDRAM device initialization sequence */
//  SDRAM_InitSequence(); 
//  
//}



///**
//  * @brief  �ԡ��֡�Ϊ��λ��sdramд������ 
//  * @param  pBuffer: ָ�����ݵ�ָ�� 
//  * @param  uwWriteAddress: Ҫд���SDRAM�ڲ���ַ
//  * @param  uwBufferSize: Ҫд�����ݴ�С
//  * @retval None.
//  */
//void SDRAM_WriteBuffer(uint32_t* pBuffer, uint32_t uwWriteAddress, uint32_t uwBufferSize)
//{
//  __IO uint32_t write_pointer = (uint32_t)uwWriteAddress;

//  /* ��ֹд���� */
//  HAL_SDRAM_WriteProtection_Disable(&hsdram1);
//  /* ���SDRAM��־���ȴ���SDRAM���� */ 
//  while(HAL_SDRAM_GetState(&hsdram1) != RESET)
//  {
//  }

//  /* ѭ��д������ */
//  for (; uwBufferSize != 0; uwBufferSize--) 
//  {
//    /* �������ݵ�SDRAM */
//    *(uint32_t *) (SDRAM_BANK_ADDR + write_pointer) = *pBuffer++;

//    /* ��ַ����*/
//    write_pointer += 4;
//  }
//    
//}

///**
//  * @brief  ��SDRAM�ж�ȡ���� 
//  * @param  pBuffer: ָ��洢���ݵ�buffer
//  * @param  ReadAddress: Ҫ��ȡ���ݵĵ�ʮ
//  * @param  uwBufferSize: Ҫ��ȡ�����ݴ�С
//  * @retval None.
//  */
//void SDRAM_ReadBuffer(uint32_t* pBuffer, uint32_t uwReadAddress, uint32_t uwBufferSize)
//{
//  __IO uint32_t write_pointer = (uint32_t)uwReadAddress;
//  
//   
//  /* ���SDRAM��־���ȴ���SDRAM���� */  
//  while ( HAL_SDRAM_GetState(&hsdram1) != RESET)
//  {
//  }
//  
//  /*��ȡ���� */
//  for(; uwBufferSize != 0x00; uwBufferSize--)
//  {
//   *pBuffer++ = *(__IO uint32_t *)(SDRAM_BANK_ADDR + write_pointer );
//    
//   /* ��ַ����*/
//    write_pointer += 4;
//  } 
//}


///**
//  * @brief  ����SDRAM�Ƿ����� 
//  * @param  None
//  * @retval ��������1���쳣����0
//  */
//uint8_t SDRAM_Test(void)
//{
//  /*д�����ݼ�����*/
//  uint32_t counter=0;
//  
//  /* 8λ������ */
//  uint8_t ubWritedata_8b = 0, ubReaddata_8b = 0;  
//  
//  /* 16λ������ */
//  uint16_t uhWritedata_16b = 0, uhReaddata_16b = 0; 
//  
//  SDRAM_INFO("���ڼ��SDRAM����8λ��16λ�ķ�ʽ��дsdram...");


//  /*��8λ��ʽ��д���ݣ���У��*/
//  
//  /* ��SDRAM����ȫ������Ϊ0 ��IS42S16400J_SIZE����8λΪ��λ�� */
//  for (counter = 0x00; counter < IS42S16400J_SIZE; counter++)
//  {
//    *(__IO uint8_t*) (SDRAM_BANK_ADDR + counter) = (uint8_t)0x0;
//  }
//  
//  /* ������SDRAMд������  8λ */
//  for (counter = 0; counter < IS42S16400J_SIZE; counter++)
//  {
//    *(__IO uint8_t*) (SDRAM_BANK_ADDR + counter) = (uint8_t)(ubWritedata_8b + counter);
//  }
//  
//  /* ��ȡ SDRAM ���ݲ����*/
//  for(counter = 0; counter<IS42S16400J_SIZE;counter++ )
//  {
//    ubReaddata_8b = *(__IO uint8_t*)(SDRAM_BANK_ADDR + counter);  //�Ӹõ�ַ��������
//    
//    if(ubReaddata_8b != (uint8_t)(ubWritedata_8b + counter))      //������ݣ�������ȣ���������,���ؼ��ʧ�ܽ����
//    {
//      SDRAM_ERROR("8λ���ݶ�д����");
//      return 0;
//    }
//  }
//	
//  
//  /*��16λ��ʽ��д���ݣ������*/
//  
//  /* ��SDRAM����ȫ������Ϊ0 */
//  for (counter = 0x00; counter < IS42S16400J_SIZE/2; counter++)
//  {
//    *(__IO uint16_t*) (SDRAM_BANK_ADDR + 2*counter) = (uint16_t)0x00;
//  }
//  
//  /* ������SDRAMд������  16λ */
//  for (counter = 0; counter < IS42S16400J_SIZE/2; counter++)
//  {
//    *(__IO uint16_t*) (SDRAM_BANK_ADDR + 2*counter) = (uint16_t)(uhWritedata_16b + counter);
//  }
//  
//    /* ��ȡ SDRAM ���ݲ����*/
//  for(counter = 0; counter<IS42S16400J_SIZE/2;counter++ )
//  {
//    uhReaddata_16b = *(__IO uint16_t*)(SDRAM_BANK_ADDR + 2*counter);  //�Ӹõ�ַ��������
//    
//    if(uhReaddata_16b != (uint16_t)(uhWritedata_16b + counter))      //������ݣ�������ȣ���������,���ؼ��ʧ�ܽ����
//    {
//      SDRAM_ERROR("16λ���ݶ�д����");

//      return 0;
//    }
//  }

//  
//  SDRAM_INFO("SDRAM��д����������"); 
//  /*���������return 1 */
//  return 1;
//  

//}




//#include "./sram/bsp_sram.h"	  



///**
//  * @brief  ��ʼ������SRAM��IO
//  * @param  ��
//  * @retval ��
//  */
//static void SRAM_GPIO_Config(void)
//{
//	GPIO_InitTypeDef  GPIO_InitStructure;
// 
//  /* ʹ��SRAM��ص�GPIOʱ�� */

//                         /*��ַ�ź���*/
//  RCC_AHB1PeriphClockCmd(FSMC_A0_GPIO_CLK | FSMC_A1_GPIO_CLK | FSMC_A2_GPIO_CLK | 
//                         FSMC_A3_GPIO_CLK | FSMC_A4_GPIO_CLK | FSMC_A5_GPIO_CLK |
//                         FSMC_A6_GPIO_CLK | FSMC_A7_GPIO_CLK | FSMC_A8_GPIO_CLK |
//                         FSMC_A9_GPIO_CLK | FSMC_A10_GPIO_CLK| FSMC_A11_GPIO_CLK| 
//												 FSMC_A12_GPIO_CLK| FSMC_A13_GPIO_CLK|FSMC_A14_GPIO_CLK|
//												 FSMC_A15_GPIO_CLK|FSMC_A16_GPIO_CLK|FSMC_A17_GPIO_CLK|FSMC_A18_GPIO_CLK|
//                         /*�����ź���*/
//                         FSMC_D0_GPIO_CLK | FSMC_D1_GPIO_CLK | FSMC_D2_GPIO_CLK | 
//                         FSMC_D3_GPIO_CLK | FSMC_D4_GPIO_CLK | FSMC_D5_GPIO_CLK |
//                         FSMC_D6_GPIO_CLK | FSMC_D7_GPIO_CLK | FSMC_D8_GPIO_CLK |
//                         FSMC_D9_GPIO_CLK | FSMC_D10_GPIO_CLK| FSMC_D11_GPIO_CLK|
//                         FSMC_D12_GPIO_CLK| FSMC_D13_GPIO_CLK| FSMC_D14_GPIO_CLK|
//                         FSMC_D15_GPIO_CLK|  
//                         /*�����ź���*/
//                         FSMC_CS_GPIO_CLK  | FSMC_WE_GPIO_CLK | FSMC_OE_GPIO_CLK |
//                         FSMC_UDQM_GPIO_CLK|FSMC_LDQM_GPIO_CLK, ENABLE);
//												 


//	 /*-- GPIO ���� -----------------------------------------------------*/

//  /* ͨ�� GPIO ���� */
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  
//  /*A��ַ�ź��� �����������*/
//  GPIO_InitStructure.GPIO_Pin = FSMC_A0_GPIO_PIN; 
//  GPIO_Init(FSMC_A0_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A0_GPIO_PORT,FSMC_A0_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A1_GPIO_PIN; 
//  GPIO_Init(FSMC_A1_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A1_GPIO_PORT,FSMC_A1_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A2_GPIO_PIN; 
//  GPIO_Init(FSMC_A2_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A2_GPIO_PORT,FSMC_A2_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A3_GPIO_PIN; 
//  GPIO_Init(FSMC_A3_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A3_GPIO_PORT,FSMC_A3_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A4_GPIO_PIN; 
//  GPIO_Init(FSMC_A4_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A4_GPIO_PORT,FSMC_A4_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A5_GPIO_PIN; 
//  GPIO_Init(FSMC_A5_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A5_GPIO_PORT,FSMC_A5_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A6_GPIO_PIN; 
//  GPIO_Init(FSMC_A6_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A6_GPIO_PORT,FSMC_A6_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A7_GPIO_PIN; 
//  GPIO_Init(FSMC_A7_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A7_GPIO_PORT,FSMC_A7_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A8_GPIO_PIN; 
//  GPIO_Init(FSMC_A8_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A8_GPIO_PORT,FSMC_A8_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A9_GPIO_PIN; 
//  GPIO_Init(FSMC_A9_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A9_GPIO_PORT,FSMC_A9_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A10_GPIO_PIN; 
//  GPIO_Init(FSMC_A10_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A10_GPIO_PORT,FSMC_A10_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A11_GPIO_PIN; 
//  GPIO_Init(FSMC_A11_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A11_GPIO_PORT,FSMC_A11_GPIO_PinSource,FSMC_GPIO_AF);
//	
//  GPIO_InitStructure.GPIO_Pin = FSMC_A12_GPIO_PIN; 
//  GPIO_Init(FSMC_A12_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A12_GPIO_PORT,FSMC_A12_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A13_GPIO_PIN; 
//  GPIO_Init(FSMC_A13_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A13_GPIO_PORT,FSMC_A13_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A14_GPIO_PIN; 
//  GPIO_Init(FSMC_A14_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A14_GPIO_PORT,FSMC_A14_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A15_GPIO_PIN; 
//  GPIO_Init(FSMC_A15_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A15_GPIO_PORT,FSMC_A15_GPIO_PinSource,FSMC_GPIO_AF);  
//	
//  GPIO_InitStructure.GPIO_Pin = FSMC_A16_GPIO_PIN; 
//  GPIO_Init(FSMC_A16_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A16_GPIO_PORT,FSMC_A16_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A17_GPIO_PIN; 
//  GPIO_Init(FSMC_A17_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A17_GPIO_PORT,FSMC_A17_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_A18_GPIO_PIN; 
//  GPIO_Init(FSMC_A18_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_A18_GPIO_PORT,FSMC_A18_GPIO_PinSource,FSMC_GPIO_AF);
//    
//  /*DQ�����ź��� �����������*/
//  GPIO_InitStructure.GPIO_Pin = FSMC_D0_GPIO_PIN; 
//  GPIO_Init(FSMC_D0_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D0_GPIO_PORT,FSMC_D0_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D1_GPIO_PIN; 
//  GPIO_Init(FSMC_D1_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D1_GPIO_PORT,FSMC_D1_GPIO_PinSource,FSMC_GPIO_AF);
//    
//  GPIO_InitStructure.GPIO_Pin = FSMC_D2_GPIO_PIN; 
//  GPIO_Init(FSMC_D2_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D2_GPIO_PORT,FSMC_D2_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D3_GPIO_PIN; 
//  GPIO_Init(FSMC_D3_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D3_GPIO_PORT,FSMC_D3_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D4_GPIO_PIN; 
//  GPIO_Init(FSMC_D4_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D4_GPIO_PORT,FSMC_D4_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D5_GPIO_PIN; 
//  GPIO_Init(FSMC_D5_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D5_GPIO_PORT,FSMC_D5_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D6_GPIO_PIN; 
//  GPIO_Init(FSMC_D6_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D6_GPIO_PORT,FSMC_D6_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D7_GPIO_PIN; 
//  GPIO_Init(FSMC_D7_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D7_GPIO_PORT,FSMC_D7_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D8_GPIO_PIN; 
//  GPIO_Init(FSMC_D8_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D8_GPIO_PORT,FSMC_D8_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D9_GPIO_PIN; 
//  GPIO_Init(FSMC_D9_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D9_GPIO_PORT,FSMC_D9_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D10_GPIO_PIN; 
//  GPIO_Init(FSMC_D10_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D10_GPIO_PORT,FSMC_D10_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D11_GPIO_PIN; 
//  GPIO_Init(FSMC_D11_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D11_GPIO_PORT,FSMC_D11_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D12_GPIO_PIN; 
//  GPIO_Init(FSMC_D12_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D12_GPIO_PORT,FSMC_D12_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D13_GPIO_PIN; 
//  GPIO_Init(FSMC_D13_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D13_GPIO_PORT,FSMC_D13_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D14_GPIO_PIN; 
//  GPIO_Init(FSMC_D14_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D14_GPIO_PORT,FSMC_D14_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_D15_GPIO_PIN; 
//  GPIO_Init(FSMC_D15_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_D15_GPIO_PORT,FSMC_D15_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  /*�����ź���*/
//  GPIO_InitStructure.GPIO_Pin = FSMC_CS_GPIO_PIN; 
//  GPIO_Init(FSMC_CS_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_CS_GPIO_PORT,FSMC_CS_GPIO_PinSource,FSMC_GPIO_AF);
//    
//  GPIO_InitStructure.GPIO_Pin = FSMC_WE_GPIO_PIN; 
//  GPIO_Init(FSMC_WE_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_WE_GPIO_PORT,FSMC_WE_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_OE_GPIO_PIN; 
//  GPIO_Init(FSMC_OE_GPIO_PORT, &GPIO_InitStructure);   
//  GPIO_PinAFConfig(FSMC_OE_GPIO_PORT,FSMC_OE_GPIO_PinSource,FSMC_GPIO_AF);  
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_UDQM_GPIO_PIN; 
//  GPIO_Init(FSMC_UDQM_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_UDQM_GPIO_PORT,FSMC_UDQM_GPIO_PinSource,FSMC_GPIO_AF);
//  
//  GPIO_InitStructure.GPIO_Pin = FSMC_LDQM_GPIO_PIN; 
//  GPIO_Init(FSMC_LDQM_GPIO_PORT, &GPIO_InitStructure);
//  GPIO_PinAFConfig(FSMC_LDQM_GPIO_PORT,FSMC_LDQM_GPIO_PinSource,FSMC_GPIO_AF); 
//}				  			


///**
//  * @brief  ��ʼ��FSMC����
//  * @param  None. 
//  * @retval None.
//  */
//void FSMC_SRAM_Init(void)
//{	
//	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
//	FSMC_NORSRAMTimingInitTypeDef  readWriteTiming;

//	/*��ʼ��SRAM��ص�GPIO*/
//	SRAM_GPIO_Config();
//		
//	/*ʹ��FSMC����ʱ��*/
//	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC,ENABLE);

//	//��ַ����ʱ�䣨ADDSET��Ϊ1��HCLK,1/168M = 6ns
//	readWriteTiming.FSMC_AddressSetupTime = 0x00;	

//	//��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�
//	readWriteTiming.FSMC_AddressHoldTime = 0x00;	 

//	//���ݱ���ʱ�䣨DATAST��+ 1��HCLK = 9/168M=54ns(��EM��SRAMоƬ)	
//	readWriteTiming.FSMC_DataSetupTime = 0x08;		  
//	
//	//��������ת�����ڣ������ڸ���ģʽ��NOR����
//	readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
//	
//	//����ʱ�ӷ�Ƶ��������ͬ�����͵Ĵ洢��
//	readWriteTiming.FSMC_CLKDivision = 0x00;	

//	//���ݱ���ʱ�䣬������ͬ���͵�NOR
//	readWriteTiming.FSMC_DataLatency = 0x00;		
//	
//	//ѡ��ƥ��SRAM��ģʽ
//	readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 
//    

//	// ѡ��FSMCӳ��Ĵ洢���� Bank1 sram4
//	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;
//	
//	//���õ�ַ���������������Ƿ��ã�������NOR
//	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; 
//	
//	//����Ҫ���ƵĴ洢�����ͣ�SRAM����
//	FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;   
//	
//	//�洢�����ݿ�ȣ�16λ
//	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b; 
//	
//	//�����Ƿ�ʹ��ͻ������ģʽ��������ͬ�����͵Ĵ洢��
//	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;
//	
//	//�����Ƿ�ʹ�ܵȴ��źţ�������ͬ�����͵Ĵ洢��
//	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;
//	
//	//���õȴ��źŵ���Ч���ԣ�������ͬ�����͵Ĵ洢��
//	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
//	
//	//�����Ƿ�֧�ְѷǶ����ͻ��������������ͬ�����͵Ĵ洢��
//	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable; 
//	
//	//���õȴ��źŲ����ʱ�䣬������ͬ�����͵Ĵ洢��
//	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
//	
//	//�洢��дʹ�� 
//	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
//	
//	//��ʹ�õȴ��ź�
//	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;  		
//	
//	// ��ʹ����չģʽ����дʹ����ͬ��ʱ��
//	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable; 
//	
//	//ͻ��д����
//	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;  
//	
//	//��дʱ������
//	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;
//	
//	//��дͬ��ʱ��ʹ����չģʽʱ������ò���Ч
//	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &readWriteTiming; 

//	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //��ʼ��FSMC����

//	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  // ʹ��BANK										  
//											
//}
//	  		



/**
  * @brief  �ԡ��֡�Ϊ��λ��sdramд������ 
  * @param  pBuffer: ָ�����ݵ�ָ�� 
  * @param  uwWriteAddress: Ҫд���SRAM�ڲ���ַ
  * @param  uwBufferSize: Ҫд�����ݴ�С
  * @retval None.
  */
void SRAM_WriteBuffer(uint32_t* pBuffer, uint32_t uwWriteAddress, uint32_t uwBufferSize)
{
  __IO uint32_t write_pointer = (uint32_t)uwWriteAddress;
 

  /* ѭ��д������ */
  for (; uwBufferSize != 0; uwBufferSize--) 
  {
    /* �������ݵ�SRAM */
    *(uint32_t *) (Bank1_SRAM4_ADDR + write_pointer) = *pBuffer++;

    /* ��ַ����*/
    write_pointer += 4;
  }
    
}

/**
  * @brief  ��SRAM�ж�ȡ���� 
  * @param  pBuffer: ָ��洢���ݵ�buffer
  * @param  ReadAddress: Ҫ��ȡ���ݵĵ�ʮ
  * @param  uwBufferSize: Ҫ��ȡ�����ݴ�С
  * @retval None.
  */
void SRAM_ReadBuffer(uint32_t* pBuffer, uint32_t uwReadAddress, uint32_t uwBufferSize)
{
  __IO uint32_t write_pointer = (uint32_t)uwReadAddress;
  
  
  /*��ȡ���� */
  for(; uwBufferSize != 0x00; uwBufferSize--)
  {
   *pBuffer++ = *(__IO uint32_t *)(Bank1_SRAM4_ADDR + write_pointer );
    
   /* ��ַ����*/
    write_pointer += 4;
  } 
}


/**
  * @brief  ����SRAM�Ƿ����� 
  * @param  None
  * @retval ��������1���쳣����0
  */
uint8_t SRAM_Test(void)
{
  /*д�����ݼ�����*/
  uint32_t counter=0;
  
  /* 8λ������ */
  uint8_t ubWritedata_8b = 0, ubReaddata_8b = 0;  
  
  /* 16λ������ */
  uint16_t uhWritedata_16b = 0, uhReaddata_16b = 0; 
  
  SRAM_INFO("���ڼ��SRAM����8λ��16λ�ķ�ʽ��дsram...");


  /*��8λ��ʽ��д���ݣ���У��*/
  
  /* ��SRAM����ȫ������Ϊ0 ��IS62WV51216_SIZE����8λΪ��λ�� */
  for (counter = 0x00; counter < IS62WV51216_SIZE; counter++)
  {
    *(__IO uint8_t*) (Bank1_SRAM4_ADDR + counter) = (uint8_t)0x0;
  }
  
  /* ������SRAMд������  8λ */
  for (counter = 0; counter < IS62WV51216_SIZE; counter++)
  {
    *(__IO uint8_t*) (Bank1_SRAM4_ADDR + counter) = (uint8_t)(ubWritedata_8b + counter);
  }
  
  /* ��ȡ SRAM ���ݲ����*/
  for(counter = 0; counter<IS62WV51216_SIZE;counter++ )
  {
    ubReaddata_8b = *(__IO uint8_t*)(Bank1_SRAM4_ADDR + counter);  //�Ӹõ�ַ��������
    
    if(ubReaddata_8b != (uint8_t)(ubWritedata_8b + counter))      //������ݣ�������ȣ���������,���ؼ��ʧ�ܽ����
    {
      SRAM_ERROR("8λ���ݶ�д����");
      return 0;
    }
  }
	
  
  /*��16λ��ʽ��д���ݣ������*/
  
  /* ��SRAM����ȫ������Ϊ0 */
  for (counter = 0x00; counter < IS62WV51216_SIZE/2; counter++)
  {
    *(__IO uint16_t*) (Bank1_SRAM4_ADDR + 2*counter) = (uint16_t)0x00;
  }
  
  /* ������SRAMд������  16λ */
  for (counter = 0; counter < IS62WV51216_SIZE/2; counter++)
  {
    *(__IO uint16_t*) (Bank1_SRAM4_ADDR + 2*counter) = (uint16_t)(uhWritedata_16b + counter);
  }
  
    /* ��ȡ SRAM ���ݲ����*/
  for(counter = 0; counter<IS62WV51216_SIZE/2;counter++ )
  {
    uhReaddata_16b = *(__IO uint16_t*)(Bank1_SRAM4_ADDR + 2*counter);  //�Ӹõ�ַ��������
    
    if(uhReaddata_16b != (uint16_t)(uhWritedata_16b + counter))      //������ݣ�������ȣ���������,���ؼ��ʧ�ܽ����
    {
      SRAM_ERROR("16λ���ݶ�д����");

      return 0;
    }
  }
  
  SRAM_INFO("SRAM��д����������"); 
  /*���������return 1 */
  return 1;

}


/*********************************************END OF FILE**********************/

