#include "acc.h"
#include "stm32f1xx_ll_adc.h"
#include "stm32f103xb.h" 
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"



void ACC_init(){
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
	LL_ADC_SetChannelSamplingTime(ADC2, LL_ADC_CHANNEL_10, LL_ADC_SAMPLINGTIME_1CYCLE_5);
	LL_ADC_SetChannelSamplingTime(ADC2, LL_ADC_CHANNEL_11, LL_ADC_SAMPLINGTIME_1CYCLE_5);
	
	//allumer GPIOC 
	LL_APB1_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
	
	//configurer GPIOC
	LL_GPIO_InitTypeDef PC0, PC1;
	LL_GPIO_StructInit(&PC0);
	LL_GPIO_StructInit(&PC1);
	
	
	PC0.Mode = LL_GPIO_MODE_ALTERNATE;
	PC1.Mode = LL_GPIO_MODE_ALTERNATE;
	
	
	PC0.Pin = LL_GPIO_PIN_0;
	PC1.Pin = LL_GPIO_PIN_1;
	
	
	LL_GPIO_Init(GPIOC, &PC0);
	LL_GPIO_Init(GPIOC, &PC1);
	LL_ADC_Enable(ADC2);
	
}

int ACC_readX(){
		//a repeter
	//LL_ADC_REG_SetSequencerLength (ADC2, LL_ADC_REG_SEQ_SCAN_DISABLE);
	LL_ADC_REG_SetSequencerRanks(ADC2, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_10);
	LL_ADC_REG_StartConversionSWStart(ADC2);
	int a = LL_ADC_REG_ReadConversionData12(ADC2);
	return a;
}

int ACC_readY(){
	//a repeter
	//LL_ADC_REG_SetSequencerLength (ADC2, LL_ADC_REG_SEQ_SCAN_DISABLE);
	LL_ADC_REG_SetSequencerRanks(ADC2, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_11);
	LL_ADC_REG_StartConversionSWStart(ADC2);
	int b = LL_ADC_REG_ReadConversionData12(ADC2);
	return b;
}


int is_good_inclination(){
	int b=ACC_readX();
	int a=ACC_readY();
	double c = ((double)a)/((double)b);
	//if( a<1750 && a>1200 && b>1998){
	if(c>(0.69) && c<(0.98)){
		return 1;
	}else{
		return 0;
		}
}
// droit 0.81
// penche mat droite < 45 0.75
// penche m g  < 45 0.85
//penche m d > 45 0.68
// penche m g > 45 1.85
// penche m d 45 0.70
// penche m g 45 0.97
