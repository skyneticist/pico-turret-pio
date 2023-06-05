#include "pid_controller.h"

/// @brief 
/// @param controller 
/// @param kp 
/// @param ki 
/// @param kd 
void pid_controller_init_all(PIDController *controller, float kp, float ki, float kd)
{
    controller->Kp = kp;
    controller->Ki = ki;
    controller->Kd = kd;
    controller->prev_error = 0.0f;
    controller->integral = 0.0f;
}

/// @brief 
/// @param controller 
/// @param setpoint 
/// @param processVariable 
/// @param deltaTime 
/// @return 
float update_pid_controller(PIDController *controller, float setpoint, float processVariable, float deltaTime)
{
    // Calculate the error
    float error = setpoint - processVariable;
    
    // Calculate the proportional term
    float proportionalTerm = controller->Kp * error;
    
    // Calculate the integral term
    controller->integral += error * deltaTime;
    float integralTerm = controller->Ki * controller->integral;
    
    // Calculate the derivative term
    float derivativeTerm = controller->Kd * (error - controller->prev_error) / deltaTime;
    
    // Calculate the output
    float output = proportionalTerm + integralTerm + derivativeTerm;
    
    // Update the previous error value
    controller->prev_error = error;
    
    return output;
}
