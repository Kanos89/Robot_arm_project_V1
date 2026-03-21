#include "servo_driver.h"

extern TIM_HandleTypeDef htim2;

// FCT to set servo angle
void Set_Servo_Angle(TIM_HandleTypeDef *htim, uint32_t channel, uint8_t angle){
	// convert of angle (0/180 deg) into pulse width (50/250)
	// 50 for 0 deg and 250 for 180
	uint32_t pulse_length = 50 + (angle*(250-50)/180);
	__HAL_TIM_SET_COMPARE(htim, channel, pulse_length);
	}

// FCT demonstration of servo angle go and go back
void Demo_Servo_Motion(void){
	//go from 0 to 180 deg by 10 deg steps
	for (uint8_t angle = 0; angle <= 180; angle += 10){
	Set_Servo_Angle(&htim2, TIM_CHANNEL_1, angle);
	HAL_Delay(1000);
	}

	//go from 180 to 0 deg by 10 deg steps
	for (uint8_t angle = 180; angle > 0; angle -= 10){
	Set_Servo_Angle(&htim2, TIM_CHANNEL_1, angle);
	HAL_Delay(1000);
	}
}
// FCT to input servo angle
void Get_UART_Angle(UART_HandleTypeDef *huart, int *angle) {
    char buffer[10];
    uint8_t i = 0;
    uint8_t char_in;

    // Clear buffer
    memset(buffer, 0, sizeof(buffer));

    // Receive characters until 'Enter' (carriage return) is pressed
    // Can be improved with listening to 'BackSlash' for missing input
    while (i < 9) {
        if (HAL_UART_Receive(huart, &char_in, 1, HAL_MAX_DELAY) == HAL_OK) {
            // User pressed Enter
        	if (char_in == '\r' || char_in == '\n') {
        		uint8_t newline[] = "\r\n";
				HAL_UART_Transmit(huart, newline, 2, 10);
            	break;
            }
            buffer[i++] = char_in;
            HAL_UART_Transmit(huart, &char_in, 1, 10); // Echo back to see what you type
        }
    }
    *angle = atoi(buffer); // Convert string to integer
}
