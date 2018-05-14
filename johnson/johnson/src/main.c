/*
 * P2 Johnson Due
 *
 * Created: 2015-06-17 14:32:55
 *  Author: Philip Ekholm, 
 */ 

#include <asf.h>

#include "motor_task.h"
#include "main_task.h"

#include "drivers/console_driver.h"
#include "drivers/delay.h"
#include "drivers/encoder.h"
#include "pin_mapper.h"
#include "MotorControll.h"
#include "config/PWM_Configuration.h"
#include "TWI.h"
// 	uint8_t array[10] = {};
// 	twi_packet_t packet_pos ={
// 		.addr[0] = 0x00,
// 		.addr [1]=0,
// 		.addr_length =0,
// 		.chip = unoAddress,
// 		.buffer = array,
// 		.length =10,
// 	};

int main (void)

{
	sysclk_init();
	board_init();
	delay_init();
	ioport_init();
	console_init();
	encoder_init();
	PWM_init();
	I2C_master_init();
	
	ioport_enable_pin(pin_mapper(TASK_DEBUG_MOTOR_PIN));
	ioport_enable_pin(pin_mapper(TASK_DEBUG_MAIN_PIN));
	ioport_enable_pin(pin_mapper(30));
	ioport_set_pin_dir(pin_mapper(TASK_DEBUG_MOTOR_PIN), IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(pin_mapper(TASK_DEBUG_MAIN_PIN), IOPORT_DIR_OUTPUT);
// 	while (1)
// 	{
// 		master_write_cmd(TWI1,12);
// 		//I2C_master_read(TWI1, &packet_pos);
// 		for(int i = 0; i < 10; i++){
// 			printf("%d\n", array[i]);
// 		}
// 	}
	/* Create our tasks for the program */
	xTaskCreate(motor_task, (const signed char * const) "motor_task", TASK_MOTOR_STACK_SIZE, NULL, TASK_MOTOR_PRIORITY, NULL);
	xTaskCreate(main_task, (const signed char * const) "main_task", TASK_MAIN_STACK_SIZE, NULL, TASK_MAIN_PRIORITY, NULL);
	
	vTaskStartScheduler();
	
	return 0;
}
