#include "acc.h"
#include "stm32f1xx_ll_adc.h"
#include "stm32f103xb.h" 
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_usart.h"
#include "Chrono.h"

int initial_level = -1;

void BAT_init(){
	//enable RCC apb2
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC2);
	//Initialisation globale de l'adc
	LL_ADC_InitTypeDef can2;
	LL_ADC_StructInit(&can2);
	can2.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
	can2.SequencersScanMode = LL_ADC_SEQ_SCAN_DISABLE;
	LL_ADC_Init(ADC2, &can2);
	
	//initialisation du groupe REGULAR
	LL_ADC_REG_InitTypeDef can2Reg;
	LL_ADC_REG_StructInit(&can2Reg);
	can2Reg.ContinuousMode = LL_ADC_REG_CONV_SINGLE;
	can2Reg.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE ;
	can2Reg.SequencerLength = LL_ADC_REG_SEQ_SCAN_DISABLE;
	can2Reg.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE ;
	LL_ADC_REG_Init(ADC2,&can2Reg);
	
		
	//config channel
	LL_ADC_SetChannelSamplingTime(ADC2, LL_ADC_CHANNEL_12, LL_ADC_SAMPLINGTIME_1CYCLE_5);
	
	//allumer GPIOC 
	LL_APB1_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
	
	//configurer GPIOC
	LL_GPIO_InitTypeDef PC2;
	LL_GPIO_StructInit(&PC2);
	
	PC2.Mode = LL_GPIO_MODE_ALTERNATE;

	
	
	PC2.Pin = LL_GPIO_PIN_2;

	
	
	LL_GPIO_Init(GPIOC, &PC2);

	LL_ADC_Enable(ADC2);
}

int BAT_level() {
	LL_ADC_REG_SetSequencerRanks(ADC2, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_12);
	LL_ADC_REG_StartConversionSWStart(ADC2);
	int a = LL_ADC_REG_ReadConversionData12(ADC2);
	return a;
}

void BAT_send(){

}
void Usart_Conf(){
	//enable Clock A pour le pin PA2
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
	LL_GPIO_InitTypeDef sortie;
	LL_GPIO_StructInit(&sortie);
	sortie.Pin = LL_GPIO_PIN_2;
	sortie.Mode = LL_GPIO_MODE_ALTERNATE;
	sortie.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	sortie.Pull = LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(GPIOA, &sortie);
	
	//PA2 output push pull 
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
	LL_USART_InitTypeDef uart;
	LL_USART_StructInit(&uart);
	
	uart.BaudRate = 19200;
	
	LL_USART_Init(USART2,&uart);
	
	LL_USART_Enable(USART2);
	
	
	
}

void send_ALERT(){
	Time Chrono_Time = (*Chrono_Read());
LL_USART_TransmitData8(USART2,(char)((int)Chrono_Time.Min/10 + 48));
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,(char)((int)Chrono_Time.Min-((int)Chrono_Time.Min/10)*10 +48));
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,':');
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,(char)((int)Chrono_Time.Sec/10 + 48));
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,(char)((int)Chrono_Time.Sec-((int)Chrono_Time.Sec/10)*10 +48));
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,':');
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,(char)((int)Chrono_Time.Hund/10 + 48));
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,(char)((int)Chrono_Time.Hund-((int)Chrono_Time.Hund/10)*10 +48));
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}	
LL_USART_TransmitData8(USART2,'-');
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,'A');
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,'L');
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,'E');
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,'R');
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,'T');
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,'E');
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,' ');
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,'B');
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,'A');
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,'T');
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,'T');
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,'E');
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,'R');
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,'I');
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,'E');
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
LL_USART_TransmitData8(USART2,(char)13);
while(LL_USART_IsActiveFlag_TXE(USART2) == 0){
}
}

int BAT_verifyLevel(){
	int res = 0;
		if (initial_level == -1){
			initial_level = BAT_level();
			res=0;
		}else if (initial_level == -2){
			res = 3;
		}else{
			int a = BAT_level();
			res = 1;
			if (initial_level * 0.8 >= a){
				BAT_send();
				initial_level = -2;
				Usart_Conf();
				send_ALERT();
				res = 2;

			}
		}
		return res;
		
}
