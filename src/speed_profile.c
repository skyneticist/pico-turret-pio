#include "speed_profile.h"

/// @brief 
/// @param profile 
/// @param acceleration 
/// @param deceleration 
/// @param current_speed 
/// @param target_speed 
void init_speed_profile(SpeedProfile *profile, float acceleration, float deceleration, float current_speed, float target_speed)
{
    profile->acceleration = acceleration;
    profile->deceleration = deceleration;
    profile->current_speed = current_speed;
    profile->target_speed = target_speed;
}

/// @brief 
/// @param profile 
/// @param setpoint 
/// @param acceleration 
/// @param deceleration 
/// @param deltaTime 
void update_speed_profile(SpeedProfile *profile, float setpoint, float acceleration, float deceleration, float deltaTime)
{
    float error = setpoint - profile->current_speed;
    
    // Apply acceleration and deceleration profiles
    if (error > 0) {
        profile->current_speed += acceleration * deltaTime;
        if (profile->current_speed > setpoint) {
            profile->current_speed = setpoint;
        }
    } else if (error < 0) {
        profile->current_speed -= deceleration * deltaTime;
        if (profile->current_speed < 0) {
            profile->current_speed = 0;
        }
    }
}
