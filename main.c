#define GLOBAL_INSTANCE 
#include "global.h"

void RCC_Configuration(void);
void RCC_Configuration1(void);
void GPIO_Configuraion(void);
void TIM1_Configuration(void);  
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

uint8_t cnt=0;
uint8_t TestData[20]="test\n\r";

void main (void)
{

  /* クロックの設定 */
  SystemInit();
  
  /* Configure the perphral clocks */
  RCC_Configuration();
  
  /*********使用機能一覧**********/
  //UART1           PCとの通信用
  //エンコーダ      駆動用モータ2個分
  //モータ                〃
  //デバッグLED     表示用3個分
  
  
  /* Uart1の初期設定*/
  vUart1_Init();
  
  /* 超音波センサの初期設定 */
  //vUltraSonic_Init();
  
  //vEncoder_Init();
  
  //vServo_Init();
  
  //vDcMotor_Init();
  
  vDebug_Init();
  
  /* Configure the GPIO */
  GPIO_Configuraion();
  
  /*タスク生成*/
  xTaskCreate( vTask1, "Task1", 100, NULL, 1, NULL);
  xTaskCreate( vTask2, "Task2", 100, NULL, 1, NULL);
  
  /*スケジューリング開始*/
  vTaskStartScheduler();
    
   
  while(1)
  {
         
   }
  
}

/* Task1 ---------------------------------------------------------*/
void vTask1(void *pvParameters)
{
  
  while(1) {  
      /*
      LED1 = (~LED1)&0x01;
      LED2 = (~LED2)&0x01;
      LED3 = (~LED3)&0x01;
    
      vTaskDelay(100000);
      */
  }
}

/* Task2 ---------------------------------------------------------*/
void vTask2(void *pvParameters){
    while(1){ 
        //itoa(TIM3->CNT,TIM2->CNT);
        //itoa(CNT);

        //cTxdata[0]=1+48;
        //cCount = strlen((char*)cTxdata);
        //vUSART1_Send_String(cTxdata ,(uint8_t)cCount);

        //if(cnt==0)
        //KServo_Ping(0xe0);

        //cnt=1;  

        xQueueSendToBack(Uart1toPC_Queue, TestData, portMAX_DELAY);
          
        vTaskDelay(1000);
    }
  
}

/* RCC_Configration ----------------------------------------------------------*/
void RCC_Configuration(void)
{
  RCC_PCLK1Config(RCC_HCLK_Div4);
  
  /* Enable DMA clocks 
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);*/

  /* Enable USART2, TIM3, clocks
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 |
                         RCC_APB1Periph_TIM3 |
                         RCC_APB1Periph_TIM2, ENABLE);*/
  
  /* Enable AFIO, GPIOA, GPIOB, USART1 clocks */
  RCC_APB2PeriphClockCmd(  RCC_APB2Periph_AFIO 
                         //| RCC_APB2Periph_TIM4 
                         //| RCC_APB2Periph_GPIOA 
                         | RCC_APB2Periph_GPIOB
                         | RCC_APB2Periph_USART1    
                         //| RCC_APB2Periph_ADC1 
                         , ENABLE);
   
}

/* GPIO_Configration --------------------------------------------------------*/
void GPIO_Configuraion(void)
{ 
  /*STBee_mini SWD enable*/
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
  
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /*
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  */
    
  /*configrate GPIO pin*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  
  
}
