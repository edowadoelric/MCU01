/* Library includes. */
#include "stm32f10x.h"
#include "system_stm32f10x.h"
#include "stm32f10x_it.h"
#include <string.h>     //stlen用
#include <stdarg.h>     //tsprintf用

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#ifdef GLOBAL_INSTANCE
#define GLOBAL
#else
#define GLOBAL extern 
#endif

#include "function.h"

//encoder.c
GLOBAL uint16_t LeftAngle;
GLOBAL uint16_t RightAngle;

//servo.c
//GLOBAL uint8_t ServoRxData[80]; //受信バッファ
//GLOBAL uint8_t ServoRxcount;    //受信カウント

//uart1.c
struct PCtoMCU {	/* PC to MCU Struct*/
	
	uint8_t Command;
	uint8_t Length;	
	int8_t 	MoterLeftPwm;
	int8_t	MoterRightPwm;
	int16_t Distance;
	int16_t Angle;

};

struct  MCUtoPC{	/* MCU to PC Struct*/

	uint8_t Command;
	uint8_t Length;	
	uint8_t CompleteFlag;
	uint8_t dumm;
	int16_t EncoderLeft;
	int16_t EncoderRight;
};

GLOBAL xQueueHandle PCtoUart1_Queue;
GLOBAL xQueueHandle Uart1toParam_Queue;
GLOBAL xQueueHandle Uart1toPC_Queue;

GLOBAL struct PCtoMCU Com1RxMsg;
GLOBAL struct MCUtoPC Com1TxMsg;

//debug.c
GLOBAL uint8_t LED1;
GLOBAL uint8_t LED2;
GLOBAL uint8_t LED3;
