
#ifndef INC_SERVO_HPP_
#define INC_SERVO_HPP_

#include "main.h" // To get TIM_HandleTypeDef

class Servo {
private:
    TIM_HandleTypeDef* _htim;   // Pointer to the Timer (e.g., &htim2)
    uint32_t _channel;          // PWM Channel (e.g., TIM_CHANNEL_1)
    uint32_t _min_pulse;        // Usually 500 (0 degrees)
    uint32_t _max_pulse;        // Usually 2500 (180 degrees)
    int _currentAngle; // Track position
	int _targetAngle;  // Track goal
	static const int HOME_ANGLE = 90; // Same home angle for all servos

public:
    // Constructor: Sets up the hardware links
    Servo(TIM_HandleTypeDef* htim, uint32_t channel);

    // Methods
    void start();               // Starts the PWM signal
    void setAngle(int angle);   // Moves to 0-180 degrees
    void setTarget(int angle);      // Set a new goal (Sweep)
	void update();                  // Call this in while(1) to move 1 step
	bool isMoving();                // Check if it reached the target
    void stop();                // Stops the PWM (if need to save power)
};


#endif /* INC_SERVO_HPP_ */
