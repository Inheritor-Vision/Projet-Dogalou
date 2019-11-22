// TOUT A FAIRE !! //

/*
 indispensable pour pouvoir adresser les registres des périphériques.
 Rem : OBLIGATION d'utiliser les définitions utiles contenues dans ce fichier (ex : TIM_CR1_CEN, RCC_APB1ENR_TIM2EN ...)
 pour une meilleure lisibilité du code.

 Pour les masques, utiliser également les définitions proposée
 Rappel : pour mettre à 1  , reg = reg | Mask (ou Mask est le représente le ou les bits à positionner à 1)
				  pour mettre à 0  , reg = reg&~ Mask (ou Mask est le représente le ou les bits à positionner à 0)
 
*/ 
#include "stm32f103xb.h" 

void (*pt1)(void);
void (*pt2)(void);
void (*pt3)(void);
void (*pt4)(void);

void TIM2_IRQHandler(void){
	TIM2->SR &= ~(1);
	(*pt1)();
	
}

void TIM1_UP_IRQHandler(){
	TIM1->SR &= ~(1);
	(*pt2)();
	
}

void TIM3_IRQHandler (){
	TIM3->SR &= ~(1);
	(*pt3)();	
}

void TIM4_IRQHandler (){
	TIM4->SR &= ~(1);
	(*pt4)();	
}


void MyTimer_Conf(TIM_TypeDef * Timer,int Arr, int Psc){
	if(Timer == TIM1){
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	}else if (Timer==TIM2){
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	}else if (Timer==TIM3){
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	}else if (Timer==TIM4){
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	}
	Timer->ARR = Arr;
	Timer->PSC = Psc;
}

void MyTimer_Start(TIM_TypeDef * Timer){
	if(Timer == TIM1){
		TIM1->CR1 |= 0x1;
	}else if (Timer==TIM2){
		TIM2->CR1 |= 0x1;
	}else if (Timer==TIM3){
		TIM3->CR1 |= 0x1;
	}else if (Timer==TIM4){
		TIM4->CR1 |= 0x1;
	}
}
void MyTimer_Stop(TIM_TypeDef * Timer){
	if(Timer == TIM1){
		TIM1->CR1 &= ~(0x1);
	}else if (Timer==TIM2){
		TIM2->CR1 &= ~(0x1);
	}else if (Timer==TIM3){
		TIM3->CR1 &= ~(0x1);
	}else if (Timer==TIM4){
		TIM4->CR1 &= ~(0x1);
	}
}

void MyTimer_IT_Enable(TIM_TypeDef * Timer){
	if(Timer == TIM1){
			TIM1->DIER |= (1);
	}else if (Timer==TIM2){
			TIM2->DIER |= (1);
	}else if (Timer==TIM3){
			TIM3->DIER |= (1);
	}else if (Timer==TIM4){
			TIM4->DIER |= (1);
	}
}

void MyTimer_IT_Disable(TIM_TypeDef * Timer){
	if(Timer == TIM1){
			TIM1->DIER &= ~(1);
	}else if (Timer==TIM2){
			TIM2->DIER &= ~(1);
	}else if (Timer==TIM3){
			TIM3->DIER &= ~(1);
	}else if (Timer==TIM4){
			TIM4->DIER &= ~(1);
	}
}

void MyTimer_IT_Conf(TIM_TypeDef * Timer, void (*IT_function) (void),int Prio){
	if(Timer == TIM1){
		NVIC_SetPriority(TIM1_UP_IRQn,Prio);
		NVIC_EnableIRQ(TIM1_UP_IRQn);
		pt1 = IT_function;
	}else if (Timer==TIM2){
		NVIC_SetPriority(TIM2_IRQn,Prio);
		NVIC_EnableIRQ(TIM2_IRQn);
		pt2 = IT_function;
	}else if (Timer==TIM3){
		NVIC_SetPriority(TIM3_IRQn,Prio);
		NVIC_EnableIRQ(TIM3_IRQn);
		pt3 = IT_function;
	}else if (Timer==TIM4){
		NVIC_SetPriority(TIM4_IRQn,Prio);
		NVIC_EnableIRQ(TIM4_IRQn);
		pt4 = IT_function;
	}
}



