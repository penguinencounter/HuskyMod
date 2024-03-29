//
// Created by penguinencounter on 3/28/24.
//

#include "gpio_common.h"
#include "gpiohs.h"
#include "include/huskylens.h"
#include "pwm.h"

namespace hl
{
bool _rgb_initialized = false;

void setup_rgb()
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
void set_rgb(double r, double g, double b)
{
    if(!_rgb_initialized)
        setup_rgb();
    pwm_set_frequency(PWM_DEVICE_2, PWM_CHANNEL_0, 100000.0, r);
    pwm_set_frequency(PWM_DEVICE_2, PWM_CHANNEL_1, 100000.0, g);
    pwm_set_frequency(PWM_DEVICE_2, PWM_CHANNEL_2, 100000.0, b);
}

bool _white_initialized = false;
void setup_white()
{
    _white_initialized = true;
    fpioa_set_function(0x17, FUNC_TIMER1_TOGGLE1);
    pwm_init(PWM_DEVICE_1);
    pwm_set_enable(PWM_DEVICE_1, PWM_CHANNEL_0, 1);
}

void set_white(double brightness)
{
    if(!_white_initialized)
        setup_white();
    pwm_set_frequency(PWM_DEVICE_1, PWM_CHANNEL_0, 100000.0, brightness);
}

bool _buttons_initialized = false;
void setup_buttons()
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

button_state get_buttons()
{
    return {
        static_cast<bool>(gpiohs_get_pin(GPIO_LEARN)),
        static_cast<bool>(gpiohs_get_pin(GPIO_DIAL_LEFT)),
        static_cast<bool>(gpiohs_get_pin(GPIO_DIAL_PRESS)),
        static_cast<bool>(gpiohs_get_pin(GPIO_DIAL_RIGHT)),
    };
}

void setup(devices_t devices) {
    if (devices & devices_t::RGBLed) setup_rgb();
    if (devices & devices_t::RGBLed) setup_white();
    if (devices& devices_t::Buttons) setup_buttons();
}

} // namespace hl