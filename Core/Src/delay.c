#include"delay.h"

static uint32_t tick = 0;
static uint32_t tick_delay = 0;

void SON_Delay_Init(uint32_t frequency_system_timer)//frequency_system_timer is frequency you provide for system timer
{
	SON_SYST->RVR = (uint32_t)(frequency_system_timer/1000 - 1);
	//CLKSOURCE = 1(prescaler = 1)
	SON_SYST->CSR |= 0x07;
}

void SON_Delay(uint32_t ms)
{
	tick_delay = 0;
	while(tick_delay <= ms);
}

void SysTick_Handler()
{
	tick++;
	tick_delay++;
	SON_SYST->CSR &= ~(1 << 16);
}

uint32_t SON_GetTick()
{
	return tick;
}

