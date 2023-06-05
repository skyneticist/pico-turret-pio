#ifndef SPEED_PROFILE_H
#define SPEED_PROFILE_H

typedef struct {
    float acceleration;  // Acceleration rate
    float deceleration;  // Deceleration rate
    float current_speed;  // Current speed
    float target_speed;   // Target speed
} SpeedProfile;

/// @brief 
/// @param profile 
/// @param acceleration 
/// @param deceleration 
/// @param current_speed 
/// @param target_speed 
void init_speed_profile(SpeedProfile *profile, float acceleration, float deceleration, float current_speed, float target_speed);

/// @brief 
/// @param profile 
/// @param setpoint 
/// @param acceleration 
/// @param deceleration 
/// @param deltaTime 
void update_speed_profile(SpeedProfile *profile, float setpoint, float acceleration, float deceleration, float deltaTime);

#endif