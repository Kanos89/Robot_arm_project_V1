#include "Servo.hpp"

Servo::Servo(TIM_HandleTypeDef* htim, uint32_t channel)
    : _htim(htim), _channel(channel), _min_pulse(50), _max_pulse(250),
	  _currentAngle(HOME_ANGLE), _targetAngle(HOME_ANGLE) {}

//start the channel and timer set
void Servo::start() {
	// Initialize the position with HOME_ANGLE
	uint32_t pulse = _min_pulse + ((_currentAngle * (_max_pulse - _min_pulse)) / 180);
		__HAL_TIM_SET_COMPARE(_htim, _channel, pulse);
    HAL_TIM_PWM_Start(_htim, _channel);
}

//directly move to angle (full speed, high current consumption)
void Servo::setAngle(int angle) {
    // Ensure 0-180 degree control
	if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;

    // Map 0-180 degrees to 50-250 pulse width
    uint32_t pulse = _min_pulse + ((angle * (_max_pulse - _min_pulse)) / 180);
	__HAL_TIM_SET_COMPARE(_htim, _channel, pulse);
}

// Initiate Target angle
void Servo::setTarget(int angle) {
    if (angle < 0) angle = 0;
    if (angle > 180) angle = 180;
    _targetAngle = angle;
}

// Move one step toward target (used to coordinate multiple servos)
void Servo::update() {
    if (_currentAngle < _targetAngle) {
        _currentAngle++;
        setAngle(_currentAngle);
    } else if (_currentAngle > _targetAngle) {
        _currentAngle--;
        setAngle(_currentAngle);
    }
}

// Check state of servo
bool Servo::isMoving() {
    return _currentAngle != _targetAngle;
}

//release PWM for power saving
void Servo::stop() {
    HAL_TIM_PWM_Stop(_htim, _channel);
}
