#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void delayy(uint32_t time)
{
	while(time)
		time--;

}

void RCC_Config()
{
	RCC->CR |= 0x00030000;										// HSEON and HSEONRDY enable
	while(!(RCC->CR & 0x00020000));								// HSEON Ready Flag wait
	RCC->CR |= 0x00080000;										// CSS Enable
	RCC->CR |= 0x01000000;										// PLL ON
	RCC->PLLCFGR |= 0x00400000;									// PLL e HSE seçtik
	RCC->PLLCFGR |= 0x00000004;									// PLL M = 4
	RCC->PLLCFGR |= 0x00005A00;									// Pll N = 168
	RCC->PLLCFGR |= 0x00000000;									// PLL p = 2
	RCC->CFGR |= 0x00000000;									// AHB Prescaler = 1
	RCC->CFGR |= 0x00080000;									// APB2 Prescaler = 2
	RCC->CFGR |= 0x00001400;									// APB1 Prescaler = 4
	RCC->CIR |= 0x00080000;										// HSERDY Flag clear
	RCC->CIR |= 0x00800000;										// CSS Flag clear
}

void GPIO_Config()
{
	RCC->AHB1ENR |= 1 << 3;

	GPIOD->MODER |= 2 << 24 | 2 << 26  |  2 << 28 | 2 << 30;	// Port D -> Pin 12 | Pin 13 | Pin 14 | Pin 15 Alternate Function selected
	GPIOD->AFR[1] |= 2 << 16 | 2 << 20 | 2 << 24 | 2 << 28;		// Port D -> Pin 12 | Pin 13 | Pin 14 | Pin 15 Tim4 -> Channel selected
}

void TIM_Config()
{
	RCC->APB1ENR |= 1 << 2;										// TIM4 clock enable

	TIM4->CR1 |= 0 << 4;										// Timer counter mode is Upcounter
	TIM4->CR1 |= 0 << 5;										// Center-aligned mode edge-aligned mode selected
	TIM4->CR1 |= 0 << 8;										// Clock division 1
	TIM4->PSC = 83;												// Prescaler value 84
	TIM4->ARR = 99;												// Period value 100

	/*
	 * Capture/Compare 1 output selected
	 * Output Compare 1 pwm mode 1 selected
	 * Capture/Compare 2 output selected
	 * Output Compare 2 pwm mode 1 selected
	 */
	TIM4->CCMR1 |= 0 << 0 | 6 << 4 | 0 << 8 | 6 << 12;

	/*
	 * Capture/Compare 3 output selected
	 * Output Compare 3 pwm mode 1 selected
	 * Capture/Compare 4 output selected
	 * Output Compare 4 pwm mode 1 selected
	 */
	TIM4->CCMR2 |= 0 << 0 | 6 << 4  | 0 << 8| 6 << 12;

	/*
	 * Capture/Compare 1 output enable
	 * Capture/Compare 2 output enable
	 * Capture/Compare 3 output enable
	 * Capture/Compare 4 output enable
	 */
	TIM4->CCER |= 1 << 0 | 1 << 4 | 1 << 8 | 1 << 12;

	TIM4->CR1 |= 1 << 0;										// Counter Enable
}

int main(void)
{
	RCC_Config();
	GPIO_Config();
	TIM_Config();
  while (1)
  {
	  //For Brightness
	  // From low to high
	  for(int i=0; i<100;i++)
	  {
		  TIM4->CCR1 |= i;		// PD12->Led1
		  delayy(20);
		  TIM4->CCR2 |= i;		// PD13->Led2
		  delayy(20);
		  TIM4->CCR3 |= i;		// PD14->Led3
		  delayy(20);
		  TIM4->CCR4 |= i;		// PD15->Led4
		  delayy(20);
	  }

	  // From high to low
	  for(int i=100; i>0;i--)
	  {
		  TIM4->CCR1 |= i;
		  delayy(20);
		  TIM4->CCR2 |= i;
		  delayy(20);
		  TIM4->CCR3 |= i;
		  delayy(20);
		  TIM4->CCR4 |= i;
		  delayy(20);
	  }
  }
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}


uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
