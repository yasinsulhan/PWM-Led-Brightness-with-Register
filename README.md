# deneme
Pulse width modulation is an essential technology used in a variety of electronic applications. From motor control to LED lighting, this technique allows for efficient and precise control of power delivery. The most essential thing for PWM is duty cycle. Duty cycle is the ratio of time a load or circuit is ON compared to the time the load or circuit is OFF. 

![duty-cycle-explained](https://github.com/yasinsulhan/deneme/assets/109728194/963d241d-2130-4bc0-b39e-79bc354c89ed)

As shown, the image above explains how duty cyle work. ***The percentage says that how much the system is ON.*** This is used for led brightness, motor speed, duration of working etc.

In this project, the brightness of leds will increase and decrease simultaneously. The leds in the project belong PD12, PD13, PD14, PD15 simultaneously. These are declared TIM4 (timer4) channels in datasheet as shown below.

![2_pin_and_ball_definitions](https://github.com/yasinsulhan/deneme/assets/109728194/93da1c5d-0279-48eb-af8b-5e11d328a116)

Timers can generate waveforms. Pulse lengths and waveform periods can be modulated from a few microseconds to several milliseconds using the timer prescaler and the RCC clock controller prescalers. So, PWM is involved timers. Before PWM is set, the timers must be arranged.

According to block diagram, Port D (PD12, PD13, PD14, PD15) is connected to AHB1 clock. TIM4 is connected to APB1 clock. These clock lines must be enabled via registers. Also these pins will be used as alternate function. Then, the most important part that is PWW frequency, period and timer tick frequency must be calculated.

**Period = (Timer_Tick_Frequency / PWM_frequency) -1**

**PWM_frequency = Timer_Tick_Frequency / (Period+1)**

**Timer_Tick_Frequency = Timer_CLK / (Prescaler+1)**

Actually there two values that can be determined which they are PWM frequency and period. PWM frequency indicate how much the brightness is. The timer clock is 42 MHz as shown in block diagram. However, this is assumed as 84 Mhz in this project. Because HCLK is assumed as 168 MHz this makes **APB1 Clock line will be 84 MHz.**

![3_clock_ispat](https://github.com/yasinsulhan/deneme/assets/109728194/cd398a5a-8628-4da3-80b8-03e1dcc4747d)

In this project, period **(ARR+1 = 99+1)** will be 100, prescaler will be 84 **(PSC+1 = 83+1)**. Because of that, PWM frequency must be much bigger due to observing brightnesses of leds.

**Timer_Tick_Frequency = 84000000 / (83+1) = 1000000Hz**
**PWM_frequency = 1000000 / (99+1) = ** 100000Hz**

As calculated above, the max frequency must be **10000Hz**. It goes from 0 to 10000 according to, led brightness.

After calculation, the timer 4 must be adjusted in registers. It is similar with [previous timer example](https://github.com/yasinsulhan/stm32f4-timer-interrupt-with-register)

The capture compare output 1,2,3,4 (for PD12, PD13, PD14, PD15) must be selected in `CCMRx` registers. Also these must be PWM mode by using the same registers. 

To be set proper frequency value, all capture compares must be enabled in `CCER` registers. Finally, All these values are declared in `CCRx` registers as shown in the loop.

```
  while (1)
  {
	  // For Brightness
    // From low to high
	  for(int i=0; i<100;i++)
	  {
		  TIM4->CCR1 |= i;        // PD12->Led1
		  delayy(20);             
		  TIM4->CCR2 |= i;        // PD13->Led2
		  delayy(20);
		  TIM4->CCR3 |= i;        // PD14->Led3
		  delayy(20);
		  TIM4->CCR4 |= i;        // PD15->Led4
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
```










