#ifndef INC_SERVO_DRIVER_H_
#define INC_SERVO_DRIVER_H_

#include "main.h"

void Set_Servo_Angle(TIM_HandleTypeDef *htim, uint32_t channel, uint8_t angle);
void Get_UART_Angle(UART_HandleTypeDef *huart, int *angle);
void Demo_Servo_Motion(void);


#endif /* INC_SERVO_DRIVER_H_ */
