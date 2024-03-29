//
// Created by penguinencounter on 3/28/24.
//

#include "fpioa.h"
#include "gpio_common.h"
#include "gpiohs.h"
#include "include/huskylens.h"
#include "pwm.h"

namespace hl
{
bool _rgb_initialized = false;

void rgb_init()
{
    _rgb_initialized = true;
    fpioa_set_function(0x20, FUNC_TIMER2_TOGGLE1);
    fpioa_set_function(0x1e, FUNC_TIMER2_TOGGLE2);
    fpioa_set_function(0x1f, FUNC_TIMER2_TOGGLE3);
    pwm_init(PWM_DEVICE_2);
    pwm_set_enable(PWM_DEVICE_2, PWM_CHANNEL_0, 1);
    pwm_set_enable(PWM_DEVICE_2, PWM_CHANNEL_1, 1);
    pwm_set_enable(PWM_DEVICE_2, PWM_CHANNEL_2, 1);
}
void rgb_set(const double r, const double g, const double b)
{
    if(!_rgb_initialized)
        rgb_init();
    pwm_set_frequency(PWM_DEVICE_2, PWM_CHANNEL_0, 100000.0, r);
    pwm_set_frequency(PWM_DEVICE_2, PWM_CHANNEL_1, 100000.0, g);
    pwm_set_frequency(PWM_DEVICE_2, PWM_CHANNEL_2, 100000.0, b);
}

bool _white_initialized = false;
void white_init()
{
    _white_initialized = true;
    fpioa_set_function(0x17, FUNC_TIMER1_TOGGLE1);
    pwm_init(PWM_DEVICE_1);
    pwm_set_enable(PWM_DEVICE_1, PWM_CHANNEL_0, 1);
}

void white_set(const double brightness)
{
    if(!_white_initialized)
        white_init();
    pwm_set_frequency(PWM_DEVICE_1, PWM_CHANNEL_0, 100000.0, brightness);
}

bool _buttons_initialized = false;
void buttons_init()
{
    _buttons_initialized = true;

    fpioa_set_function(0x27, FUNC_GPIOHS2);
    fpioa_set_function(0x26, FUNC_GPIOHS3);
    fpioa_set_function(0x25, FUNC_GPIOHS4);
    fpioa_set_function(0x24, FUNC_GPIOHS5);
    gpiohs_set_drive_mode(GPIO_LEARN, GPIO_DM_INPUT);
    gpiohs_set_drive_mode(GPIO_DIAL_LEFT, GPIO_DM_INPUT);
    gpiohs_set_drive_mode(GPIO_DIAL_PRESS, GPIO_DM_INPUT);
    gpiohs_set_drive_mode(GPIO_DIAL_RIGHT, GPIO_DM_INPUT);
}

button_state buttons_get()
{
    return {
        .learn = static_cast<bool>(gpiohs_get_pin(GPIO_LEARN)),
        .dial_left = static_cast<bool>(gpiohs_get_pin(GPIO_DIAL_LEFT)),
        .dial_press = static_cast<bool>(gpiohs_get_pin(GPIO_DIAL_PRESS)),
        .dial_right = static_cast<bool>(gpiohs_get_pin(GPIO_DIAL_RIGHT)),
    };
}

void init(const devices_t devices)
{
    if(devices & RGBLed)
        rgb_init();
    if(devices & WhiteLed)
        white_init();
    if(devices & Buttons)
        buttons_init();
}

} // namespace hl