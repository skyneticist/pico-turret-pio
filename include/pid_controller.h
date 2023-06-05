#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#define X_SETPOINT_INIT 640
#define Y_SETPOINT_INIT 460

typedef struct {
    float Kp;  // Proportional gain
    float Ki;  // Integral gain
    float Kd;  // Derivative gain
    float prev_error;  // Previous error value
    float integral;  // Integral value
} PIDController;

/// @brief 
/// @param controller 
/// @param kp 
/// @param ki 
/// @param kd 
void pid_controller_init_all(PIDController *controller, float kp, float ki, float kd);

/// @brief 
/// @param controller 
/// @param setpoint 
/// @param processVariable 
/// @param deltaTime 
/// @return 
float update_pid_controller(PIDController *controller, float setpoint, float processVariable, float deltaTime);

#endif