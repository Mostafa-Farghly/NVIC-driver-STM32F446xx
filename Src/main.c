/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 */

#include "std_types.h"
#include "nvic.h"
#include <stdio.h>

#define TEST_NUM		4

void SCB_priorityGroupInit(uint8 a_priorityG);

int main(void)
{
	SCB_priorityGroupInit(0b101);

	NVIC_enableIRQ(EXTI0_IRQ);
	NVIC_enableIRQ(SPI1_IRQ);

#if TEST_NUM == 1

	/*
	 * Test 1
	 *
	 * EXTI0 Group Priority is greater than SPI1 Group Priority
	 *
	 * Expected result: No Nesting
	 */

	NVIC_setPriority(EXTI0_IRQ, 2, 0);
	NVIC_setPriority(SPI1_IRQ, 3, 0);

#elif TEST_NUM == 2

	/*
	 * Test 2
	 *
	 * EXTI0 Group Priority is smaller than SPI1 Group Priority
	 *
	 * Expected result: Nesting
	 */

	NVIC_setPriority(EXTI0_IRQ, 3, 0);
	NVIC_setPriority(SPI1_IRQ, 2, 0);

#elif TEST_NUM == 3

	/*
	 * Test 3
	 *
	 * EXTI0 Group Priority is equal to SPI1 Group Priority
	 * EXTI0 sub Priority is grater than SPI1 sub Priority
	 *
	 * Expected result: No Nesting
	 */

	NVIC_setPriority(EXTI0_IRQ, 2, 0);
	NVIC_setPriority(SPI1_IRQ, 2, 1);

#elif TEST_NUM == 4

	/*
	 * Test 4
	 *
	 * EXTI0 Group Priority is equal to SPI1 Group Priority
	 * EXTI0 sub Priority is smaller than SPI1 sub Priority
	 *
	 * Expected result: No Nesting
	 */

	NVIC_setPriority(EXTI0_IRQ, 2, 2);
	NVIC_setPriority(SPI1_IRQ, 2, 0);

#endif

	NVIC_SetPendingIRQ(EXTI0_IRQ);

	/* Loop forever */
	for(;;);
}

/* ----------------- SCB Priority Grouping Initialization Function ----------------- */
void SCB_priorityGroupInit(uint8 a_priorityG)
{
	a_priorityG &= 0x7;

	*((uint32 *)(0xE000ED0CUL)) = 0x05FA0000UL | (a_priorityG << 8);
}

/* ------------------------------------- ISRs ------------------------------------- */

void EXTI0_IRQHandler(void)
{
	printf("In EXTI0 Handler\n");

	NVIC_SetPendingIRQ(SPI1_IRQ);

	printf("NVIC_getPendingIRQ(SPI1_IRQ) = %d\n", NVIC_getPendingIRQ(SPI1_IRQ));

	while(1);
}

void SPI1_IRQHandler(void)
{
	printf("In SPI1 Handler\n");
	printf("NVIC_getPendingIRQ(EXTI0_IRQ) = %d\n", NVIC_getPendingIRQ(EXTI0_IRQ));
	while(1);
}
