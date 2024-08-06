#include "GPIO_interrupt.h"

/*
 * Trigger: FALLING OR RISING mode
 * Priority: 0->15 (0 is the highest priority and 15 is the lowest priority);
 */
SON_STATUS_t SON_EXTI_GPIO_Enable(SON_GPIO_t GPIOx, SON_GPIO_Pin_t GPIO_Pin,
		SON_Trigger_t Trigger, uint8_t Priority)
{
	if(Priority > 15 || ((Trigger != SON_FALLING) && (Trigger != SON_RISING)))
	{
		return SON_ERROR;
	}
	SON_SYSCFG->EXTICR[GPIO_Pin / 4] &= ~(0x0f << ((GPIO_Pin % 4) * 4));
	SON_SYSCFG->EXTICR[GPIO_Pin / 4] |= (GPIOx << ((GPIO_Pin % 4) * 4));

	SON_EXTI->IMR |= (0x01 << GPIO_Pin);
	if(Trigger == SON_FALLING)
	{
		EXTI->FTSR |= (0x01 << GPIO_Pin);
	}
	else if(Trigger == SON_RISING)
	{
		EXTI->RTSR |= (0x01 << GPIO_Pin);
	}

	if(GPIO_Pin <= SON_GPIO_Pin_4)
	{
		SON_NVIC->ISER[0] |= (0x01 << (GPIO_Pin - SON_GPIO_Pin_0 + 6));
		SON_NVIC->IPR[(GPIO_Pin - SON_GPIO_Pin_0 + 6)] = (uint8_t)(Priority << 4);
	}
	else if(GPIO_Pin <= SON_GPIO_Pin_9)
	{
		SON_NVIC->ISER[0] |= (0x01 << 23);
		SON_NVIC->IPR[23] = (uint8_t)(Priority << 4);
	}
	else if(GPIO_Pin <= SON_GPIO_Pin_15)
	{
		SON_NVIC->ISER[1] |= (0x01 << 8);
		SON_NVIC->IPR[40] = (uint8_t)(Priority << 4);
	}
	else
	{
		return SON_ERROR;
	}
	return SON_OK;
}

SON_STATUS_t SON_EXTI_GPIO_Unenable(SON_GPIO_t GPIOx,SON_GPIO_Pin_t GPIO_Pin)
{
	SON_EXTI->IMR &= ~(0x01 << GPIO_Pin);
	if(GPIO_Pin <= SON_GPIO_Pin_4)
	{
		SON_NVIC->ISER[0] &=~ (0x01 << (GPIO_Pin - GPIO_PIN_0 + 6));
	}
	else if(GPIO_Pin <= SON_GPIO_Pin_9)
	{
		SON_NVIC->ISER[0] &=~ (0x01 << 23);
	}
	else if(GPIO_Pin <= SON_GPIO_Pin_15)
	{
		SON_NVIC->ISER[1] &=~ (0x01 << 8);
	}
	else
	{
		return SON_ERROR;
	}
	return SON_OK;
}

weak_func void SON_EXTI0_IRQHandler();
weak_func void SON_EXTI1_IRQHandler();
weak_func void SON_EXTI2_IRQHandler();
weak_func void SON_EXTI3_IRQHandler();
weak_func void SON_EXTI4_IRQHandler();
weak_func void SON_EXTI9_5_IRQHandler(SON_GPIO_Pin_t GPIO_Pin);
weak_func void SON_EXTI15_10_IRQHandler(SON_GPIO_Pin_t GPIO_Pin);

void EXTI0_IRQHandler()
{
	SON_EXTI0_IRQHandler();
	SON_EXTI->PR |= (0x01 << 0);
}


void EXTI1_IRQHandler()
{
	SON_EXTI1_IRQHandler();
	SON_EXTI->PR |= (0x01 << 1);
}

void EXTI2_IRQHandler()
{
	SON_EXTI2_IRQHandler();
	SON_EXTI->PR |= (0x01 << 2);
}

void EXTI3_IRQHandler()
{
	SON_EXTI3_IRQHandler();
	SON_EXTI->PR |= (0x01 << 3);
}

void EXTI4_IRQHandler()
{
	SON_EXTI4_IRQHandler();
	SON_EXTI->PR |= (1 << 4);
}

void EXTI9_5_IRQHandler()
{
	if(((SON_EXTI->PR >> 5)& 0x01) == 1)
	{
		SON_EXTI9_5_IRQHandler(SON_GPIO_Pin_5);
		SON_EXTI->PR |= (0x01 << 5);
	}

	if(((SON_EXTI->PR >> 6)& 0x01) == 1)
	{
		SON_EXTI9_5_IRQHandler(SON_GPIO_Pin_6);
		SON_EXTI->PR |= (0x01 << 6);
	}

	if(((SON_EXTI->PR >> 7)& 0x01) == 1)
	{
		SON_EXTI9_5_IRQHandler(SON_GPIO_Pin_7);
		SON_EXTI->PR |= (0x01 << 7);
	}

	if(((SON_EXTI->PR >> 8)& 0x01) == 1)
	{
		SON_EXTI9_5_IRQHandler(SON_GPIO_Pin_8);
		SON_EXTI->PR |= (0x01 << 8);
	}

	if(((SON_EXTI->PR >> 9)& 0x01) == 1)
	{
		SON_EXTI9_5_IRQHandler(SON_GPIO_Pin_9);
		SON_EXTI->PR |= (0x01 << 9);
	}

}

void EXTI15_10_IRQHandler()
{
	if(((SON_EXTI->PR >> 10)& 0x01) == 1)
	{
		SON_EXTI15_10_IRQHandler(SON_GPIO_Pin_10);
		SON_EXTI->PR |= (0x01 << 10);
	}

	if(((SON_EXTI->PR >> 11)& 0x01) == 1)
	{
		SON_EXTI15_10_IRQHandler(SON_GPIO_Pin_11);
		SON_EXTI->PR |= (0x01 << 11);
	}

	if(((SON_EXTI->PR >> 12)& 0x01) == 1)
	{
		SON_EXTI15_10_IRQHandler(SON_GPIO_Pin_12);
		SON_EXTI->PR |= (0x01 << 12);
	}

	if(((SON_EXTI->PR >> 13)& 0x01) == 1)
	{
		SON_EXTI15_10_IRQHandler(SON_GPIO_Pin_13);
		SON_EXTI->PR |= (0x01 << 13);
	}

	if(((SON_EXTI->PR >> 14)& 0x01) == 1)
	{
		SON_EXTI15_10_IRQHandler(SON_GPIO_Pin_14);
		SON_EXTI->PR |= (0x01 << 14);
	}

	if(((SON_EXTI->PR >> 15)& 0x01) == 1)
	{
		SON_EXTI15_10_IRQHandler(SON_GPIO_Pin_15);
		SON_EXTI->PR |= (0x01 << 15);
	}
}



weak_func void SON_EXTI0_IRQHandler()
{

}

weak_func void SON_EXTI1_IRQHandler()
{

}

weak_func void SON_EXTI2_IRQHandler()
{

}

weak_func void SON_EXTI3_IRQHandler()
{

}

weak_func void SON_EXTI4_IRQHandler()
{

}

weak_func void SON_EXTI9_5_IRQHandler(SON_GPIO_Pin_t GPIO_Pin)
{

}

weak_func void SON_EXTI15_10_IRQHandler(SON_GPIO_Pin_t GPIO_Pin)
{

}

